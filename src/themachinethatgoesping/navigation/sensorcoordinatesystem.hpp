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
    std::vector<navdata::PositionalOffsets> _TargetOffsets; ///< Positional offsets of registered targets
    std::unordered_map<std::string, size_t>
        _TargetOffsetIDs; ///< TargetId (position in vector) for each registered key

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

    navdata::SensorDataLocal _sensor_data; ///< Local sensor data

    bool   _Latlon_set = false;
    double _Lat;
    double _Lon;

    double _X     = 0; // Position Y in meters
    double _Y     = 0; // Position X in meters

    double _rotation_point_x = 0;
    double _rotation_point_y = 0;
    double _rotation_point_z = 0;

  public:
    SensorCoordinateSystem() = default;

    //------------------------------------- get vessel position -----------------------------------
    /**
     * @brief get_targetDepth: Get the depth of the target including depth sensor values and heave
     * including motion correction)
     * @param key: Name of the target
     * @return return depth (world coordinates)
     */
    double get_targetDepth(const std::string& key) const
    {
        auto map_it = _TargetOffsetIDs.find(key);
        if (map_it == _TargetOffsetIDs.end())
        {
            std::stringstream s;
            s << "ERROR[SensorCoordinateSystem::get_targetDepth]: Could not find target key: "
              << key << "!";
            throw std::out_of_range(s.str());
        }

        const auto& target_offset = _TargetOffsets[map_it->second];

        // vessel quat is negative rotation quat because rotation point is the center of the
        // rotation
        auto target_xyz_quat =
            tools::rotationfunctions::getQuaterniondfromVector(target_offset.x - _rotation_point_x,
                                                               target_offset.y - _rotation_point_y,
                                                               target_offset.z - _rotation_point_z);

        // distance between the rotation point and the depth sensor quat
        auto depthSensor_xyz_quat = tools::rotationfunctions::getQuaterniondfromVector(
            _depth_sensor_offsets.x - _rotation_point_x,
            _depth_sensor_offsets.y - _rotation_point_y,
            _depth_sensor_offsets.z - _rotation_point_z);

        auto vessel_quat = get_vesselQuat(); // current rotation of vessel
        auto target_xyz  = tools::rotationfunctions::rotateXYZ(vessel_quat, target_xyz_quat);
        auto depthSensor_xyz =
            tools::rotationfunctions::rotateXYZ(vessel_quat, depthSensor_xyz_quat);

        //_Z is depth sensor depth
        //_Heave is defined as positive up
        // difference between vessel and depth sensor z
        return target_xyz[2] - depthSensor_xyz[2] + _sensor_data.gps_z - _sensor_data.heave_heave;
    }

    /**
     * @brief get_targetXY: Get the depth of the target including depth sensor values and heave
     * including motion correction)
     * @param key: Name of the target
     * @param use_VesselXY: Include the _X and _Y coordinates from the vessel (or not)
     * @return return x,y coordinates in meters (x=northing,y=easting) (relative to _X,_Y from
     * position system, includtion motion and depth corrections)
     */
    std::pair<double, double> get_targetXY(const std::string& key, bool use_VesselXY) const
    {
        auto map_it = _TargetOffsetIDs.find(key);
        if (map_it == _TargetOffsetIDs.end())
        {
            std::stringstream s;
            s << "ERROR[SensorCoordinateSystem::get_targetXY]: Could not find target key: " << key
              << "!";
            throw std::out_of_range(s.str());
        }

        const auto& target_offset = _TargetOffsets[map_it->second];

        // vessel quat is negative rotation quat because rotation point is the center of the
        // rotation
        auto target_xyz_quat =
            tools::rotationfunctions::getQuaterniondfromVector(target_offset.x - _rotation_point_x,
                                                               target_offset.y - _rotation_point_y,
                                                               target_offset.z - _rotation_point_z);

        // distance between the rotation point and the depth sensor quat
        auto positionSystem_xyz_quat = tools::rotationfunctions::getQuaterniondfromVector(
            _position_system_offsets.x - _rotation_point_x,
            _position_system_offsets.y - _rotation_point_y,
            _position_system_offsets.z - _rotation_point_z);

        auto vessel_quat = get_vesselQuat(); // current rotation of vessel
        auto target_xyz  = tools::rotationfunctions::rotateXYZ(vessel_quat, target_xyz_quat);
        auto positionSystem_xyz =
            tools::rotationfunctions::rotateXYZ(vessel_quat, positionSystem_xyz_quat);

        if (use_VesselXY)
        {
            positionSystem_xyz[0] += _X;
            positionSystem_xyz[1] += _Y;
        }

        return std::make_pair(target_xyz[0] - positionSystem_xyz[0],
                              target_xyz[1] - positionSystem_xyz[1]);
    }

    /**
     * @brief get_targetPosSysDistanceAndAzimuth: Get the target distance and azimuth (0° Noth, 90°
     * East) of the Position system towards the target
     * @param key: Name of the target
     * @param radians: if true will output heading as radians (otherwise degrees)
     * @return return distance,azimuth (0° Noth, 90° East) coordinates in meters,° (relative to the
     * position system, includtion motion and depth corrections)
     */
    std::pair<double, double> get_targetPosSysDistanceAndAzimuth(const std::string& key,
                                                                 bool               radians) const
    {
        auto xy = get_targetXY(key, false);

        double distance =
            std::sqrt(std::get<0>(xy) * std::get<0>(xy) + std::get<1>(xy) * std::get<1>(xy));

        // north 0°/360°, east 90°, south 180°, west 270°
        double azimuth = NAN; // only when x and y are 0

        if (std::get<0>(xy) == 0)
        {
            if (std::get<1>(xy) < 0)
                azimuth = 1.5 * M_PI; // 270°
            else if (std::get<1>(xy) > 0)
                azimuth = 0.5 * M_PI; // 90°
            // else azimuth = NAN;
        }
        else if (std::get<1>(xy) == 0)
        {
            if (std::get<0>(xy) < 0)
                azimuth = M_PI; // 180°
            else if (std::get<0>(xy) > 0)
                azimuth = 0;
        }
        else
        {
            azimuth = std::atan2(std::get<1>(xy), std::get<0>(xy));
        }

        while (azimuth < 0)
            azimuth += 2 * M_PI;
        while (azimuth > 2 * M_PI)
            azimuth -= 2 * M_PI;

        if (!radians)
            azimuth *= 180 / M_PI;

        return std::make_pair(distance, azimuth);
    }

    /**
     * @brief get_targetLatLon: Get the lat lon position of the target using all offsets and the
     * position from the position system
     * @param key: Name of the target
     * @return return latitude and longitude of the target in °
     */
    std::pair<double, double> get_targetLatLon(const std::string& key) const
    {
        double distance, heading;
        std::tie(distance, heading) = get_targetPosSysDistanceAndAzimuth(key, false);

        if (std::isnan(heading))
        {
            // this happens if there is no offset between the antenna and the target
            if (distance == 0)
                return std::make_pair(_Lat, _Lon);

            // this should never happen
            else
                throw(std::runtime_error(
                    "vessel::get_targetLatLon[Fatal Error]: [get_targetPosSysDistanceAndAzimuth] "
                    "heading is nan but distance is not 0! (this should not happen)"));
        }

        double                  target_lat, target_lon;
        GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                     GeographicLib::Constants::WGS84_f());
        geod.Direct(_Lat, _Lon, heading, distance, target_lat, target_lon);

        return std::make_pair(target_lat, target_lon);
    }

    /**
     * @brief get_vesselDepth: Get the depth of the vessel including depth sensor values and heave
     * including motion correction)
     * @return depth of the vessel point
     */
    double get_vesselDepth() const
    {

        auto vessel_quat = get_vesselQuat(); // current rotation of vessel

        // vessel quat is negative rotation quat because rotation point is the center of the
        // rotation
        auto vessel_xyz_quat = tools::rotationfunctions::getQuaterniondfromVector(
            -_rotation_point_x, -_rotation_point_y, -_rotation_point_z);

        // distance between the rotation point and the depth sensor quat
        auto depthSensor_xyz_quat = tools::rotationfunctions::getQuaterniondfromVector(
            _depth_sensor_offsets.x - _rotation_point_x,
            _depth_sensor_offsets.y - _rotation_point_y,
            _depth_sensor_offsets.z - _rotation_point_z);

        auto vessel_xyz = tools::rotationfunctions::rotateXYZ(vessel_quat, vessel_xyz_quat);
        auto depthSensor_xyz =
            tools::rotationfunctions::rotateXYZ(vessel_quat, depthSensor_xyz_quat);

        //_Z is depth sensor depth
        //_Heave is defined as positive up
        // difference between vessel and depth sensor z
        return vessel_xyz[2] - depthSensor_xyz[2] + _sensor_data.gps_z - _sensor_data.heave_heave;
    }

    Eigen::Quaterniond get_vesselQuat() const
    {
        /* first do yaw rotation */
        double heading = _sensor_data.compass_heading;
        bool use_motionSensorYaw = false;

        if (std::isnan(heading))
        {
            use_motionSensorYaw = true;
            heading = _sensor_data.imu_yaw;
        }
        else
        {
            // yaw is applied first and therefore
            // additive
            heading = heading - _compass_offsets.yaw;
        }

        Eigen::Quaternion<double> offset_quat;
        double                    yaw_offset = 0;
        if (use_motionSensorYaw)
            yaw_offset = _motion_sensor_offsets.yaw;

        offset_quat = tools::rotationfunctions::quaternion_from_ypr(
            yaw_offset, _motion_sensor_offsets.pitch, _motion_sensor_offsets.roll, true);

        if (use_motionSensorYaw)
        {

            auto sensor_quat =
                tools::rotationfunctions::quaternion_from_ypr(_sensor_data.imu_yaw, _sensor_data.imu_pitch, _sensor_data.imu_roll, true);
            sensor_quat.normalize();
            offset_quat.normalize();

            return offset_quat.inverse() * sensor_quat;
        }
        else
        {

            auto sensor_quat =
                tools::rotationfunctions::quaternion_from_ypr(0.0, _sensor_data.imu_pitch, _sensor_data.imu_roll, true);
            auto compass_quat =
                tools::rotationfunctions::quaternion_from_ypr(heading, 0.0, 0.0, true);

            sensor_quat.normalize();
            offset_quat.normalize();
            compass_quat.normalize();
            return compass_quat * offset_quat.inverse() * sensor_quat;
        }
    }

    std::tuple<double, double, double> get_targetYPR(const std::string& key, bool radians) const
    {
        auto ypr =
            tools::rotationfunctions::ypr_from_quaternion(get_targetYPR_as_Quat(key), !radians);

        return std::make_tuple(ypr[0], ypr[1], ypr[2]);
    }

    Eigen::Quaterniond get_targetYPR_as_Quat(const std::string& key) const
    {
        auto map_it = _TargetOffsetIDs.find(key);
        if (map_it == _TargetOffsetIDs.end())
        {
            std::stringstream s;
            s << "ERROR[SensorCoordinateSystem::get_target_offsets]: Could not find target key: "
              << key << "!";
            throw std::out_of_range(s.str());
        }

        const auto& target_offset = _TargetOffsets[map_it->second];

        Eigen::Quaternion<double> target_quat;
        target_quat = tools::rotationfunctions::quaternion_from_ypr(
            target_offset.yaw, target_offset.pitch, target_offset.roll, true);

        auto vessel_quat = get_vesselQuat();

        vessel_quat.normalize();
        target_quat.normalize();

        return vessel_quat * target_quat;
    }

    std::tuple<double, double, double> get_vesselYPR(bool radians) const
    {
        auto ypr = tools::rotationfunctions::ypr_from_quaternion(get_vesselQuat(), !radians);

        return std::make_tuple(ypr[0], ypr[1], ypr[2]);
    }

    //------------------------------------- get sensor information --------------------------------
    void set_positionSystemLatLon(double lat, double lon)
    {
        _Latlon_set = true;
        _Lat        = lat;
        _Lon        = lon;
    }
    void set_positionSystemXY(double X, double Y)
    {
        _Latlon_set = false;
        _X          = X;
        _Y          = Y;
    }

    void set_sensor_data(const navdata::SensorDataLocal& sensor_data)
    {
        _sensor_data = sensor_data;
    }

    navdata::SensorDataLocal get_sensor_data() const
    {
        return _sensor_data;
    }

    //------------------------------------- Rotation point offsets --------------------------------
    void set_rotationPoint(double x, double y, double z)
    {
        _rotation_point_x = x;
        _rotation_point_y = y;
        _rotation_point_z = z;
    }
    void set_rotationPointZ(double z) { _rotation_point_z = z; }
    void set_vesselPointWaterlineOffset(double vesselPointHeight)
    {
        _rotation_point_z = -vesselPointHeight;
    }
    std::tuple<double, double, double> get_rotationPoint() const
    {
        return std::make_tuple(_rotation_point_x, _rotation_point_y, _rotation_point_z);
    }

    //------------------------------------- Target offsets(e.g Offsets of Multibeam)---------------
    void set_targetOffsets(const std::string& key,
                           double             x,
                           double             y,
                           double             z,
                           double             yaw,
                           double             pitch,
                           double             roll)
    {
        set_targetOffsets(key, navdata::PositionalOffsets(x, y, z, yaw, pitch, roll));
    }
    void set_targetOffsets(const std::string& key, const navdata::PositionalOffsets& new_offsets)
    {

        auto map_it = _TargetOffsetIDs.find(key);
        if (map_it == _TargetOffsetIDs.end())
        {
            _TargetOffsets.push_back(new_offsets);
            _TargetOffsetIDs[key] = _TargetOffsets.size() - 1;
        }
        else
        {
            _TargetOffsets[map_it->second] = new_offsets;
        }
    }
    navdata::PositionalOffsets get_targetOffsets(const std::string& key) const
    {
        auto map_it = _TargetOffsetIDs.find(key);
        if (map_it == _TargetOffsetIDs.end())
        {
            std::stringstream s;
            s << "ERROR[SensorCoordinateSystem::get_target_offsets]: Could not find target key: "
              << key << "!";
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
    void set_compass_offsets(const navdata::PositionalOffsets& new_offsets) { _compass_offsets = new_offsets; }
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
    navdata::PositionalOffsets get_position_system_offsets() const { return _position_system_offsets; }

};

} // namespace navigation
} // namespace themachinethatgoesping
