// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
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
    using tools::rotationfunctions::Rotation;
    datastructures::GeolocationLocal location;

    // current rotation of the vessel (heading + attitude, mounting offsets removed)
    const Rotation<float> vessel_rotation =
        get_system_rotation_as_quat(sensor_data, _offsets_heading_source, _offsets_attitude_source);

    const auto&            target_offsets      = get_target(target_id);
    const Rotation<float>& target_installation = target_offsets.rotation;

    // rotate the lever arms into the world frame
    const auto target_xyz =
        vessel_rotation.rotate(target_offsets.x, target_offsets.y, target_offsets.z);
    const auto depth_source_xyz = vessel_rotation.rotate(
        _offsets_depth_source.x, _offsets_depth_source.y, _offsets_depth_source.z);
    const auto positionSystem_xyz = vessel_rotation.rotate(
        _offsets_position_source.x, _offsets_position_source.y, _offsets_position_source.z);

    // compute target depth
    location.z = target_xyz[2] - depth_source_xyz[2] + sensor_data.depth - sensor_data.heave -
                 _waterline_offset;

    // compute target orientation
    location.rotation = vessel_rotation * target_installation;

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

tools::rotationfunctions::Rotation<float> SensorConfiguration::get_vessel_rotation(
    const datastructures::Sensordata& sensor_data) const
{
    return get_system_rotation_as_quat(
        sensor_data, _offsets_heading_source, _offsets_attitude_source);
}

datastructures::SensorPose SensorConfiguration::compute_target_pose(
    const std::string&                               target_id,
    const datastructures::Sensordata&                sensor_data,
    float                                            reference_heading_in_degrees,
    bool                                             level_lever_arm,
    const std::string&                               subarray_id,
    const std::optional<datastructures::SensorPose>& subarray_pose) const
{
    using tools::rotationfunctions::Rotation;

    const Rotation<float> vessel_rotation = get_vessel_rotation(sensor_data);
    const auto&           target_offsets  = get_target(target_id);

    // ship-frame orientation: remove the common reference heading (so all poses of a ping share
    // one frame), keep the vessel attitude and the target installation.
    const Rotation<float> pose_rotation = Rotation<float>(-reference_heading_in_degrees, 0.f, 0.f) *
                                          vessel_rotation * target_offsets.rotation;

    // horizontal lever arm: raw body-frame offsets, or roll/pitch-leveled (heading removed)
    float x = target_offsets.x;
    float y = target_offsets.y;
    if (level_lever_arm)
    {
        const auto ypr     = vessel_rotation.ypr();
        const auto leveled = Rotation<float>(0.f, ypr[1], ypr[2])
                                 .rotate(target_offsets.x, target_offsets.y, target_offsets.z);
        x = leveled[0];
        y = leveled[1];
    }

    // depth below the waterline (heading-independent z of the rotated lever arms)
    const auto target_xyz =
        vessel_rotation.rotate(target_offsets.x, target_offsets.y, target_offsets.z);
    const auto depth_source_xyz = vessel_rotation.rotate(
        _offsets_depth_source.x, _offsets_depth_source.y, _offsets_depth_source.z);
    const float z = target_xyz[2] - depth_source_xyz[2] + sensor_data.depth - sensor_data.heave -
                    _waterline_offset;

    datastructures::SensorPose pose(target_id, x, y, z, pose_rotation, false);

    // Add a subarray phase-center offset (an explicit subarray_pose overrides a registered
    // subarray_id; "" and no pose = none). The offset is defined in the target (transducer) frame,
    // so it is rotated into the pose frame by the pose orientation and added to the position; the
    // pose orientation is only changed when the subarray carries a non-identity rotation.
    const datastructures::SensorPose* subarray = nullptr;
    if (subarray_pose.has_value())
        subarray = &subarray_pose.value();
    else if (!subarray_id.empty())
        subarray = &get_target_subarray(target_id, subarray_id);

    if (subarray != nullptr)
    {
        const auto offset = pose.rotation.rotate(subarray->x, subarray->y, subarray->z);
        pose.x += offset[0];
        pose.y += offset[1];
        pose.z += offset[2];
        if (!subarray->has_zero_rotation())
            pose.rotation = pose.rotation * subarray->rotation;
    }

    return pose;
}

std::array<float, 3> SensorConfiguration::get_vessel_attitude(
    const datastructures::Sensordata& sensor_data) const
{
    // {yaw, pitch, roll} in degrees, same convention as compute_target_position
    return get_vessel_rotation(sensor_data).ypr();
}

