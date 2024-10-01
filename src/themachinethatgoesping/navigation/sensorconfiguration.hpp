// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensorconfiguration.doc.hpp"
#include <cmath>
#include <exception>
#include <iostream>
#include <math.h>
#include <string>
#include <string_view>

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "datastructures.hpp"

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
    std::map<std::string, datastructures::PositionalOffsets>
        _target_offsets; ///< TargetId (position in vector) for each registered target_id

    datastructures::PositionalOffsets
        _offsets_attitude_source; ///< Static Roll,Pitch,Yaw (installation) offsets of the attitude
                                  ///< sensor
    datastructures::PositionalOffsets
        _offsets_heading_source; ///< Static Yaw (installation) Offsets of CompassOffsets
    datastructures::PositionalOffsets
        _offsets_position_source; ///< Static x,y,z (installation) Offsets of the PositionSystem
    datastructures::PositionalOffsets
        _offsets_depth_source; ///< Static xy,z (installation) Offsets of the depth sensor
    // Static Position of Heave Sensor
    // Offsets _HeaveSensorOffsets;

    float _waterline_offset =
        0.0; ///< Waterline offset (negative waterline offset means that z=0 is below the waterline

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
                    const datastructures::PositionalOffsets& target_offsets);

    /**
     * @brief add targets (e.g. MBES) with given target_ids and offsets to the sensor position
     * system
     *
     * @param targets map<target_id, target_offsets> of target offsets
     */
    void add_targets(const std::map<std::string, datastructures::PositionalOffsets>& targets);

    /**
     * @brief Get stored target offsets of a specified target
     *
     * @param target_id name of the registered target
     * @return const datastructures::PositionalOffsets& offsets of the target
     */
    const datastructures::PositionalOffsets& get_target(const std::string& target_id) const;

    /**
     * @brief Get the map of stored target offsets objects
     *
     * @return const std::unordered_map<std::string, datastructures::PositionalOffsets>&
     */
    const std::map<std::string, datastructures::PositionalOffsets>& get_targets() const;

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

    // ----- get/set sensor offsets -----
    /**
     * @brief Set the attitude sensor offsets
     *
     * @param sensor_offsets offsets structure (only yaw, pitch and roll are used)
     */
    void set_attitude_source(const datastructures::PositionalOffsets& sensor_offsets);

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
     * @return const datastructures::PositionalOffsets& offsets of the attitude sensor
     */
    datastructures::PositionalOffsets get_attitude_source() const;

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
    void set_heading_source(const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief Get the registered compass offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the compass
     */
    datastructures::PositionalOffsets get_heading_source() const;

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
    void set_depth_source(const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief Get the registered depth sensor offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the depth sensor
     */
    datastructures::PositionalOffsets get_depth_source() const;

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
    void set_position_source(const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief Get the registered position system offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the position system
     */
    datastructures::PositionalOffsets get_position_source() const;

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
     * @return Eigen::Quaternion<float> Rotation of the sensor system compared to the world
     * reference system
     */
    static Eigen::Quaternion<float> get_system_rotation_as_quat(
        const datastructures::Sensordata&        sensor_data,
        const datastructures::PositionalOffsets& offsets_heading_source,
        const datastructures::PositionalOffsets& offsets_attitude_source);

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
        using datastructures::PositionalOffsets;
        using tools::classhelper::stream::container_from_stream;

        SensorConfiguration obj;

        unsigned int num_targets;
        is.read(reinterpret_cast<char*>(&num_targets), sizeof(num_targets));
        while (num_targets--)
        {
            std::string       target_id               = container_from_stream<std::string>(is);
            PositionalOffsets target_offsets          = PositionalOffsets::from_stream(is);
            obj._target_offsets[std::move(target_id)] = std::move(target_offsets);
        }

        obj._offsets_attitude_source = PositionalOffsets::from_stream(is);
        obj._offsets_heading_source  = PositionalOffsets::from_stream(is);
        obj._offsets_position_source = PositionalOffsets::from_stream(is);
        obj._offsets_depth_source    = PositionalOffsets::from_stream(is);
        is.read(reinterpret_cast<char*>(&obj._waterline_offset), sizeof(obj._waterline_offset));

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
               _waterline_offset == other._waterline_offset;
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
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer("SensorConfiguration", float_precision, superscript_exponents);

        for (const auto& [target_id, target_offsets] : _target_offsets)
        {
            printer.register_section("Target offsets \"" + target_id + "\"");
            printer.append(target_offsets.__printer__(float_precision, superscript_exponents));
        }

        printer.register_section("Attitude sensor offsets");
        printer.append(_offsets_attitude_source.__printer__(float_precision, superscript_exponents));

        printer.register_section("Compass offsets");
        printer.append(_offsets_heading_source.__printer__(float_precision, superscript_exponents));

        printer.register_section("Position system offsets");
        printer.append(_offsets_position_source.__printer__(float_precision, superscript_exponents));

        printer.register_section("Depth sensor offsets");
        printer.append(_offsets_depth_source.__printer__(float_precision, superscript_exponents));

        printer.register_section("waterline offsets");
        printer.register_value("Waterline offset", _waterline_offset, "m");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorConfiguration)
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
