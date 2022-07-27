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

    const navdata::PositionalOffsets& get_targe_offsets(const std::string& target_id) const
    {
        return _TargetOffsets.at(
            _TargetOffsetIDs.at(target_id)); // throws std::out_of_range if not found
    }

    navdata::GeoLocationLocal compute_position(const navdata::SensorData& sensor_data,
                                               const std::string&         target_id) const
    {
        navdata::GeoLocationLocal location;

        // first get the current roation of the vessel
        auto vessel_quat = get_vesselQuat(sensor_data, _compass_offsets, _motion_sensor_offsets);

        // convert x,y,z offsets to quaternions
        auto depth_sensor_xyz_quat   = _depth_sensor_offsets.xyz_as_quaternion();
        auto positionSystem_xyz_quat = _position_system_offsets.xyz_as_quaternion();

        // convert target to quaternion

        auto target_offsets  = get_targe_offsets(target_id);
        auto target_xyz_quat = target_offsets.xyz_as_quaternion();
        auto target_ypr_quat = target_offsets.ypr_as_quaternion();

        // get rotated positions
        auto target_xyz = tools::rotationfunctions::rotateXYZ(vessel_quat, target_xyz_quat);
        auto depth_sensor_xyz =
            tools::rotationfunctions::rotateXYZ(vessel_quat, depth_sensor_xyz_quat);
        auto positionSystem_xyz =
            tools::rotationfunctions::rotateXYZ(vessel_quat, positionSystem_xyz_quat);

        // compute target depth
        location.z =
            target_xyz[2] - depth_sensor_xyz[2] + sensor_data.gps_z - sensor_data.heave_heave;

        // compute target ypr
        auto target_quat = vessel_quat * target_ypr_quat;
        auto ypr         = tools::rotationfunctions::ypr_from_quaternion(target_quat);
        location.yaw     = ypr[0];
        location.pitch   = ypr[1];
        location.roll    = ypr[2];

        // coompute target xy
        location.northing = target_xyz[0] - positionSystem_xyz[0];
        location.easting  = target_xyz[1] - positionSystem_xyz[1];

        return location;
    }

    navdata::GeoLocationLocal compute_position(const navdata::SensorDataLocal& sensor_data,
                                               const std::string&              target_id) const
    {
        auto position = compute_position(navdata::SensorData(sensor_data), target_id);

        // coompute target xy
        position.northing += sensor_data.gps_northing;
        position.easting += sensor_data.gps_easting;

        return position;
    }
    
    navdata::GeoLocationUTM compute_position(const navdata::SensorDataUTM& sensor_data,
                                               const std::string&              target_id) const
    {
        auto position = compute_position(navdata::SensorDataLocal(sensor_data), target_id);

        return navdata::GeoLocationUTM(position,sensor_data.gps_zone,sensor_data.gps_northern_hemisphere);
    }

    navdata::GeoLocationLatLon compute_position(const navdata::SensorDataLatLon& sensor_data,
                                               const std::string&              target_id) const
    {        
        auto position = compute_position(navdata::SensorData(sensor_data), target_id);                        

        double distance, heading;
        std::tie(distance, heading) = compute_targetPosSysDistanceAndAzimuth(position.northing, position.easting);

        double                  target_lat, target_lon;
        if (std::isnan(heading))
        {
            // this happens if there is no offset between the antenna and the target
            if (distance == 0){
                target_lat = sensor_data.gps_latitude;
                target_lon = sensor_data.gps_longitude;
            }

            // this should never happen
            else
                throw(std::runtime_error(
                    "vessel::get_targetLatLon[Fatal Error]: [get_targetPosSysDistanceAndAzimuth] "
                    "heading is nan but distance is not 0! (this should not happen)"));
        }
        else
        {
        GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                     GeographicLib::Constants::WGS84_f());
        geod.Direct(sensor_data.gps_latitude, sensor_data.gps_longitude, heading, distance, target_lat, target_lon);

        }

        // GeoPositionLocal is implicitly converted to GeoPosition when calling this function
        return navdata::GeoLocationLatLon(position,target_lat,target_lon);
    }

    //------------------------------------- get vessel position -----------------------------------

    std::pair<double, double> compute_targetPosSysDistanceAndAzimuth(double northing, double easting,
                                                                 bool radians = false) const
                                                                 {
                                                                    double distance =
            std::sqrt(northing * northing + easting * easting);

        // north 0°/360°, east 90°, south 180°, west 270°
        double azimuth = NAN; // only when x and y are 0

        if (northing == 0)
        {
            if (easting < 0)
                azimuth = 1.5 * M_PI; // 270°
            else if (easting > 0)
                azimuth = 0.5 * M_PI; // 90°
            // else azimuth = NAN;
        }
        else if (easting == 0)
        {
            if (northing < 0)
                azimuth = M_PI; // 180°
            else if (northing > 0)
                azimuth = 0;
        }
        else
        {
            azimuth = std::atan2(easting, northing);
        }

        // move azimuth into 0-2pi range
        static const double M_2PI = 2. * M_PI;
        while (azimuth < 0)
            azimuth += M_2PI;
        while (azimuth > M_2PI)
            azimuth -= M_2PI;

        if (!radians)
            azimuth *= 180 / M_PI;

        return std::make_pair(distance, azimuth);
                                                                 }


    static Eigen::Quaterniond get_vesselQuat(
        const navdata::SensorData&        sensor_data,
        const navdata::PositionalOffsets& compasss_offsets,
        const navdata::PositionalOffsets& motion_sensor_offsets)
    {
        /* first do yaw rotation */
        double heading             = sensor_data.compass_heading;
        bool   use_motionSensorYaw = false;

        if (std::isnan(heading))
        {
            use_motionSensorYaw = true;
            heading             = sensor_data.imu_yaw;
        }
        else
        {
            // yaw is applied first and therefore
            // additive
            heading = heading - compasss_offsets.yaw;
        }

        Eigen::Quaternion<double> offset_quat;
        double                    yaw_offset = 0;
        if (use_motionSensorYaw)
            yaw_offset = motion_sensor_offsets.yaw;

        offset_quat = tools::rotationfunctions::quaternion_from_ypr(
            yaw_offset, motion_sensor_offsets.pitch, motion_sensor_offsets.roll, true);

        if (use_motionSensorYaw)
        {
            auto sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
                sensor_data.imu_yaw, sensor_data.imu_pitch, sensor_data.imu_roll, true);
            sensor_quat.normalize();
            offset_quat.normalize();

            return offset_quat.inverse() * sensor_quat;
        }
        else
        {
            auto sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
                0.0, sensor_data.imu_pitch, sensor_data.imu_roll, true);
            auto compass_quat =
                tools::rotationfunctions::quaternion_from_ypr(heading, 0.0, 0.0, true);

            sensor_quat.normalize();
            offset_quat.normalize();
            compass_quat.normalize();
            auto vessel_quat = compass_quat * offset_quat.inverse() * sensor_quat;
            vessel_quat.normalize();
            return vessel_quat;
        }
    }
    
    //------------------------------------- Target offsets(e.g Offsets of Multibeam)---------------
    void set_targetOffsets(const std::string& target_id,
                           double             x,
                           double             y,
                           double             z,
                           double             yaw,
                           double             pitch,
                           double             roll)
    {
        set_targetOffsets(target_id, navdata::PositionalOffsets(x, y, z, yaw, pitch, roll));
    }
    void set_targetOffsets(const std::string&                target_id,
                           const navdata::PositionalOffsets& new_offsets)
    {

        auto map_it = _TargetOffsetIDs.find(target_id);
        if (map_it == _TargetOffsetIDs.end())
        {
            _TargetOffsets.push_back(new_offsets);
            _TargetOffsetIDs[target_id] = _TargetOffsets.size() - 1;
        }
        else
        {
            _TargetOffsets[map_it->second] = new_offsets;
        }
    }
    navdata::PositionalOffsets get_targetOffsets(const std::string& target_id) const
    {
        auto map_it = _TargetOffsetIDs.find(target_id);
        if (map_it == _TargetOffsetIDs.end())
        {
            std::stringstream s;
            s << "ERROR[SensorCoordinateSystem::get_target_offsets]: Could not find target "
                 "target_id: "
              << target_id << "!";
            throw std::out_of_range(s.str());
        }
        return _TargetOffsets[map_it->second];
    }

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
