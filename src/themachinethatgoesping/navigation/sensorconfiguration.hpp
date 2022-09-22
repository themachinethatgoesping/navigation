// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <cmath>
#include <exception>
#include <iostream>
#include <math.h>
#include <string>

#include <bitsery/ext/std_map.h>

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
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
    std::unordered_map<std::string, datastructures::PositionalOffsets>
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

  public:
    /**
     * @brief Construct a new, empty Sensor Coordinate System object
     * After construction: add sensor offsets and targets (offsets)
     * Then compute target positions for sensor data
     *
     */
    SensorConfiguration() = default;

    // ----- compute_target_position -----
    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorDataLatLon / this structure includes latitude and longitude
     * information
     * @return datastructures::GeoLocationLatLon  / this structure includes latitude and longitude
     * information
     */
    datastructures::GeoLocationLatLon compute_target_position(
        const std::string&                      target_id,
        const datastructures::SensorDataLatLon& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorDataUTM / this structure includes northing/easting and utm zone or
     * hemisphere information
     * @return datastructures::GeoLocationUTM  / this structure includes northing/easting and utm
     * zone or hemisphere information
     */
    datastructures::GeoLocationUTM compute_target_position(
        const std::string&                   target_id,
        const datastructures::SensorDataUTM& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorDataLocal / this structure includes northing/easting but no zone or
     * hemisphere information
     * @return datastructures::GeoLocationLocal  / this structure includes northing/easting but no
     * zone or hemisphere information
     */
    datastructures::GeoLocationLocal compute_target_position(
        const std::string&                     target_id,
        const datastructures::SensorDataLocal& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorData / this structure includes no coordinate information
     * @return datastructures::GeoLocationLocal  / this structure includes northing and east, which
     * are set relative to the sensor coordinate system center
     */
    datastructures::GeoLocationLocal compute_target_position(
        const std::string&                target_id,
        const datastructures::SensorData& sensor_data) const;

    // ----- get/set target offsets -----
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
                    double             x,
                    double             y,
                    double             z,
                    double             yaw,
                    double             pitch,
                    double             roll);

    /**
     * @brief add a target (e.g. MBES) with offsets to the sensor position system
     *
     * @param target_id name of the target for reference
     * @param target_offsets mounting offsets of the target
     */
    void add_target(const std::string&                       target_id,
                    const datastructures::PositionalOffsets& target_offsets);

    /**
     * @brief Get stored target offsets of a specified target
     *
     * @param target_id name of the registered target
     * @return const datastructures::PositionalOffsets& offsets of the target
     */
    const datastructures::PositionalOffsets& get_offsets_target(const std::string& target_id) const;

    // ----- get/set sensor offsets -----
    /**
     * @brief Set the attitude sensor offsets
     *
     * @param sensor_offsets offsets structure (only yaw, pitch and roll are used)
     */
    void set_offsets_attitude_source(const datastructures::PositionalOffsets& sensor_offsets);

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
    void set_offsets_attitude_source(double yaw, double pitch, double roll);

    /**
     * @brief Get the attitude sensor offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the attitude sensor
     */
    datastructures::PositionalOffsets get_offsets_attitude_source() const;

    /**
     * @brief Set the compass offsets
     *
     * @param yaw yaw offset of the compass (right-handed around the z-axis) (in degrees, 90° =
     * east)
     */
    void set_offsets_heading_source(double yaw);

    /**
     * @brief Set the compass offsets
     *
     * @param sensor_offsets offsets structure (only yaw is used)
     */
    void set_offsets_heading_source(const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief Get the registered compass offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the compass
     */
    datastructures::PositionalOffsets get_offsets_heading_source() const;

    /**
     * @brief Set the depth sensor offsets
     *
     * @param x x-offset of the depth sensor (in meters, positive forward)
     * @param y y-offset of the depth sensor (in meters, positive starboard)
     * @param z z-offset of the depth sensor (in meters, positive down)
     */
    void set_offsets_depth_source(double x, double y, double z);

    /**
     * @brief Set the depth sensor offsets
     *
     * @param sensor_offsets offsets structure (only x, y and z are used)
     */
    void set_offsets_depth_source(const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief Get the registered depth sensor offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the depth sensor
     */
    datastructures::PositionalOffsets get_offsets_depth_source() const;

    /**
     * @brief Set the position system offsets
     *
     * @param x x-offset of the depth sensor (in meters, positive forward)
     * @param y y-offset of the depth sensor (in meters, positive starboard)
     * @param z z-offset of the depth sensor (in meters, positive down)
     */
    void set_offsets_position_source(double x, double y, double z);

    /**
     * @brief Set the position system offsets
     *
     * @param sensor_offsets offsets structure (only x, y and z are used)
     */
    void set_offsets_position_source(const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief Get the registered position system offsets
     *
     * @return const datastructures::PositionalOffsets& offsets of the position system
     */
    datastructures::PositionalOffsets get_offsets_position_source() const;

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
     * @return Eigen::Quaterniond Rotation of the sensor system compared to the world reference
     * system
     */
    static Eigen::Quaterniond get_system_rotation_as_quat(
        const datastructures::SensorData&        sensor_data,
        const datastructures::PositionalOffsets& offsets_heading_source,
        const datastructures::PositionalOffsets& offsets_attitude_source);

    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        // serialize map of PositionOffsets
        s.ext(_target_offsets,
              bitsery::ext::StdMap{ 100 },
              [](S& s, std::string& key, datastructures::PositionalOffsets& value) {
                  s.container1b(key, 100);
                  s.object(value);
              });
        s.object(_offsets_attitude_source);
        s.object(_offsets_heading_source);
        s.object(_offsets_position_source);
        s.object(_offsets_depth_source);
    }

  public:
    bool operator==(const SensorConfiguration& other) const
    {

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
               _offsets_depth_source == other._offsets_depth_source;
    }
    bool operator!=(const SensorConfiguration& other) const { return !(*this == other); }

    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("SensorConfiguration", float_precision);

        for (const auto& [target_id, target_offsets] : _target_offsets)
        {
            printer.register_section("Target offsets \"" + target_id + "\"");
            printer.append(target_offsets.__printer__(float_precision));
        }

        printer.register_section("Attitude sensor offsets");
        printer.append(_offsets_attitude_source.__printer__(float_precision));

        printer.register_section("Compass offsets");
        printer.append(_offsets_heading_source.__printer__(float_precision));

        printer.register_section("Position system offsets");
        printer.append(_offsets_position_source.__printer__(float_precision));

        printer.register_section("Depth sensor offsets");
        printer.append(_offsets_depth_source.__printer__(float_precision));

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorConfiguration)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace navigation
} // namespace themachinethatgoesping
