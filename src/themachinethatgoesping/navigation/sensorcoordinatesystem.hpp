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
    std::vector<navdata::PositionalOffsets>
        _TargetOffsets; ///< Positional offsets of registered targets
    std::unordered_map<std::string, size_t>
        _TargetOffsetIDs; ///< TargetId (position in vector) for each registered target_id

    // Static Roll,Pitch,Yaw Offsets of Motionsensor Installation and Position of Motionsensor
    navdata::PositionalOffsets _motion_sensor_offsets;
    // Static Roll,Pitch,Yaw Offsets of Motionsensor Installation and Position of Motionsensor
    navdata::PositionalOffsets _compass_offsets;
    // Static Position of Positionsystem
    navdata::PositionalOffsets _position_system_offsets;
    // Static Position of Depth Sensor
    navdata::PositionalOffsets _depth_sensor_offsets;
    // Static Position of Heave Sensor
    // Offsets _HeaveSensorOffsets;

  public:
    /**
     * @brief Construct a new Sensor Coordinate System object
     *
     */
    SensorCoordinateSystem() = default;

    const navdata::PositionalOffsets& get_target_offsets(const std::string& target_id) const;
    const navdata::PositionalOffsets& get_target_offsets(size_t target_id) const;

    void set_target_offsets(const std::string&                target_id,
                            const navdata::PositionalOffsets& offsets);
    void set_target_offsets(const std::string& target_id,
                            double             x,
                            double             y,
                            double             z,
                            double             yaw,
                            double             pitch,
                            double             roll);

    // ----- compute_target_position -----
    navdata::GeoLocationLocal compute_target_position(const std::string&         target_id,
                                                      const navdata::SensorData& sensor_data) const;

    navdata::GeoLocationLocal compute_target_position(
        const std::string&              target_id,
        const navdata::SensorDataLocal& sensor_data) const;

    navdata::GeoLocationUTM compute_target_position(
        const std::string&            target_id,
        const navdata::SensorDataUTM& sensor_data) const;

    navdata::GeoLocationLatLon compute_target_position(
        const std::string&               target_id,
        const navdata::SensorDataLatLon& sensor_data) const;

    static Eigen::Quaterniond get_vessel_ypr_as_quat(
        const navdata::SensorData&        sensor_data,
        const navdata::PositionalOffsets& compasss_offsets,
        const navdata::PositionalOffsets& motion_sensor_offsets)
    {

        if (std::isnan(sensor_data.compass_heading))
        {
            // if compass_heading is nan, the imu_yaw will be used as heading
            // convert offset to quaternion
            Eigen::Quaternion<double> imu_offset_quat =
                tools::rotationfunctions::quaternion_from_ypr(motion_sensor_offsets.yaw,
                                                              motion_sensor_offsets.pitch,
                                                              motion_sensor_offsets.roll,
                                                              true);

            // convert sensor yaw,pitch,roll to quaternion
            auto imu_sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
                sensor_data.imu_yaw, sensor_data.imu_pitch, sensor_data.imu_roll, true);

            // return sensor yaw, pitch, roll corrected for (rotated by) the sensor offsets
            // TODO: check if the order is correct
            auto vessel_quat = imu_sensor_quat * imu_offset_quat.inverse();
            vessel_quat.normalize();
            return vessel_quat;
        }
        else
        {
            // if compass_heading is nan, the imu_yaw will be used as heading
            // convert offset to quaternion
            Eigen::Quaternion<double> imu_offset_quat =
                tools::rotationfunctions::quaternion_from_ypr(motion_sensor_offsets.yaw,
                                                              motion_sensor_offsets.pitch,
                                                              motion_sensor_offsets.roll,
                                                              true);
                                                              

            // convert sensor pitch,roll to quaternion (ignore reported yaw)
            auto imu_sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
                0.0, sensor_data.imu_pitch, sensor_data.imu_roll, true);

            // compute roll and pitch using the imu_offsets (including yaw offset)
            // TODO: check if the order is correct
            auto pr_quat = imu_sensor_quat * imu_offset_quat.inverse() ;
            pr_quat.normalize();

            // compute sensor quat using the correct pitch and roll (ignore yaw)
            auto ypr = tools::rotationfunctions::ypr_from_quaternion(pr_quat, false);
            auto sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
                0., ypr[1], ypr[2], false);

            // rotate sensor quat using compass_heading
            double heading = sensor_data.compass_heading - compasss_offsets.yaw;
            auto   compass_quat =
                tools::rotationfunctions::quaternion_from_ypr(heading, 0.0, 0.0, true);

            auto vessel_quat = compass_quat * sensor_quat;
            vessel_quat.normalize();
            return vessel_quat;
        }
    }

    //------------------------------------- Target offsets(e.g Offsets of Multibeam)---------------

    void set_motion_sensor_offsets(double yaw, double pitch, double roll)
    {
        _motion_sensor_offsets = navdata::PositionalOffsets(0.0, 0.0, 0.0, yaw, pitch, roll);
    }
    void set_motion_sensor_offsets(const navdata::PositionalOffsets& new_offsets)
    {
        _motion_sensor_offsets = new_offsets;
    }

    navdata::PositionalOffsets get_motion_sensor_offsets() const { return _motion_sensor_offsets; }

    void set_compass_offsets(double yaw)
    {
        _compass_offsets = navdata::PositionalOffsets(0.0, 0.0, 0.0, yaw, 0.0, 0.0);
        // Offsets(0.0, 0.0, 0.0, yaw, 0.0, 0.0, Offsets::t_angleOffsetType::additive);
    }
    void set_compass_offsets(const navdata::PositionalOffsets& new_offsets)
    {
        _compass_offsets = new_offsets;
    }
    navdata::PositionalOffsets get_compass_offsets() const { return _compass_offsets; }

    void set_depth_sensor_offsets(double x, double y, double z)
    {
        _depth_sensor_offsets = navdata::PositionalOffsets(x, y, z, 0.0, 0.0, 0.0);
    }
    void set_depth_sensor_offsets(const navdata::PositionalOffsets& new_offsets)
    {
        _depth_sensor_offsets = new_offsets;
    }
    navdata::PositionalOffsets get_depth_sensor_offsets() const { return _depth_sensor_offsets; }

    //    void set_heaveSensorOffsets(double x, double y, double z);
    //    void set_heaveSensorOffsets(const Offsets& new_offsets);
    //    Offsets get_heaveSensorOffsets() const;

    void set_position_system_offsets(double x, double y, double z)
    {
        _position_system_offsets = navdata::PositionalOffsets(x, y, z, 0.0, 0.0, 0.0);
    }
    void set_position_system_offsets(const navdata::PositionalOffsets& new_offsets)
    {
        _position_system_offsets = new_offsets;
    }
    navdata::PositionalOffsets get_position_system_offsets() const
    {
        return _position_system_offsets;
    }
};

} // namespace navigation
} // namespace themachinethatgoesping
