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
    const Rotation<float> vessel_rotation = get_vessel_rotation(sensor_data);

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
    const datastructures::Sensordata& sensor_data,
    float                             reference_heading_in_degrees) const
{
    return get_system_rotation(sensor_data,
                               _offsets_heading_source,
                               _offsets_attitude_source,
                               reference_heading_in_degrees);
}

datastructures::SensorPose SensorConfiguration::compute_target_pose(
    const std::string&                               target_id,
    const datastructures::Sensordata&                sensor_data,
    float                                            reference_heading_in_degrees,
    const std::string&                               subarray_id,
    const std::optional<datastructures::SensorPose>& subarray_pose) const
{
    using tools::rotationfunctions::Rotation;

    // Vessel orientation in the surface frame of the reference heading:
    // Rz(vessel_heading - reference_heading) * attitude. For a target sampled at transmit time the
    // residual yaw is zero; for a receive pose sampled later it keeps the yaw the vessel turned
    // through since transmit -- which a plain roll/pitch leveling would wrongly discard.
    const Rotation<float> vessel_rotation =
        get_vessel_rotation(sensor_data, reference_heading_in_degrees);

    // Static target pose in the vessel frame, already combined with the subarray phase center.
    const datastructures::SensorPose target = get_target(target_id, subarray_id, subarray_pose);

    const Rotation<float> pose_rotation = vessel_rotation * target.rotation;

    // Lever arm rotated into the surface frame by the full reference-relative rotation (no yaw
    // dropped). The z component is heading-independent, so it matches the geolocation depth.
    const auto target_xyz    = vessel_rotation.rotate(target.x, target.y, target.z);
    const auto depth_src_xyz = vessel_rotation.rotate(
        _offsets_depth_source.x, _offsets_depth_source.y, _offsets_depth_source.z);

    const float x = target_xyz[0];
    const float y = target_xyz[1];
    const float z = target_xyz[2] - depth_src_xyz[2] + sensor_data.depth - sensor_data.heave -
                    _waterline_offset;

    return datastructures::SensorPose(target_id, x, y, z, pose_rotation, false);
}

