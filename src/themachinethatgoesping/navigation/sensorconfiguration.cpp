// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensorconfiguration.hpp"

namespace themachinethatgoesping {
namespace navigation {

// ----- compute_target_position -----

datastructures::GeoLocationLocal SensorConfiguration::compute_target_position(
    const std::string&         target_id,
    const datastructures::SensorData& sensor_data) const
{
    datastructures::GeoLocationLocal location;

    // first get the current rotation of the vessel
    auto vessel_quat =
        get_system_rotation_as_quat(sensor_data, _compass_offsets, _motion_sensor_offsets);

    // convert target to quaternion
    auto target_offsets  = get_target_offsets(target_id);
    auto target_ypr_quat = tools::rotationfunctions::quaternion_from_ypr(
        target_offsets.yaw, target_offsets.pitch, target_offsets.roll);

    // get rotated positions
    auto target_xyz = tools::rotationfunctions::rotateXYZ(
        vessel_quat, target_offsets.x, target_offsets.y, target_offsets.z);
    auto depth_sensor_xyz = tools::rotationfunctions::rotateXYZ(
        vessel_quat, _depth_sensor_offsets.x, _depth_sensor_offsets.y, _depth_sensor_offsets.z);
    auto positionSystem_xyz = tools::rotationfunctions::rotateXYZ(vessel_quat,
                                                                  _position_system_offsets.x,
                                                                  _position_system_offsets.y,
                                                                  _position_system_offsets.z);

    // compute target depth
    location.z = target_xyz[2] - depth_sensor_xyz[2] + sensor_data.gps_z - sensor_data.heave_heave;

    // compute target ypr
    // TODO: check if the order is correct
    auto target_quat = vessel_quat * target_ypr_quat;
    auto ypr         = tools::rotationfunctions::ypr_from_quaternion(target_quat);
    location.yaw     = ypr[0];
    location.pitch   = ypr[1];
    location.roll    = ypr[2];

    // compute target xy
    location.northing = target_xyz[0] - positionSystem_xyz[0];
    location.easting  = target_xyz[1] - positionSystem_xyz[1];

    return location;
}

datastructures::GeoLocationLocal SensorConfiguration::compute_target_position(
    const std::string&              target_id,
    const datastructures::SensorDataLocal& sensor_data) const
{
    auto position = compute_target_position(target_id, datastructures::SensorData(sensor_data));

    // compute target xy
    position.northing += sensor_data.gps_northing;
    position.easting += sensor_data.gps_easting;

    return position;
}

datastructures::GeoLocationUTM SensorConfiguration::compute_target_position(
    const std::string&            target_id,
    const datastructures::SensorDataUTM& sensor_data) const
{
    auto position = compute_target_position(target_id, datastructures::SensorDataLocal(sensor_data));

    return datastructures::GeoLocationUTM(
        position, sensor_data.gps_zone, sensor_data.gps_northern_hemisphere);
}

datastructures::GeoLocationLatLon SensorConfiguration::compute_target_position(
    const std::string&               target_id,
    const datastructures::SensorDataLatLon& sensor_data) const
{
    // compute position from SensorData (no x,y or lat,lon coordinates)
    // this position is thus referenced to the gps antenna (0,0), which allows to compute
    // distance and azimuth if target towards the gps antenna
    auto position = compute_target_position(target_id, datastructures::SensorData(sensor_data));

    double distance =
        std::sqrt(position.northing * position.northing + position.easting * position.easting);
    double heading = tools::rotationfunctions::compute_heading(position.northing, position.easting);

    double target_lat, target_lon;
    if (std::isnan(heading))
    {
        // this happens if there is no offset between the antenna and the target
        if (distance == 0)
        {
            target_lat = sensor_data.gps_latitude;
            target_lon = sensor_data.gps_longitude;
        }

        // this should never happen
        else
            throw(
                std::runtime_error("compute_target_position[ERROR]: heading is nan but distance is "
                                   "not 0! (this should never happen)"));
    }
    else
    {
        GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                     GeographicLib::Constants::WGS84_f());
        geod.Direct(sensor_data.gps_latitude,
                    sensor_data.gps_longitude,
                    heading,
                    distance,
                    target_lat,
                    target_lon);
    }

