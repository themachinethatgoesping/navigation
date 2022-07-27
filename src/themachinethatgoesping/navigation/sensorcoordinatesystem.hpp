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
    std::vector<navdata::PositionalOffsets> _TargetOffsets; ///< Positional offsets of registered targets
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

    navdata::SensorData _sensor_data; ///< Local sensor data

    bool   _Latlon_set = false;
    double _Lat;
    double _Lon;

    double _X     = 0; // Position Y in meters
    double _Y     = 0; // Position X in meters

  public:
  /**
   * @brief Construct a new Sensor Coordinate System object
   * 
   */
    SensorCoordinateSystem() = default;

    const navdata::PositionalOffsets& get_targe_offsets(const std::string& target_id) const
    {
        return _TargetOffsets.at(_TargetOffsetIDs.at(target_id));   // throws std::out_of_range if not found
    }

    navdata::GeoLocation compute_position(const navdata::SensorData& sensor_data,const std::string& target_id) const
    {
        navdata::GeoLocation location;

        // first get the current roation of the vessel
         auto vessel_quat = get_vesselQuat(sensor_data, _compass_offsets,_motion_sensor_offsets); 

        // convert x,y,z offsets to quaternions
        auto depth_sensor_xyz_quat = _depth_sensor_offsets.xyz_as_quaternion();

        // convert target to quaternion
        
        auto target_offsets = get_targe_offsets(target_id);
        auto target_xyz_quat = target_offsets.xyz_as_quaternion();
        auto target_ypr_quat = target_offsets.ypr_as_quaternion();

        // get rotated positions
        auto target_xyz  = tools::rotationfunctions::rotateXYZ(vessel_quat, target_xyz_quat);
        auto depth_sensor_xyz =
            tools::rotationfunctions::rotateXYZ(vessel_quat, depth_sensor_xyz_quat);
 
        // compute target depth
        location.z = target_xyz[2] - depth_sensor_xyz[2] + _sensor_data.gps_z - _sensor_data.heave_heave;

        // compute target ypr
        auto target_quat = vessel_quat * target_ypr_quat;
        auto ypr =
            tools::rotationfunctions::ypr_from_quaternion(target_quat);
        location.yaw = ypr[0];
        location.pitch = ypr[1];
        location.roll = ypr[2];
        
        return location;
    }


    //------------------------------------- get vessel position -----------------------------------

    std::tuple<double, double, double> get_targetYPR(const std::string& target_id) const
    {
        auto position = compute_position(_sensor_data, target_id);
        return std::make_tuple(position.yaw, position.pitch, position.roll);
    }


    /**
     * @brief get_targetDepth: Get the depth of the target including depth sensor values and heave
     * including motion correction)
     * @param target_id: Name of the target
     * @return return depth (world coordinates)
     */
    double get_targetDepth(const std::string& target_id) const
    {
        return compute_position(_sensor_data, target_id).z;
    }

    /**
     * @brief get_targetXY: Get the depth of the target including depth sensor values and heave
     * including motion correction)
     * @param target_id: Name of the target
     * @param use_VesselXY: Include the _X and _Y coordinates from the vessel (or not)
     * @return return x,y coordinates in meters (x=northing,y=easting) (relative to _X,_Y from
     * position system, includtion motion and depth corrections)
     */
    std::pair<double, double> get_targetXY(const std::string& target_id, bool use_VesselXY) const
    {
        auto target_xyz_quat = get_targe_offsets(target_id).xyz_as_quaternion();

        // distance between the rotation point and the depth sensor quat
        auto positionSystem_xyz_quat = _position_system_offsets.xyz_as_quaternion();

        auto vessel_quat = get_vesselQuat(_sensor_data, _compass_offsets,_motion_sensor_offsets); // current rotation of vessel
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
     * @param target_id: Name of the target
     * @param radians: if true will output heading as radians (otherwise degrees)
     * @return return distance,azimuth (0° Noth, 90° East) coordinates in meters,° (relative to the
     * position system, includtion motion and depth corrections)
     */
    std::pair<double, double> get_targetPosSysDistanceAndAzimuth(const std::string& target_id,
                                                                 bool               radians) const
    {
        auto xy = get_targetXY(target_id, false);

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
     * @param target_id: Name of the target
     * @return return latitude and longitude of the target in °
     */
    std::pair<double, double> get_targetLatLon(const std::string& target_id) const
    {
        double distance, heading;
        std::tie(distance, heading) = get_targetPosSysDistanceAndAzimuth(target_id, false);

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

    static Eigen::Quaterniond get_vesselQuat(
        const navdata::SensorData& sensor_data, 
        const navdata::PositionalOffsets& compasss_offsets, 
        const navdata::PositionalOffsets& motion_sensor_offsets)
    {
        /* first do yaw rotation */
        double heading = sensor_data.compass_heading;
        bool use_motionSensorYaw = false;

        if (std::isnan(heading))
        {
            use_motionSensorYaw = true;
            heading = sensor_data.imu_yaw;
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
            auto sensor_quat =
                tools::rotationfunctions::quaternion_from_ypr(sensor_data.imu_yaw, sensor_data.imu_pitch, sensor_data.imu_roll, true);
            sensor_quat.normalize();
            offset_quat.normalize();

            return offset_quat.inverse() * sensor_quat;
        }
        else
        {
            auto sensor_quat =
                tools::rotationfunctions::quaternion_from_ypr(0.0, sensor_data.imu_pitch, sensor_data.imu_roll, true);
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

    std::tuple<double, double, double> get_vesselYPR(bool radians) const
    {
        auto ypr = tools::rotationfunctions::ypr_from_quaternion(get_vesselQuat(_sensor_data, _compass_offsets,_motion_sensor_offsets), !radians);

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

    void set_sensor_data(const navdata::SensorData& sensor_data)
    {
        _sensor_data = sensor_data;
    }

    navdata::SensorData get_sensor_data() const
    {
        return _sensor_data;
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
    void set_targetOffsets(const std::string& target_id, const navdata::PositionalOffsets& new_offsets)
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
            s << "ERROR[SensorCoordinateSystem::get_target_offsets]: Could not find target target_id: "
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
