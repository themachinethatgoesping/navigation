// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensorconfiguration.doc.hpp"
#include <array>
#include <cmath>
#include <exception>
#include <iostream>
#include <math.h>
#include <optional>
#include <string>
#include <string_view>

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/rotation.hpp>

#include "datastructures.hpp"
#include "sensorconfiguration_presets.hpp"

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief A coordinate system that allows for specifying sensor offsets (e.g. gps antenna and
 * attitude sensor) and target offsets (e.g. MBES). Call the class and specify target_id and current
 * sensor data to derive the geolocation and attitude of the specified targets
 *
 */
class SensorConfiguration
{
    // Note: by using a ordered map, the targets are sorted by their target_id
    // because the order is the same, the binary hash will be the same
    // Otherwise, the binary hash would be different for the same content in different order
    std::map<std::string, datastructures::SensorPose>
        _target_offsets; ///< TargetId (position in vector) for each registered target_id

    /// Optional named subarray offsets per target. Keyed [target_id][subarray_id]; each entry is a
    /// SensorPose in the target (transducer) frame that compute_target_pose can add to the target
    /// pose to obtain a per-subarray phase center (e.g. multibeam transmit subarrays
    /// port/center/starboard and the receive-array phase center).
    std::map<std::string, std::map<std::string, datastructures::SensorPose>>
        _target_subarray_offsets;

    std::string _model_name;               ///< echosounder model (e.g. "EM2040"); set by format readers
    std::string _transducer_configuration; ///< configuration string (e.g. "DualRx", "STC0"); set by format readers

    datastructures::SensorPose
        _offsets_attitude_source; ///< Static Roll,Pitch,Yaw (installation) offsets of the attitude
                                  ///< sensor
    datastructures::SensorPose
        _offsets_heading_source; ///< Static Yaw (installation) Offsets of CompassOffsets
    datastructures::SensorPose
        _offsets_position_source; ///< Static x,y,z (installation) Offsets of the PositionSystem
    datastructures::SensorPose
        _offsets_depth_source; ///< Static xy,z (installation) Offsets of the depth sensor
    // Static Position of Heave Sensor
    // Offsets _HeaveSensorOffsets;

    float _waterline_offset =
        0.0; ///< Waterline offset (negative waterline offset means that z=0 is below the waterline

    bool _position_source_motion_compensated =
        false; ///< true if the logged position is already referenced to the vessel reference point
               ///< (motion compensation applied by the PU, e.g. .all P{n}M=1 / .kmall POSI C=On).
               ///< Then compute_position_system_offset returns {0,0,0}.

    /// Display preference for __printer__ only (NOT serialized, NOT part of equality/hash):
    /// true = one row per target (compact table); false = transposed (fields as rows, with an
    /// explanation column). Toggle with set_printer_style / print(optionA=...).
    bool _printer_style_a = true;

    mutable std::optional<xxh::hash_t<64>> _cached_binary_hash; ///< cached binary hash, reset on mutation

    /// Derived cache: each registered subarray phase center combined with its target, expressed in
    /// the vessel-static frame (position target.xyz + target.rotation·subarray.xyz, rotation
    /// target.rotation·subarray.rotation). Keyed [target_id][subarray_id] — linked to
    /// _target_subarray_offsets by the same keys — and rebuilt on demand whenever the configuration
    /// changes. Not serialized (fully derived from _target_offsets + _target_subarray_offsets).
    mutable bool _subarray_poses_cached = false;
    mutable std::map<std::string, std::map<std::string, datastructures::SensorPose>>
        _target_subarray_poses;

    /// Invalidate the cached binary hash and derived caches (call from every mutating method)
    void invalidate_hash_cache()
    {
        _cached_binary_hash.reset();
        _subarray_poses_cached = false;
    }

    /// Combine a target pose with a subarray offset (target/array frame) into the vessel-static frame.
    static datastructures::SensorPose combine_target_subarray(
        const datastructures::SensorPose& target, const datastructures::SensorPose& subarray);

    /// (Re)build _target_subarray_poses from the current targets + subarray offsets if stale.
    void ensure_subarray_poses() const;

