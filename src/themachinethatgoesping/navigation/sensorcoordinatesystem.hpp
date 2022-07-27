// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>
#include <cmath>
#include <exception>
#include <iostream>
#include <math.h>
#include <string>

#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "navdata.hpp"

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief A coordinate system that allows for specifying sensor offsets (e.g. gps antenna and motion
 * sensor) and target offsets (e.g. MBES) to derive the geolocation and attitude of the specified
 * targets
 *
 */
class SensorCoordinateSystem
{
    std::unordered_map<std::string, navdata::PositionalOffsets>
        _TargetOffsets; /// TargetId (position in vector) for each registered target_id

    navdata::PositionalOffsets _motion_sensor_offsets; /// Static Roll,Pitch,Yaw (installation) Offsets of Motionsensor 
    navdata::PositionalOffsets _compass_offsets; /// Static Yaw (installation) Offsets of CompassOffsets 
    navdata::PositionalOffsets _position_system_offsets; /// Static x,y,z (installation) Offsets of the PositionSystem 
    navdata::PositionalOffsets _depth_sensor_offsets;   /// Static xy,z (installation) Offsets of the depth sensor 
    // Static Position of Heave Sensor
    // Offsets _HeaveSensorOffsets;

  public:
    /**
     * @brief Construct a new, empty Sensor Coordinate System object
     * After construction: add sensor offsets and targets (offstes)
     * Then compute target positions for sensor data
     *
     */
    SensorCoordinateSystem() = default;