std::array<float, 3> SensorConfiguration::compute_position_system_offset(
    const datastructures::Sensordata& sensor_data,
    float                             reference_heading_in_degrees,
    bool                              at_waterline) const
{
    // Location of the active position-system reference point relative to the vessel reference
    // point, expressed in the surface (reference-heading) frame: R * (position_source lever arm),
    // where R = Rz(vessel_heading - reference_heading) * attitude. This is the heading-referenced
    // translation between the position system and the vessel reference point, including the full
    // horizontal antenna lever arm.
    //
    // at_waterline replaces the antenna height by the waterline offset, i.e. it projects the
    // position-system point onto the water surface. This is the horizontal reference the Kongsberg
    // .all XYZ88 beam positions use (the positioning system fixes a location on the sea surface),
    // so the lever arm from this point to the transducer carries the transducer's depth below the
    // waterline rather than below the antenna.
    // If the position source is motion compensated (.all P{n}M=1 / .kmall POSI C=On), the logged
    // position is already referenced to the vessel reference point: the reported position point
    // coincides with the reference point, so its offset is zero. Applying the geometric antenna
    // lever arm here would double-correct beam positions referenced to the positioning system.
    if (_position_source_motion_compensated)
        return { 0.f, 0.f, 0.f };

    const auto vessel_rotation = get_vessel_rotation(sensor_data, reference_heading_in_degrees);
    const float z = at_waterline ? _waterline_offset : _offsets_position_source.z;
    return vessel_rotation.rotate(_offsets_position_source.x, _offsets_position_source.y, z);
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

datastructures::SensorPose SensorConfiguration::combine_target_subarray(
    const datastructures::SensorPose& target, const datastructures::SensorPose& subarray)
{
    // The subarray offset lives in the target (array) frame: rotate it into the vessel frame by the
    // target installation and add to the target position; compose rotations only if the subarray tilts.
    const auto offset = target.rotation.rotate(subarray.x, subarray.y, subarray.z);
    datastructures::SensorPose combined = target;
    combined.x += offset[0];
    combined.y += offset[1];
    combined.z += offset[2];
    if (!subarray.has_zero_rotation())
        combined.rotation = target.rotation * subarray.rotation;
    return combined;
}

void SensorConfiguration::ensure_subarray_poses() const
{
    if (_subarray_poses_cached)
        return;

    _target_subarray_poses.clear();
    for (const auto& [target_id, subarrays] : _target_subarray_offsets)
    {
        auto target_it = _target_offsets.find(target_id);
        if (target_it == _target_offsets.end())
            continue; // orphan subarrays (target not registered yet) -> combined on the fly on demand
        auto& out = _target_subarray_poses[target_id];
        for (const auto& [subarray_id, subarray] : subarrays)
            out[subarray_id] = combine_target_subarray(target_it->second, subarray);
    }
    _subarray_poses_cached = true;
}

datastructures::SensorPose SensorConfiguration::get_target(
    const std::string&                               target_id,
    const std::string&                               subarray_id,
    const std::optional<datastructures::SensorPose>& subarray_pose) const
{
    const auto& target = get_target(target_id); // throws a descriptive error if the target is unknown

    if (subarray_pose.has_value())
        return combine_target_subarray(target, *subarray_pose); // custom offset -> combine on the fly

    if (subarray_id.empty())
        return target;

    // registered subarray -> precomputed vessel-frame pose
    ensure_subarray_poses();
    auto target_it = _target_subarray_poses.find(target_id);
    if (target_it != _target_subarray_poses.end())
    {
        auto sub_it = target_it->second.find(subarray_id);
        if (sub_it != target_it->second.end())
            return sub_it->second;
    }
    // not cached (e.g. subarray registered before its target): combine now. get_target_subarray
    // throws the descriptive out_of_range if the subarray is truly not registered.
    return combine_target_subarray(target, get_target_subarray(target_id, subarray_id));
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

void SensorConfiguration::set_subarrays_by_role(
    const std::map<std::string, datastructures::SensorPose>& subarrays)
{
    if (subarrays.empty())
        return;

    // split into transmit subarrays (everything except "RX") and the receive phase center ("RX")
    std::map<std::string, datastructures::SensorPose> tx_subs, rx_subs;
    for (const auto& [subarray_id, offset] : subarrays)
        (subarray_id == "RX" ? rx_subs : tx_subs)[subarray_id] = offset;

    for (const auto& target_id : get_target_ids())
    {
        if (target_id.starts_with("TRX"))
            set_target_subarrays(target_id, subarrays);
        else if (target_id.starts_with("TX"))
            set_target_subarrays(target_id, tx_subs);
        else if (target_id.starts_with("RX"))
            set_target_subarrays(target_id, rx_subs);
    }
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

void SensorConfiguration::set_position_source_motion_compensated(bool motion_compensated)
{
    invalidate_hash_cache();
    _position_source_motion_compensated = motion_compensated;
}
bool SensorConfiguration::get_position_source_motion_compensated() const
{
    return _position_source_motion_compensated;
}

// ----- helper functions -----
tools::rotationfunctions::Rotation<float> SensorConfiguration::get_system_rotation(
    const datastructures::Sensordata& sensor_data,
    const datastructures::SensorPose& offsets_heading_source,
    const datastructures::SensorPose& offsets_attitude_source,
    float                             reference_heading_in_degrees)
{
    using tools::rotationfunctions::Rotation;

    // sensor attitude as a rotation (pitch/roll only; the reported yaw is ignored)
    const Rotation<float> sensor_pitch_roll(0.f, sensor_data.pitch(), sensor_data.roll());

    // Remove the IMU mounting offset with the sensor pose's own rotation (raw * offset^-1), unless
    // the offsets are already applied to the logged data (e.g. Kongsberg .all is pre-corrected).
    const Rotation<float> pitch_roll_offset_removed =
        offsets_attitude_source.ypr_offsets_applied
            ? sensor_pitch_roll
            : sensor_pitch_roll * Rotation<float>(offsets_attitude_source.rotation.inverse());

    // keep only the corrected pitch/roll (removing the offset can introduce a spurious yaw)
    const auto            ypr = pitch_roll_offset_removed.ypr();
    const Rotation<float> pitch_roll(0.f, ypr[1], ypr[2]);

    // heading: remove the heading mounting offset unless already applied, then express it relative
    // to the reference heading (default 0 -> absolute world heading)
    float heading = offsets_heading_source.ypr_offsets_applied
                        ? sensor_data.heading()
                        : sensor_data.heading() - offsets_heading_source.yaw();
    heading -= reference_heading_in_degrees;

    return Rotation<float>(heading, 0.f, 0.f) * pitch_roll; // compass * pitch/roll
}
} // namespace navigation
} // namespace themachinethatgoesping
