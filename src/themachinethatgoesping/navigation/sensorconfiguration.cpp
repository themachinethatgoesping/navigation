// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensorconfiguration.hpp"

namespace themachinethatgoesping {
namespace navigation {

// ----- compute_target_position -----

datastructures::GeolocationLocal SensorConfiguration::compute_target_position(
    const std::string&                target_id,
    const datastructures::Sensordata& sensor_data) const
{
    datastructures::GeolocationLocal location;

    // first get the current rotation of the vessel
    Eigen::Quaternion<float> vessel_quat =
        get_system_rotation_as_quat(sensor_data, _offsets_heading_source, _offsets_attitude_source);

    // convert target to quaternion
    auto target_offsets  = get_target(target_id);
    auto target_ypr_quat = tools::rotationfunctions::quaternion_from_ypr(
        target_offsets.yaw, target_offsets.pitch, target_offsets.roll);

    // get rotated positions
    auto target_xyz = tools::rotationfunctions::rotateXYZ<float>(
        vessel_quat, target_offsets.x, target_offsets.y, target_offsets.z);
    auto depth_source_xyz = tools::rotationfunctions::rotateXYZ(
        vessel_quat, _offsets_depth_source.x, _offsets_depth_source.y, _offsets_depth_source.z);
    auto positionSystem_xyz = tools::rotationfunctions::rotateXYZ(vessel_quat,
                                                                  _offsets_position_source.x,
                                                                  _offsets_position_source.y,
                                                                  _offsets_position_source.z);

    // compute target depth
    location.z = target_xyz[2] - depth_source_xyz[2] + sensor_data.depth - sensor_data.heave -
                 _waterline_offset;

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

datastructures::GeolocationLocal SensorConfiguration::compute_target_position(
    const std::string&                     target_id,
    const datastructures::SensordataLocal& sensor_data) const
{
    auto position = compute_target_position(target_id, datastructures::Sensordata(sensor_data));

    // compute target xy
    position.northing += sensor_data.northing;
    position.easting += sensor_data.easting;

    return position;
}

datastructures::GeolocationUTM SensorConfiguration::compute_target_position(
    const std::string&                   target_id,
    const datastructures::SensordataUTM& sensor_data) const
{
    auto position =
        compute_target_position(target_id, datastructures::SensordataLocal(sensor_data));

    return datastructures::GeolocationUTM(
        position, sensor_data.utm_zone, sensor_data.northern_hemisphere);
}

datastructures::GeolocationLatLon SensorConfiguration::compute_target_position(
    const std::string&                      target_id,
    const datastructures::SensordataLatLon& sensor_data) const
{
    // compute position from Sensordata (no x,y or lat,lon coordinates)
    // this position is thus referenced to the gps antenna (0,0), which allows to compute
    // distance and azimuth if target towards the gps antenna
    auto position = compute_target_position(target_id, datastructures::Sensordata(sensor_data));

    auto distance =
        std::sqrt(position.northing * position.northing + position.easting * position.easting);
    auto heading = tools::rotationfunctions::compute_heading(position.northing, position.easting);

    double target_lat, target_lon;
    if (std::isnan(heading))
    {
        // this happens if there is no offset between the antenna and the target
        if (distance == 0)
        {
            target_lat = sensor_data.latitude;
            target_lon = sensor_data.longitude;
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
        geod.Direct(
            sensor_data.latitude, sensor_data.longitude, heading, distance, target_lat, target_lon);
    }

    // GeoPositionLocal is implicitly converted to GeoPosition when calling this function
    return datastructures::GeolocationLatLon(position, target_lat, target_lon);
}

// ----- get/set target offsets -----
const datastructures::PositionalOffsets& SensorConfiguration::get_target(
    const std::string& target_id) const
{
    // more specific error message
    try
    {
        return _target_offsets.at(target_id); // throws std::out_of_range if not found
    }
    catch (std::out_of_range& e)
    {
        // more specific error message
        std::string tmp = "[";

        if (!_target_offsets.empty())
        {
            for (const auto& kv : _target_offsets)
                tmp += kv.first + ",";
            tmp.back() = ']';
        }
        else
            tmp += "]";

        throw(std::out_of_range(
            fmt::format("ERROR[SensorConfiguration::get_target]: Could not find target "
                        "offsets for id {}. The following target ids are registered: {}",
                        target_id,
                        tmp)));
    }
}

const std::map<std::string, datastructures::PositionalOffsets>& SensorConfiguration::get_targets()
    const
{
    return _target_offsets;
}

void SensorConfiguration::remove_target(const std::string& target_id)
{
    _target_offsets.erase(target_id);
}

void SensorConfiguration::remove_targets()
{
    _target_offsets.clear();
    add_target("0", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

bool SensorConfiguration::has_target(const std::string& target_id) const
{
    return _target_offsets.contains(target_id);
}

void SensorConfiguration::add_target(const std::string&                       target_id,
                                     const datastructures::PositionalOffsets& target_offsets)
{
    _target_offsets[target_id] = target_offsets;
}

void SensorConfiguration::add_target(const std::string& target_id,
                                     float              x,
                                     float              y,
                                     float              z,
                                     float              yaw,
                                     float              pitch,
                                     float              roll)
{
    add_target(target_id, datastructures::PositionalOffsets(target_id, x, y, z, yaw, pitch, roll));
}

void SensorConfiguration::add_targets(
    const std::map<std::string, datastructures::PositionalOffsets>& targets)
{
    for (const auto& target : targets)
        add_target(target.first, target.second);
}

// ----- get/set sensor offsets -----
void SensorConfiguration::set_attitude_source(std::string_view name,
                                              float            yaw,
                                              float            pitch,
                                              float            roll)
{
    _offsets_attitude_source =
        datastructures::PositionalOffsets(name, 0.0, 0.0, 0.0, yaw, pitch, roll);
}
void SensorConfiguration::set_attitude_source(
    const datastructures::PositionalOffsets& sensor_offsets)
{
    _offsets_attitude_source = sensor_offsets;
}

datastructures::PositionalOffsets SensorConfiguration::get_attitude_source() const
{
    return _offsets_attitude_source;
}

void SensorConfiguration::set_heading_source(std::string_view name, float yaw)
{
    _offsets_heading_source = datastructures::PositionalOffsets(name, 0.0, 0.0, 0.0, yaw, 0.0, 0.0);
}
void SensorConfiguration::set_heading_source(
    const datastructures::PositionalOffsets& sensor_offsets)
{
    _offsets_heading_source = sensor_offsets;
}
datastructures::PositionalOffsets SensorConfiguration::get_heading_source() const
{
    return _offsets_heading_source;
}

void SensorConfiguration::set_waterline_offset(float z)
{
    _waterline_offset = z;
}

float SensorConfiguration::get_waterline_offset() const
{
    return _waterline_offset;
}

void SensorConfiguration::set_depth_source(std::string_view name, float x, float y, float z)
{
    _offsets_depth_source = datastructures::PositionalOffsets(name, x, y, z, 0.0, 0.0, 0.0);
}
void SensorConfiguration::set_depth_source(const datastructures::PositionalOffsets& sensor_offsets)
{
    _offsets_depth_source = sensor_offsets;
}
datastructures::PositionalOffsets SensorConfiguration::get_depth_source() const
{
    return _offsets_depth_source;
}

void SensorConfiguration::set_position_source(std::string_view name, float x, float y, float z)
{
    _offsets_position_source = datastructures::PositionalOffsets(name, x, y, z, 0.0, 0.0, 0.0);
}
void SensorConfiguration::set_position_source(
    const datastructures::PositionalOffsets& sensor_offsets)
{
    _offsets_position_source = sensor_offsets;
}
datastructures::PositionalOffsets SensorConfiguration::get_position_source() const
{
    return _offsets_position_source;
}

// ----- helper functions -----
Eigen::Quaternion<float> SensorConfiguration::get_system_rotation_as_quat(
    const datastructures::Sensordata&        sensor_data,
    const datastructures::PositionalOffsets& offsets_heading_source,
    const datastructures::PositionalOffsets& offsets_attitude_source)
{
    // convert offset to quaternion
    Eigen::Quaternion<float> imu_offset_quat =
        tools::rotationfunctions::quaternion_from_ypr(offsets_attitude_source.yaw,
                                                      offsets_attitude_source.pitch,
                                                      offsets_attitude_source.roll,
                                                      true);

    // convert sensor pitch,roll to quaternion (ignore reported yaw)
    auto imu_sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
        0.0f, sensor_data.pitch, sensor_data.roll, true);

    // compute roll and pitch using the imu_offsets (including yaw offset)
    // TODO: check if the order is correct
    auto pr_quat = imu_sensor_quat * imu_offset_quat.inverse();
    pr_quat.normalize();

    // compute sensor quat using the correct pitch and roll (ignore yaw)
    auto ypr         = tools::rotationfunctions::ypr_from_quaternion(pr_quat, false);
    auto sensor_quat = tools::rotationfunctions::quaternion_from_ypr(0.f, ypr[1], ypr[2], false);

    // rotate sensor quat using heading
    float heading      = sensor_data.heading - offsets_heading_source.yaw;
    auto  compass_quat = tools::rotationfunctions::quaternion_from_ypr(heading, 0.0f, 0.0f, true);

    auto vessel_quat = compass_quat * sensor_quat;
    vessel_quat.normalize();
    return vessel_quat;
}
} // namespace navigation
} // namespace themachinethatgoesping