    // ----- compute_target_position -----
    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorDataLocal / this structure includes northing/easting but no zone or
     * hemisphere informatoin
     * @return navdata::GeoLocationLocal  / this structure includes northing/easting but no zone or
     * hemisphere informatoin
     */
    navdata::GeoLocationLocal compute_target_position(
        const std::string&              target_id,
        const navdata::SensorDataLocal& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorDataUTM / this structure includes northing/easting and utm zone or
     * hemisphere informatoin
     * @return navdata::GeoLocationUTM  / this structure includes northing/easting and utm zone or
     * hemisphere informatoin
     */
    navdata::GeoLocationUTM compute_target_position(
        const std::string&            target_id,
        const navdata::SensorDataUTM& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorDataLatLon / this structure includes latitude and longitude
     * informatoin
     * @return navdata::GeoLocationLatLon  / this structure includes latitude and longitude
     * informatoin
     */
    navdata::GeoLocationLatLon compute_target_position(
        const std::string&               target_id,
        const navdata::SensorDataLatLon& sensor_data) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorData / this structure includes no coordinate information
     * @return navdata::GeoLocationLocal  / this structure includes northing and east, which are set
     * relative to the sensor coordinate system center
     */
    navdata::GeoLocationLocal compute_target_position(const std::string&         target_id,
                                                      const navdata::SensorData& sensor_data) const;

    // ----- get/set target offsets -----
    /**
     * @brief register a target (e.g. MBES) with offsets to the sensor position system
     * 
     * @param target_id name of the target for reference
     * @param offsets mounting offsets of the target
     */
    void register_target(const std::string& target_id, const navdata::PositionalOffsets& offsets);
    /**
     * @brief register a target (e.g. MBES) with offsets to the sensor position system
     * 
     * @param target_id name of the target for reference
     * @param x x-offset of the target (in meters, positive foorward)
     * @param y y-offset of the target (in meters, positive starboard)
     * @param z z-offset of the target (in meters, positive down)
     * @param yaw yaw offset of the target (righthanded around the z-axis) (in degrees, 90° = east)
     * @param pitch pitch offset of the target (righthanded around the y-axis) (in degrees, positive = bow up)
     * @param roll roll offset of the target (righthanded around the x-axis) (in degrees, positive = port up)
     */
    void register_target(const std::string& target_id,
                    double             x,
                    double             y,
                    double             z,
                    double             yaw,
                    double             pitch,
                    double             roll);

    /**
     * @brief Get stored target offsets of a specified target
     * 
     * @param target_id name of the registered target
     * @return const navdata::PositionalOffsets& offsets of the target
     */
    const navdata::PositionalOffsets& get_target_offsets(const std::string& target_id) const;

    // ----- get/set sensor offsets -----
    /**
     * @brief Set the motion sensor offsets
     * 
     * @param yaw yaw offset of the motion sensor (righthanded around the z-axis) (in degrees, 90° = east)
     * @param pitch pitch offset of the motion sensor (righthanded around the y-axis) (in degrees, positive = bow up)
     * @param roll roll offset of the motion sensor (righthanded around the x-axis) (in degrees, positive = port up)
     */
    void set_motion_sensor_offsets(double yaw, double pitch, double roll);
    /**
     * @brief Set the motion sensor offsets
     * 
     * @param new_offsets offsets structure (only yaw, pitch and roll are used)
     */
    void set_motion_sensor_offsets(const navdata::PositionalOffsets& new_offsets);
    /**
     * @brief Get the motion sensor offsets
     * 
     * @return const navdata::PositionalOffsets& offsets of the motion sensor
     */
    navdata::PositionalOffsets get_motion_sensor_offsets() const;

    /**
     * @brief Set the compass offsets
     * 
     * @param yaw yaw offset of the compass (righthanded around the z-axis) (in degrees, 90° = east)
     */
    void                       set_compass_offsets(double yaw);

    /**
     * @brief Set the compass offsets
     * 
     * @param new_offsets offsets structure (only yaw is used)
     */
    void                       set_compass_offsets(const navdata::PositionalOffsets& new_offsets);

    /**
     * @brief Get the registered compass offsets
     * 
     * @return const navdata::PositionalOffsets& offsets of the compass
     */
    navdata::PositionalOffsets get_compass_offsets() const;

    /**
     * @brief Set the depth sensor offsets 
     * 
     * @param x x-offset of the depth sensor (in meters, positive foorward)
     * @param y y-offset of the depth sensor (in meters, positive starboard)
     * @param z z-offset of the depth sensor (in meters, positive down)
     */
    void set_depth_sensor_offsets(double x, double y, double z);

    /**
     * @brief Set the depth sensor offsets 
     * 
     * @param new_offsets offsets structure (only x, y and z are used)
     */
    void set_depth_sensor_offsets(const navdata::PositionalOffsets& new_offsets);

    /**
     * @brief Get the registered depth sensor offsets 
     * 
     * @return const navdata::PositionalOffsets& offsets of the depth sensor
     */
    navdata::PositionalOffsets get_depth_sensor_offsets() const;

    /**
     * @brief Set the position system offsets
     * 
     * @param x x-offset of the depth sensor (in meters, positive foorward)
     * @param y y-offset of the depth sensor (in meters, positive starboard)
     * @param z z-offset of the depth sensor (in meters, positive down)
     */
    void set_position_system_offsets(double x, double y, double z);

    /**
     * @brief Set the position system offsets
     * 
     * @param new_offsets offsets structure (only x, y and z are used)
     */
    void set_position_system_offsets(const navdata::PositionalOffsets& new_offsets);

    /**
     * @brief Get the registered position system offsets
     * 
     * @return const navdata::PositionalOffsets& offsets of the position system
     */
    navdata::PositionalOffsets get_position_system_offsets() const;

  private:
    // ----- helper functinos -----
    /**
     * @brief Compute the rotation of the sensor coordinate system (relative to the world reference coordinate system) using the sensor data and (rotation) offsets.
     * Note1: If compass_heading in SensorData is NAN, the imu_yaw is used (and compass_offsets are ignored)
     * Note2: if compass_heading is used the motion_sensor_offset yaw will be used to correct the motion_sensor_offset roll and pitch but will not be added to the heading 
     * 
     * @param sensor_data Sensor data object (used are: compass_heading, imu_yaw, imu_pitch, imu_roll)
     * @param compasss_offsets Offsets of the compass (used is only yaw offset)
     * @param motion_sensor_offsets Offsets of the IMU (used are yaw, pitch and roll), if compass_heading is used, yaw is used to correct pitch, and roll but not added to the heading
     * @return Eigen::Quaterniond Rotation of the sensor system compared to the world reference system
     */
    static Eigen::Quaterniond get_system_rotation_as_quat(
        const navdata::SensorData&        sensor_data,
        const navdata::PositionalOffsets& compasss_offsets,
        const navdata::PositionalOffsets& motion_sensor_offsets);
};

} // namespace navigation
} // namespace themachinethatgoesping