    // GeoPositionLocal is implicitly converted to GeoPosition when calling this function
    return datastructures::GeoLocationLatLon(position, target_lat, target_lon);
}

// ----- get/set target offsets -----
const datastructures::PositionalOffsets& SensorConfiguration::get_target_offsets(
    const std::string& target_id) const
{
    return _target_offsets.at(target_id); // throws std::out_of_range if not found
}

void SensorConfiguration::add_target(const std::string&                target_id,
                                             const datastructures::PositionalOffsets& target_offsets)
{
    _target_offsets[target_id] = target_offsets;
}

void SensorConfiguration::add_target(const std::string& target_id,
                                             double             x,
                                             double             y,
                                             double             z,
                                             double             yaw,
                                             double             pitch,
                                             double             roll)
{
    add_target(target_id, datastructures::PositionalOffsets(x, y, z, yaw, pitch, roll));
}

// ----- get/set sensor offsets -----
void SensorConfiguration::set_motion_sensor_offsets(double yaw, double pitch, double roll)
{
    _motion_sensor_offsets = datastructures::PositionalOffsets(0.0, 0.0, 0.0, yaw, pitch, roll);
}
void SensorConfiguration::set_motion_sensor_offsets(
    const datastructures::PositionalOffsets& sensor_offsets)
{
    _motion_sensor_offsets = sensor_offsets;
}

datastructures::PositionalOffsets SensorConfiguration::get_motion_sensor_offsets() const
{
    return _motion_sensor_offsets;
}

void SensorConfiguration::set_compass_offsets(double yaw)
{
    _compass_offsets = datastructures::PositionalOffsets(0.0, 0.0, 0.0, yaw, 0.0, 0.0);
}
void SensorConfiguration::set_compass_offsets(const datastructures::PositionalOffsets& sensor_offsets)
{
    _compass_offsets = sensor_offsets;
}
datastructures::PositionalOffsets SensorConfiguration::get_compass_offsets() const
{
    return _compass_offsets;
}

void SensorConfiguration::set_depth_sensor_offsets(double x, double y, double z)
{
    _depth_sensor_offsets = datastructures::PositionalOffsets(x, y, z, 0.0, 0.0, 0.0);
}
void SensorConfiguration::set_depth_sensor_offsets(const datastructures::PositionalOffsets& sensor_offsets)
{
    _depth_sensor_offsets = sensor_offsets;
}
datastructures::PositionalOffsets SensorConfiguration::get_depth_sensor_offsets() const
{
    return _depth_sensor_offsets;
}

void SensorConfiguration::set_position_system_offsets(double x, double y, double z)
{
    _position_system_offsets = datastructures::PositionalOffsets(x, y, z, 0.0, 0.0, 0.0);
}
void SensorConfiguration::set_position_system_offsets(
    const datastructures::PositionalOffsets& sensor_offsets)
{
    _position_system_offsets = sensor_offsets;
}
datastructures::PositionalOffsets SensorConfiguration::get_position_system_offsets() const
{
    return _position_system_offsets;
}

// ----- helper functions -----
Eigen::Quaterniond SensorConfiguration::get_system_rotation_as_quat(
    const datastructures::SensorData&        sensor_data,
    const datastructures::PositionalOffsets& compass_offsets,
    const datastructures::PositionalOffsets& motion_sensor_offsets)
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
        auto pr_quat = imu_sensor_quat * imu_offset_quat.inverse();
        pr_quat.normalize();

        // compute sensor quat using the correct pitch and roll (ignore yaw)
        auto ypr         = tools::rotationfunctions::ypr_from_quaternion(pr_quat, false);
        auto sensor_quat = tools::rotationfunctions::quaternion_from_ypr(0., ypr[1], ypr[2], false);

        // rotate sensor quat using compass_heading
        double heading    = sensor_data.compass_heading - compass_offsets.yaw;
        auto compass_quat = tools::rotationfunctions::quaternion_from_ypr(heading, 0.0, 0.0, true);

        auto vessel_quat = compass_quat * sensor_quat;
        vessel_quat.normalize();
        return vessel_quat;
    }
}
} // namespace navigation
} // namespace themachinethatgoesping