  public:
    /**
     * @brief Construct a new, empty Sensor Coordinate System object
     * After construction: add sensor offsets and targets (offsets)
     * Then compute target positions for sensor data
     *
     */
    SensorConfiguration(std::string_view default_sensor_name = "zero-referenced")
    {
        _offsets_attitude_source.name = default_sensor_name;
        _offsets_heading_source.name  = default_sensor_name;
        _offsets_position_source.name = default_sensor_name;
        _offsets_depth_source.name    = default_sensor_name;

        add_target("0", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    }

    /**
     * @brief Return the SensorConfiguration object without registered targets
     *
     * @return SensorConfiguration
     */
    SensorConfiguration without_targets() const
    {
        SensorConfiguration result(*this);
        result.remove_targets();
        return result;
    }

    /**
     * @brief Check if the given SensorConfiguration includes a target (offsets) that is
     * incompatible with the given SensorConfiguration targets
     *
     * @return false if the same target_id is registered with different offsets, true otherwise
     */
    bool can_merge_targets_with(const SensorConfiguration& other) const
    {
        /* check for incompatible targets */
        for (const auto& [target_id, offsets] : _target_offsets)
        {
            if (other._target_offsets.find(target_id) != other._target_offsets.end())
            {
                if (offsets != other._target_offsets.at(target_id))
                    return false;
            }
        }

        return true;
    }

    // ----- compute_target_position -----
    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensordataLatLon / this structure includes latitude and longitude
     * information
     * @return datastructures::GeolocationLatLon  / this structure includes latitude and longitude
     * information
     */
    datastructures::GeolocationLatLon compute_target_position(
        const std::string&                      target_id,
        const datastructures::SensordataLatLon& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensordataUTM / this structure includes northing/easting and utm zone or
     * hemisphere information
     * @return datastructures::GeolocationUTM  / this structure includes northing/easting and utm
     * zone or hemisphere information
     */
    datastructures::GeolocationUTM compute_target_position(
        const std::string&                   target_id,
        const datastructures::SensordataUTM& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensordataLocal / this structure includes northing/easting but no zone or
     * hemisphere information
     * @return datastructures::GeolocationLocal  / this structure includes northing/easting but no
     * zone or hemisphere information
     */
    datastructures::GeolocationLocal compute_target_position(
        const std::string&                     target_id,
        const datastructures::SensordataLocal& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data Sensordata / this structure includes no coordinate information
     * @return datastructures::GeolocationLocal  / this structure includes northing and east, which
     * are set relative to the sensor coordinate system center
     */
    datastructures::GeolocationLocal compute_target_position(
        const std::string&                target_id,
        const datastructures::Sensordata& sensor_data) const;

    /**
     * @brief Compute the offset-corrected vessel orientation as a Rotation.
     *
     * Applies the registered sensor mounting offsets to the raw sensor_data attitude: the attitude
     * source (IMU) mounting offset is removed with a rotation operation (raw ⊗ offset⁻¹, i.e.
     * yaw/pitch/roll are NOT simply added) and the heading source offset is subtracted from the
     * heading -- both only when they are not already applied to the logged data
     * (SensorPose::ypr_offsets_applied). The heading is then expressed relative to
     * reference_heading_in_degrees. Use rotation.ypr() to obtain the {yaw, pitch, roll} angles.
     *
     * @param sensor_data Sensordata (only heading, pitch and roll are used)
     * @param reference_heading_in_degrees heading (deg) removed from the orientation so the result
     * is expressed in the surface frame of that heading (0 = keep the absolute world heading); for a
     * receive pose sampled after transmit this keeps the residual yaw (vessel turn since transmit)
     * @return vessel orientation (Rotation), heading measured relative to reference_heading
     */
    tools::rotationfunctions::Rotation<float> get_vessel_rotation(
        const datastructures::Sensordata& sensor_data,
        float                             reference_heading_in_degrees = 0.f) const;

    /**
     * @brief Compute the ready-to-trace pose (position + ship-frame orientation) of a target.
     *
     * Unlike compute_target_position (which returns a geolocation), this bakes the target
     * installation, the vessel attitude and the removal of a common reference heading into a
     * single pose, so a raytracer can consume it without re-composing
     * installation/attitude/heading. The orientation is
     * vessel_rotation(reference_heading) · target_installation and the position is that SAME
     * reference-relative vessel_rotation applied to the body-frame lever arm (z reduced to the
     * depth below the waterline). Pass the SAME reference_heading (the heading at transmit time) for
     * every target of a ping so all poses share one surface frame.
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data Sensordata (heading/pitch/roll + depth/heave)
     * @param reference_heading_in_degrees heading (deg) removed from the orientation (transmit
     * heading)
     * @param subarray_id optional name of a registered subarray offset of the target to add to the
     * pose (e.g. "0"/"1"/"2" for a transmit subarray, "RX" for the receive phase center); "" = none
     * @param subarray_pose optional explicit subarray offset (target frame) that overrides
     * @p subarray_id; handy for debugging or one-off corrections
     * @return target pose (position + ship-frame Rotation)
     */
    datastructures::SensorPose compute_target_pose(
        const std::string&                               target_id,
        const datastructures::Sensordata&                sensor_data,
        float                                            reference_heading_in_degrees,
        const std::string&                               subarray_id   = "",
        const std::optional<datastructures::SensorPose>& subarray_pose = std::nullopt) const;

    /**
     * @brief Compute the location of the active position-system reference point relative to the
     * vessel reference point, in the surface (reference-heading) frame.
     *
     * This is the heading-referenced translation between the position system and the vessel
     * reference point: vessel_rotation(reference_heading) · position_source_lever_arm. It carries
     * the full horizontal antenna lever arm (not only its vertical component), so it can be used to
     * convert beam positions referenced to the positioning system (e.g. Kongsberg .all XYZ88) into
     * the vessel-reference-point convention (e.g. Kongsberg .kmall).
     *
     * @param sensor_data Sensordata (heading/pitch/roll are used)
     * @param reference_heading_in_degrees heading (deg) removed from the orientation (transmit
     * heading); 0 = keep the absolute world heading
     * @param at_waterline if true, replace the antenna height by the waterline offset, i.e. project
     * the position-system point onto the water surface (the horizontal reference of the .all XYZ88
     * beam positions); if false, use the true antenna height (position_source.z)
     * @return {x, y, z} of the position-system reference point in the surface frame (metres)
     */
    std::array<float, 3> compute_position_system_offset(
        const datastructures::Sensordata& sensor_data,
        float                             reference_heading_in_degrees = 0.f,
        bool                              at_waterline                 = false) const;

    // ----- get/set target offsets -----

    /**
     * Checks if the sensor configuration has a target with the specified ID.
     *
     * @param target_id The ID of the target to check for.
     * @return True if the sensor configuration has the target, false otherwise.
     */
    bool has_target(const std::string& target_id) const;

    /**
     * @brief add a target (e.g. MBES) with offsets to the sensor position system
     *
     * @param target_id name of the target for reference
     * @param x x-offset of the target (in meters, positive forward)
     * @param y y-offset of the target (in meters, positive starboard)
     * @param z z-offset of the target (in meters, positive down)
     * @param yaw yaw offset of the target (right-handed around the z-axis) (in degrees, 90° = east)
     * @param pitch pitch offset of the target (right-handed around the y-axis) (in degrees,
     * positive = bow up)
     * @param roll roll offset of the target (right-handed around the x-axis) (in degrees, positive
     * = port up)
     */
    void add_target(const std::string& target_id,
                    float              x,
                    float              y,
                    float              z,
                    float              yaw,
                    float              pitch,
                    float              roll);

    /**
     * @brief add a target (e.g. MBES) with offsets to the sensor position system
     *
     * @param target_id name of the target for reference
     * @param target_offsets mounting offsets of the target
     */
    void add_target(const std::string&                       target_id,
                    const datastructures::SensorPose& target_offsets);

    /**
     * @brief add targets (e.g. MBES) with given target_ids and offsets to the sensor position
     * system
     *
     * @param targets map<target_id, target_offsets> of target offsets
     */
    void add_targets(const std::map<std::string, datastructures::SensorPose>& targets);

    /**
     * @brief Get stored target offsets of a specified target
     *
     * @param target_id name of the registered target
     * @return const datastructures::SensorPose& offsets of the target
     */
    const datastructures::SensorPose& get_target(const std::string& target_id) const;

    /**
     * @brief Get a target's static pose, optionally combined with one of its subarray phase centers.
     *
     * The subarray offset lives in the target (transducer/array) frame; the returned combined pose is
     * in the vessel-static frame (independent of vessel attitude), so compute_target_pose can rotate
     * it in one step. Registered subarrays return a precomputed pose; a custom @p subarray_pose is
     * combined on the fly.
     *
     * @param target_id registered target
     * @param subarray_id registered subarray of the target ("" = none, returns the plain target)
     * @param subarray_pose optional explicit subarray offset (target frame) overriding @p subarray_id
     * @return the (combined) target pose in the vessel-static frame
     */
    datastructures::SensorPose get_target(
        const std::string&                               target_id,
        const std::string&                               subarray_id,
        const std::optional<datastructures::SensorPose>& subarray_pose = std::nullopt) const;

    /**
     * @brief Get the map of stored target offsets objects
     *
     * @return const std::unordered_map<std::string, datastructures::SensorPose>&
     */
    const std::map<std::string, datastructures::SensorPose>& get_targets() const;

    /**
     * @brief Remove the target with the specified target_id
     *
     * @param target_id name of the registered target
     */
    void remove_target(const std::string& target_id);

    /**
     * @brief Remove all stored targets
     *
     */
    void remove_targets();

    // ----- target subarray offsets (transmit subarrays / receive phase center) -----
    /**
     * @brief Register (or overwrite) a single named subarray offset for a target.
     *
     * A subarray offset is a small SensorPose in the target (transducer) frame that
     * compute_target_pose can add to the target pose to obtain the pose of a specific transmit
     * subarray or the receive-array phase center. The position is always applied; the rotation is
     * only composed when it is not the identity (see SensorPose::has_zero_rotation).
     *
     * @param target_id parent target
     * @param subarray_id name of the subarray (e.g. "0"/"1"/"2" for tx port/center/starboard, "RX")
     * @param subarray_offsets offset pose in the target frame
     */
    void add_target_subarray(const std::string&                target_id,
                             const std::string&                subarray_id,
                             const datastructures::SensorPose& subarray_offsets);

    /**
     * @brief Replace all subarray offsets of a target with the given map.
     * @param target_id parent target
     * @param subarrays map<subarray_id, offset pose in the target frame>
     */
    void set_target_subarrays(
        const std::string&                                       target_id,
        const std::map<std::string, datastructures::SensorPose>& subarrays);

    /**
     * @brief Attach a flat subarray-offset map to every registered target by its role, so a head
     * only carries the offsets of the array(s) it actually contains.
     *
     * The transmit subarrays (all keys except "RX") are attached to transmit targets (id starts
     * with "TX"), the receive phase center ("RX") to receive targets (id starts with "RX"), and a
     * combined transmit/receive target (id starts with "TRX") receives both. Targets that match no
     * role (e.g. "0") are left untouched. No-op if @p subarrays is empty.
     *
     * @param subarrays flat map<subarray_id, offset pose> as returned by get_model_subarray_offsets
     */
    void set_subarrays_by_role(const std::map<std::string, datastructures::SensorPose>& subarrays);

    /**
     * @brief Set the subarray offsets of a target from the hardcoded per-model preset.
     *
     * Looks the model up with get_model_subarray_offsets and stores the result on @p target_id.
     * Does nothing if the model is unknown (get_model_subarray_offsets returns an empty map).
     *
     * @param target_id parent target
     * @param model_name echosounder model (e.g. "EM2040", "EM2040P", "2042"); case-insensitive,
     *        an optional leading "EM" is ignored
     */
    void set_target_subarrays_from_model(const std::string& target_id, std::string_view model_name);

    /// @brief true if the target has any registered subarray offsets.
    bool has_target_subarrays(const std::string& target_id) const;

    /// @brief true if the target has a subarray offset with the given id.
    bool has_target_subarray(const std::string& target_id, const std::string& subarray_id) const;

    /**
     * @brief Get a single registered subarray offset.
     * @param target_id parent target
     * @param subarray_id name of the subarray
     * @return the subarray offset pose (throws std::out_of_range if not registered)
     */
    const datastructures::SensorPose& get_target_subarray(const std::string& target_id,
                                                          const std::string& subarray_id) const;

    /**
     * @brief Get all subarray offsets of a target.
     * @param target_id parent target
     * @return map<subarray_id, offset pose> (throws std::out_of_range if the target has none)
     */
    const std::map<std::string, datastructures::SensorPose>& get_target_subarrays(
        const std::string& target_id) const;

    /// @brief Ids of the subarray offsets registered for a target (empty if none).
    std::vector<std::string> get_target_subarray_ids(const std::string& target_id) const;

    /// @brief Remove all subarray offsets of a target.
    void remove_target_subarrays(const std::string& target_id);

    /**
     * @brief Hardcoded transmit/receive subarray phase-center offsets for a known echosounder model.
     *
     * Returns a flat map with the transmit subarrays keyed "0" (port), "1" (center), "2"
     * (starboard) — or just "0" for single-array systems — plus the receive-array phase center
     * keyed "RX". All offsets are SensorPoses in the transducer frame (x forward, y starboard,
     * z down, metres). The map is empty for an unknown model. Source: QPS dm-0423 / Kongsberg.
     *
     * @param model_name echosounder model (case-insensitive, optional leading "EM" ignored)
     */
    static std::map<std::string, datastructures::SensorPose> get_model_subarray_offsets(
        std::string_view model_name);

    /**
     * @brief A single hardcoded subarray offset for a model (convenience for building a manual
     *        subarray_pose, e.g. for compute_target_pose debugging).
     * @param model_name echosounder model
     * @param subarray_id "0"/"1"/"2"/"RX"
     * @return the offset pose (throws std::out_of_range if the model or subarray is unknown)
     */
    static datastructures::SensorPose get_model_subarray_offset(std::string_view   model_name,
                                                                const std::string& subarray_id);

    // ----- system metadata -----
    /// @brief Set the echosounder model name (e.g. "EM2040", "EM710").
    void set_model_name(std::string name);
    /// @brief Echosounder model name, or empty string if not set.
    std::string get_model_name() const { return _model_name; }

    /// @brief Set the transducer configuration string (e.g. "DualRx", "SingleTxSingleRx", "STC0").
    void set_transducer_configuration(std::string cfg);
    /// @brief Transducer configuration string, or empty string if not set.
    std::string get_transducer_configuration() const { return _transducer_configuration; }

    /// @brief select the print()/info_string() table layout: true = one row per target (default,
    /// compact), false = transposed (fields x/y/z/... as rows, records as columns + explanation).
    void set_printer_style(bool row_per_target) { _printer_style_a = row_per_target; }
    /// @brief current print() table layout (see set_printer_style)
    bool get_printer_style() const { return _printer_style_a; }

    // ----- get/set sensor offsets -----
    /**
     * @brief Set the attitude sensor offsets
     *
     * @param sensor_offsets offsets structure (only yaw, pitch and roll are used)
     */
    void set_attitude_source(const datastructures::SensorPose& sensor_offsets);

    /**
     * @brief Set the attitude sensor offsets
     *
     * @param yaw yaw offset of the attitude sensor (right-handed around the z-axis) (in degrees,
     * 90° = east)
     * @param pitch pitch offset of the attitude sensor (right-handed around the y-axis) (in
     * degrees, positive = bow up)
     * @param roll roll offset of the attitude sensor (right-handed around the x-axis) (in degrees,
     * positive = port up)
     */
    void set_attitude_source(std::string_view name, float yaw, float pitch, float roll);

    /**
     * @brief Get the attitude sensor offsets
     *
     * @return const datastructures::SensorPose& offsets of the attitude sensor
     */
    datastructures::SensorPose get_attitude_source() const;

    /**
     * @brief Set the compass offsets
     *
     * @param yaw yaw offset of the compass (right-handed around the z-axis) (in degrees, 90° =
     * east)
     */
    void set_heading_source(std::string_view name, float yaw);

    /**
     * @brief Set the compass offsets
     *
     * @param sensor_offsets offsets structure (only yaw is used)
     */
    void set_heading_source(const datastructures::SensorPose& sensor_offsets);

    /**
     * @brief Get the registered compass offsets
     *
     * @return const datastructures::SensorPose& offsets of the compass
     */
    datastructures::SensorPose get_heading_source() const;

    /**
     * @brief Set the waterline offset
     * Negative waterline offset means that z=0 is below the waterline
     *
     * @param waterline_offset
     */
    void set_waterline_offset(float waterline_offset);

    /**
     * @brief Get the waterline offset
     * Negative waterline offset means that z=0 is below the waterline
     *
     * @return waterline_offset
     */
    float get_waterline_offset() const;

    /**
     * @brief Set whether the position source is motion compensated.
     *
     * When true, the logged position is already referenced to the vessel reference point (the PU
     * applied the antenna-to-reference-point lever arm, e.g. Kongsberg .all P{n}M=1 or .kmall POSI
     * C=On). In that case compute_position_system_offset returns {0,0,0} instead of the geometric
     * antenna lever arm, so beam positions referenced to the positioning system are not
     * double-corrected.
     *
     * @param motion_compensated true if the position is already re the vessel reference point
     */
    void set_position_source_motion_compensated(bool motion_compensated);

    /**
     * @brief Get whether the position source is motion compensated.
     *
     * See set_position_source_motion_compensated.
     *
     * @return true if the logged position is already re the vessel reference point
     */
    bool get_position_source_motion_compensated() const;

    /**
     * @brief Set the depth sensor offsets
     *
     * @param x x-offset of the depth sensor (in meters, positive forward)
     * @param y y-offset of the depth sensor (in meters, positive starboard)
     * @param z z-offset of the depth sensor (in meters, positive down)
     */
    void set_depth_source(std::string_view name, float x, float y, float z);

    /**
     * @brief Set the depth sensor offsets
     *
     * @param sensor_offsets offsets structure (only x, y and z are used)
     */
    void set_depth_source(const datastructures::SensorPose& sensor_offsets);

    /**
     * @brief Get the registered depth sensor offsets
     *
     * @return const datastructures::SensorPose& offsets of the depth sensor
     */
    datastructures::SensorPose get_depth_source() const;

    /**
     * @brief Set the position system offsets
     *
     * @param x x-offset of the depth sensor (in meters, positive forward)
     * @param y y-offset of the depth sensor (in meters, positive starboard)
     * @param z z-offset of the depth sensor (in meters, positive down)
     */
    void set_position_source(std::string_view name, float x, float y, float z);

    /**
     * @brief Set the position system offsets
     *
     * @param sensor_offsets offsets structure (only x, y and z are used)
     */
    void set_position_source(const datastructures::SensorPose& sensor_offsets);

    /**
     * @brief Get the registered position system offsets
     *
     * @return const datastructures::SensorPose& offsets of the position system
     */
    datastructures::SensorPose get_position_source() const;

    /**
     * @brief Get the ids of the registered targets
     *
     * @return std::vector<std::string_view>
     */
    std::vector<std::string> get_target_ids() const
    {
        std::vector<std::string> target_ids;
        for (const auto& target : _target_offsets)
        {
            target_ids.push_back(target.first);
        }
        return target_ids;
    }

  private:
    // ----- helper functions -----
    /**
     * @brief Compute the rotation of the sensor coordinate system (relative to the world reference
     * coordinate system) using the sensor data and (rotation) offsets. Note: if
     * heading is used the attitude_source_offset yaw will be used to correct the
     * attitude_source_offset roll and pitch but will not be added to the heading
     *
     * @param sensor_data Sensor data object (used are: heading, pitch,
     * roll)
     * @param offsets_heading_source Offsets of the compass (used is only yaw offset)
     * @param offsets_attitude_source Offsets of the IMU (used are yaw, pitch and roll), if
     * heading is used, yaw is used to correct pitch, and roll but not added to the heading
     * @param reference_heading_in_degrees heading (deg) removed from the result so it is expressed
     * relative to that heading (0 = absolute world heading)
     * @return Rotation of the sensor system relative to the (reference) world reference system
     */
    static tools::rotationfunctions::Rotation<float> get_system_rotation(
        const datastructures::Sensordata& sensor_data,
        const datastructures::SensorPose& offsets_heading_source,
        const datastructures::SensorPose& offsets_attitude_source,
        float                             reference_heading_in_degrees = 0.f);

  public:
    // ----- file I/O -----
    /**
     * @brief Write the sensor configuration to a stream.
     * Warning: there is no error checking!
     *
     * @param os
     */
    void to_stream(std::ostream& os) const
    {
        using tools::classhelper::stream::container_to_stream;

        // iterate over _target_offsets to write them to the stream
        unsigned int num_targets = _target_offsets.size();
        os.write(reinterpret_cast<const char*>(&num_targets), sizeof(num_targets));

        for (const auto& target : _target_offsets)
        {
            container_to_stream(os, target.first);
            target.second.to_stream(os);
        }

        _offsets_attitude_source.to_stream(os);
        _offsets_heading_source.to_stream(os);
        _offsets_position_source.to_stream(os);
        _offsets_depth_source.to_stream(os);
        os.write(reinterpret_cast<const char*>(&_waterline_offset), sizeof(_waterline_offset));
        os.write(reinterpret_cast<const char*>(&_position_source_motion_compensated),
                 sizeof(_position_source_motion_compensated));

        // subarray offsets: map<target_id, map<subarray_id, SensorPose>>
        unsigned int num_sub_targets = _target_subarray_offsets.size();
        os.write(reinterpret_cast<const char*>(&num_sub_targets), sizeof(num_sub_targets));
        for (const auto& [target_id, subarrays] : _target_subarray_offsets)
        {
            container_to_stream(os, target_id);
            unsigned int num_subarrays = subarrays.size();
            os.write(reinterpret_cast<const char*>(&num_subarrays), sizeof(num_subarrays));
            for (const auto& [subarray_id, offsets] : subarrays)
            {
                container_to_stream(os, subarray_id);
                offsets.to_stream(os);
            }
        }

        container_to_stream(os, _model_name);
        container_to_stream(os, _transducer_configuration);
    }

    /**
     * @brief Read the sensor configuration from a stream.
     * Warning: there is no error checking!
     *
     * @param is
     * @return SensorConfiguration
     */
    static SensorConfiguration from_stream(std::istream& is)
    {
        using datastructures::SensorPose;
        using tools::classhelper::stream::container_from_stream;

        SensorConfiguration obj;

        unsigned int num_targets;
        is.read(reinterpret_cast<char*>(&num_targets), sizeof(num_targets));
        while (num_targets--)
        {
            std::string       target_id               = container_from_stream<std::string>(is);
            SensorPose target_offsets          = SensorPose::from_stream(is);
            obj._target_offsets[std::move(target_id)] = std::move(target_offsets);
        }

        obj._offsets_attitude_source = SensorPose::from_stream(is);
        obj._offsets_heading_source  = SensorPose::from_stream(is);
        obj._offsets_position_source = SensorPose::from_stream(is);
        obj._offsets_depth_source    = SensorPose::from_stream(is);
        is.read(reinterpret_cast<char*>(&obj._waterline_offset), sizeof(obj._waterline_offset));
        is.read(reinterpret_cast<char*>(&obj._position_source_motion_compensated),
                sizeof(obj._position_source_motion_compensated));

        unsigned int num_sub_targets;
        is.read(reinterpret_cast<char*>(&num_sub_targets), sizeof(num_sub_targets));
        while (num_sub_targets--)
        {
            std::string  target_id = container_from_stream<std::string>(is);
            unsigned int num_subarrays;
            is.read(reinterpret_cast<char*>(&num_subarrays), sizeof(num_subarrays));
            std::map<std::string, SensorPose> subarrays;
            while (num_subarrays--)
            {
                std::string subarray_id           = container_from_stream<std::string>(is);
                subarrays[std::move(subarray_id)] = SensorPose::from_stream(is);
            }
            obj._target_subarray_offsets[std::move(target_id)] = std::move(subarrays);
        }

        obj._model_name              = container_from_stream<std::string>(is);
        obj._transducer_configuration = container_from_stream<std::string>(is);

        return obj;
    }

    /**
     * @brief Compare two SensorConfiguration objects for equality
     *
     * @param other SensorConfiguration object to compare to
     * @return true
     * @return false
     */
    bool operator==(const SensorConfiguration& other) const
    {
        if (_target_offsets.size() != other._target_offsets.size())
        {
            return false;
        }

        for (const auto& [target_id, target_offsets] : _target_offsets)
        {
            if (other._target_offsets.find(target_id) == other._target_offsets.end())
            {
                return false;
            }
            if (target_offsets != other._target_offsets.at(target_id))
            {
                return false;
            }
        }

        return _offsets_attitude_source == other._offsets_attitude_source &&
               _offsets_heading_source == other._offsets_heading_source &&
               _offsets_position_source == other._offsets_position_source &&
               _offsets_depth_source == other._offsets_depth_source &&
               _waterline_offset == other._waterline_offset &&
               _position_source_motion_compensated ==
                   other._position_source_motion_compensated &&
               _target_subarray_offsets == other._target_subarray_offsets &&
               _model_name == other._model_name &&
               _transducer_configuration == other._transducer_configuration;
    }
    /**
     * @brief Compare two SensorConfiguration objects for inequality
     *
     * @param other SensorConfiguration object to compare to
     * @return true
     * @return false
     */
    bool operator!=(const SensorConfiguration& other) const { return !(*this == other); }

    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer(
            "SensorConfiguration", float_precision, superscript_exponents);

        auto fnum = [&](float v) { return fmt::format("{:.{}f}", v, float_precision); };
        auto pose_cells = [&](const datastructures::SensorPose& p) {
            return std::vector<std::string>{ fnum(p.x),     fnum(p.y),       fnum(p.z),
                                             fnum(p.yaw()), fnum(p.pitch()), fnum(p.roll()) };
        };
        auto make_row = [&](const std::string& label, const datastructures::SensorPose& p) {
            std::vector<std::string> row   = { label };
            auto                     cells = pose_cells(p);
            row.insert(row.end(), cells.begin(), cells.end());
            return row;
        };

        // Stack similar records as an aligned table. Two styles, selectable via set_printer_style /
        // print(optionA=...): style A = one row per record; style B = the transposed layout (fields
        // x/y/z/yaw/pitch/roll as rows, records as columns) which keeps an explanation last column.
        const std::vector<std::string> explanation = { "explanation", "forward, m",  "starboard, m",
                                                       "down, m",     "yaw, deg",    "pitch, deg",
                                                       "roll, deg" };
        auto add_table = [&](std::string_view title, const std::string& first_column,
                             std::vector<std::vector<std::string>> rows) {
            if (rows.empty())
                return;
            if (_printer_style_a)
                printer.register_table(
                    title, { first_column, "x", "y", "z", "yaw", "pitch", "roll" }, rows);
            else
            {
                rows.push_back(explanation);
                printer.register_table(
                    title, { "field", "x", "y", "z", "yaw", "pitch", "roll" }, rows, true);
            }
        };

        std::vector<std::vector<std::string>> targets;
        for (const auto& [id, pose] : _target_offsets)
            targets.push_back(make_row(id, pose));
        add_table("Target offsets", "target", std::move(targets));

        add_table("Sensor offsets", "sensor",
                  { make_row("attitude", _offsets_attitude_source),
                    make_row("compass", _offsets_heading_source),
                    make_row("position", _offsets_position_source),
                    make_row("depth", _offsets_depth_source) });

        std::vector<std::vector<std::string>> subarrays;
        for (const auto& [target_id, subs] : _target_subarray_offsets)
            for (const auto& [subarray_id, pose] : subs)
                subarrays.push_back(make_row(target_id + " / " + subarray_id, pose));
        add_table("Subarray offsets", "target / subarray", std::move(subarrays));

        printer.register_section("System");
        printer.register_value("waterline_offset", _waterline_offset, "m");
        printer.register_string("position_motion_compensated",
                                _position_source_motion_compensated ? "true" : "false",
                                "position already re reference point");
        if (!_model_name.empty())
            printer.register_string("model", _model_name, "");
        if (!_transducer_configuration.empty())
            printer.register_string("configuration", _transducer_configuration, "");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS_NO_HASH__(SensorConfiguration)

    /// Cached binary hash: avoids re-serializing the entire object on every lookup.
    xxh::hash_t<64> binary_hash() const
    {
        if (!_cached_binary_hash.has_value())
        {
            xxh::hash3_state_t<64>               hash;
            boost::iostreams::stream<XXHashSink> stream(hash);
            this->to_stream(stream);
            stream.flush();
            _cached_binary_hash = hash.digest();
        }
        return *_cached_binary_hash;
    }
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

/**
 * @brief Boost hash function
 *
 * @param object object to hash
 * @return std::size_t
 */
inline std::size_t hash_value(const themachinethatgoesping::navigation::SensorConfiguration& object)
{
    return object.binary_hash();
}

} // namespace navigation
} // namespace themachinethatgoesping

template<>
struct std::hash<themachinethatgoesping::navigation::SensorConfiguration>
{
    std::size_t operator()(
        const themachinethatgoesping::navigation::SensorConfiguration& object) const
    {
        return object.binary_hash();
    }
};