// ----- get/set target offsets -----
const datastructures::SensorPose& SensorConfiguration::get_target(
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

const std::map<std::string, datastructures::SensorPose>& SensorConfiguration::get_targets()
    const
{
    return _target_offsets;
}

void SensorConfiguration::remove_target(const std::string& target_id)
{
    invalidate_hash_cache();
    _target_offsets.erase(target_id);
    _target_subarray_offsets.erase(target_id);
}

void SensorConfiguration::remove_targets()
{
    invalidate_hash_cache();
    _target_offsets.clear();
    _target_subarray_offsets.clear();
    add_target("0", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

bool SensorConfiguration::has_target(const std::string& target_id) const
{
    return _target_offsets.contains(target_id);
}

void SensorConfiguration::add_target(const std::string&                       target_id,
                                     const datastructures::SensorPose& target_offsets)
{
    invalidate_hash_cache();
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
    add_target(target_id, datastructures::SensorPose(target_id, x, y, z, yaw, pitch, roll));
}

void SensorConfiguration::add_targets(
    const std::map<std::string, datastructures::SensorPose>& targets)
{
    for (const auto& target : targets)
        add_target(target.first, target.second);
}

// ----- target subarray offsets -----

std::map<std::string, datastructures::SensorPose> SensorConfiguration::get_model_subarray_offsets(
    std::string_view model_name)
{
    return navigation::get_model_subarray_offsets(model_name);
}

datastructures::SensorPose SensorConfiguration::get_model_subarray_offset(
    std::string_view model_name, const std::string& subarray_id)
{
    return navigation::get_model_subarray_offset(model_name, subarray_id);
}

void SensorConfiguration::add_target_subarray(const std::string&                target_id,
                                              const std::string&                subarray_id,
                                              const datastructures::SensorPose& subarray_offsets)
{
    invalidate_hash_cache();
    _target_subarray_offsets[target_id][subarray_id] = subarray_offsets;
}

void SensorConfiguration::set_target_subarrays(
    const std::string&                                       target_id,
    const std::map<std::string, datastructures::SensorPose>& subarrays)
{
    invalidate_hash_cache();
    if (subarrays.empty())
        _target_subarray_offsets.erase(target_id);
    else
        _target_subarray_offsets[target_id] = subarrays;
}

void SensorConfiguration::set_target_subarrays_from_model(const std::string& target_id,
                                                          std::string_view   model_name)
{
    auto offsets = get_model_subarray_offsets(model_name);
    if (!offsets.empty())
        set_target_subarrays(target_id, offsets);
}

bool SensorConfiguration::has_target_subarrays(const std::string& target_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    return it != _target_subarray_offsets.end() && !it->second.empty();
}

bool SensorConfiguration::has_target_subarray(const std::string& target_id,
                                              const std::string& subarray_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    return it != _target_subarray_offsets.end() && it->second.contains(subarray_id);
}

const datastructures::SensorPose& SensorConfiguration::get_target_subarray(
    const std::string& target_id, const std::string& subarray_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    if (it != _target_subarray_offsets.end())
    {
        auto sub = it->second.find(subarray_id);
        if (sub != it->second.end())
            return sub->second;
    }
    throw std::out_of_range(
        fmt::format("ERROR[SensorConfiguration::get_target_subarray]: no subarray '{}' registered "
                    "for target '{}'",
                    subarray_id,
                    target_id));
}

const std::map<std::string, datastructures::SensorPose>& SensorConfiguration::get_target_subarrays(
    const std::string& target_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    if (it == _target_subarray_offsets.end())
        throw std::out_of_range(fmt::format(
            "ERROR[SensorConfiguration::get_target_subarrays]: target '{}' has no subarray offsets",
            target_id));
    return it->second;
}

std::vector<std::string> SensorConfiguration::get_target_subarray_ids(
    const std::string& target_id) const
{
    std::vector<std::string> ids;
    auto                     it = _target_subarray_offsets.find(target_id);
    if (it != _target_subarray_offsets.end())
        for (const auto& [subarray_id, offsets] : it->second)
            ids.push_back(subarray_id);
    return ids;
}

void SensorConfiguration::remove_target_subarrays(const std::string& target_id)
{
    invalidate_hash_cache();
    _target_subarray_offsets.erase(target_id);
}

// ----- system metadata -----
void SensorConfiguration::set_model_name(std::string name)
{
    invalidate_hash_cache();
    _model_name = std::move(name);
}

void SensorConfiguration::set_transducer_configuration(std::string cfg)
{
    invalidate_hash_cache();
    _transducer_configuration = std::move(cfg);
}

// ----- get/set sensor offsets -----
void SensorConfiguration::set_attitude_source(std::string_view name,
                                              float            yaw,
                                              float            pitch,
                                              float            roll)
{
    invalidate_hash_cache();
    _offsets_attitude_source =
        datastructures::SensorPose(name, 0.0, 0.0, 0.0, yaw, pitch, roll);
}
void SensorConfiguration::set_attitude_source(
    const datastructures::SensorPose& sensor_offsets)
{
    invalidate_hash_cache();
    _offsets_attitude_source = sensor_offsets;
}

datastructures::SensorPose SensorConfiguration::get_attitude_source() const
{
    return _offsets_attitude_source;
}

void SensorConfiguration::set_heading_source(std::string_view name, float yaw)
{
    invalidate_hash_cache();
    _offsets_heading_source = datastructures::SensorPose(name, 0.0, 0.0, 0.0, yaw, 0.0, 0.0);
}
void SensorConfiguration::set_heading_source(
    const datastructures::SensorPose& sensor_offsets)
{
    invalidate_hash_cache();
    _offsets_heading_source = sensor_offsets;
}
datastructures::SensorPose SensorConfiguration::get_heading_source() const
{
    return _offsets_heading_source;
}

void SensorConfiguration::set_waterline_offset(float z)
{
    invalidate_hash_cache();
    _waterline_offset = z;
}

float SensorConfiguration::get_waterline_offset() const
{
    return _waterline_offset;
}

void SensorConfiguration::set_depth_source(std::string_view name, float x, float y, float z)
{
    invalidate_hash_cache();
    _offsets_depth_source = datastructures::SensorPose(name, x, y, z, 0.0, 0.0, 0.0);
}
void SensorConfiguration::set_depth_source(const datastructures::SensorPose& sensor_offsets)
{
    invalidate_hash_cache();
    _offsets_depth_source = sensor_offsets;
}
datastructures::SensorPose SensorConfiguration::get_depth_source() const
{
    return _offsets_depth_source;
}

void SensorConfiguration::set_position_source(std::string_view name, float x, float y, float z)
{
    invalidate_hash_cache();
    _offsets_position_source = datastructures::SensorPose(name, x, y, z, 0.0, 0.0, 0.0);
}
void SensorConfiguration::set_position_source(
    const datastructures::SensorPose& sensor_offsets)
{
    invalidate_hash_cache();
    _offsets_position_source = sensor_offsets;
}
datastructures::SensorPose SensorConfiguration::get_position_source() const
{
    return _offsets_position_source;
}

// ----- helper functions -----
Eigen::Quaternion<float> SensorConfiguration::get_system_rotation_as_quat(
    const datastructures::Sensordata&        sensor_data,
    const datastructures::SensorPose& offsets_heading_source,
    const datastructures::SensorPose& offsets_attitude_source)
{
    // convert offset to quaternion
    // If the attitude offsets are already applied to the logged sensor data (e.g. Kongsberg .all,
    // where the PU corrects the attitude for the sensor mounting offsets before logging), use the
    // identity offset so that the correction is not applied twice.
    Eigen::Quaternion<float> imu_offset_quat =
        offsets_attitude_source.ypr_offsets_applied
            ? Eigen::Quaternion<float>::Identity()
            : tools::rotationfunctions::quaternion_from_ypr(offsets_attitude_source.yaw(),
                                                            offsets_attitude_source.pitch(),
                                                            offsets_attitude_source.roll(),
                                                            true);

    // convert sensor pitch,roll to quaternion (ignore reported yaw)
    auto imu_sensor_quat = tools::rotationfunctions::quaternion_from_ypr(
        0.0f, sensor_data.pitch(), sensor_data.roll(), true);

    // compute roll and pitch using the imu_offsets (including yaw offset)
    // TODO: check if the order is correct
    auto pr_quat = imu_sensor_quat * imu_offset_quat.inverse();
    pr_quat.normalize();

    // compute sensor quat using the correct pitch and roll (ignore yaw)
    auto ypr         = tools::rotationfunctions::ypr_from_quaternion(pr_quat, false);
    auto sensor_quat = tools::rotationfunctions::quaternion_from_ypr(0.f, ypr[1], ypr[2], false);

    // rotate sensor quat using heading
    // As above, only remove the heading offset when it has not already been applied to the heading
    // data (e.g. Kongsberg .all logs the heading corrected for the heading offset).
    float heading      = offsets_heading_source.ypr_offsets_applied
                             ? sensor_data.heading()
                             : sensor_data.heading() - offsets_heading_source.yaw();
    auto  compass_quat = tools::rotationfunctions::quaternion_from_ypr(heading, 0.0f, 0.0f, true);

    auto vessel_quat = compass_quat * sensor_quat;
    vessel_quat.normalize();
    return vessel_quat;
}
} // namespace navigation
} // namespace themachinethatgoesping
