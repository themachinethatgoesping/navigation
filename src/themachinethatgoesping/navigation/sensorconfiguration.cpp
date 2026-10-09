// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensorconfiguration.hpp"

namespace themachinethatgoesping {
namespace navigation {

// ----- construction / lifecycle -----

SensorConfiguration::SensorConfiguration(std::string_view default_sensor_name)
{
    _offsets_attitude_source.name = default_sensor_name;
    _offsets_heading_source.name  = default_sensor_name;
    _offsets_position_source.name = default_sensor_name;
    _offsets_depth_source.name    = default_sensor_name;

    add_target("0", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

SensorConfiguration SensorConfiguration::without_targets() const
{
    SensorConfiguration result(*this);
    result.remove_targets();
    return result;
}

bool SensorConfiguration::can_merge_targets_with(const SensorConfiguration& other) const
{
    /* check for incompatible targets */
    for (const auto& [target_id, offsets] : _target_offsets)
    {
        auto it = other._target_offsets.find(target_id);
        if (it != other._target_offsets.end())
        {
            if (offsets != it->second)
                return false;
        }
    }

    return true;
}

void SensorConfiguration::invalidate_hash_cache()
{
    _cached_binary_hash.reset();
    _subarray_poses_cached = false;
}

// ----- compute_target_position -----

datastructures::GeolocationLocal SensorConfiguration::compute_target_position(
    const datastructures::SensorPose& target_offsets,
    const datastructures::Sensordata& sensor_data) const
{
    using tools::rotationfunctions::Rotation;
    datastructures::GeolocationLocal location;

    // current rotation of the vessel (heading + attitude, mounting offsets removed)
    const Rotation<float> vessel_rotation = get_vessel_rotation(sensor_data);

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
    const datastructures::SensorPose&      target,
    const datastructures::SensordataLocal& sensor_data) const
{
    auto position = compute_target_position(target, datastructures::Sensordata(sensor_data));

    // compute target xy
    position.northing += sensor_data.northing;
    position.easting += sensor_data.easting;

    return position;
}

datastructures::GeolocationUTM SensorConfiguration::compute_target_position(
    const datastructures::SensorPose&    target,
    const datastructures::SensordataUTM& sensor_data) const
{
    auto position = compute_target_position(target, datastructures::SensordataLocal(sensor_data));

    return datastructures::GeolocationUTM(
        position, sensor_data.utm_zone, sensor_data.northern_hemisphere);
}

datastructures::GeolocationLatLon SensorConfiguration::compute_target_position(
    const datastructures::SensorPose&       target,
    const datastructures::SensordataLatLon& sensor_data) const
{
    // compute position from Sensordata (no x,y or lat,lon coordinates)
    // this position is thus referenced to the gps antenna (0,0), which allows to compute
    // distance and azimuth if target towards the gps antenna
    auto position = compute_target_position(target, datastructures::Sensordata(sensor_data));

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

// The string_view overloads resolve the target offsets (get_target) and delegate to the
// SensorPose-based overloads above.
datastructures::GeolocationLocal SensorConfiguration::compute_target_position(
    std::string_view                  target_id,
    const datastructures::Sensordata& sensor_data) const
{
    return compute_target_position(get_target(target_id), sensor_data);
}

datastructures::GeolocationLocal SensorConfiguration::compute_target_position(
    std::string_view                       target_id,
    const datastructures::SensordataLocal& sensor_data) const
{
    return compute_target_position(get_target(target_id), sensor_data);
}

datastructures::GeolocationUTM SensorConfiguration::compute_target_position(
    std::string_view                     target_id,
    const datastructures::SensordataUTM& sensor_data) const
{
    return compute_target_position(get_target(target_id), sensor_data);
}

datastructures::GeolocationLatLon SensorConfiguration::compute_target_position(
    std::string_view                        target_id,
    const datastructures::SensordataLatLon& sensor_data) const
{
    return compute_target_position(get_target(target_id), sensor_data);
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
    const datastructures::SensorPose& target,
    const datastructures::Sensordata& sensor_data,
    float                             reference_heading_in_degrees) const
{
    using tools::rotationfunctions::Rotation;

    // Vessel orientation in the surface frame of the reference heading:
    // Rz(vessel_heading - reference_heading) * attitude. For a target sampled at transmit time the
    // residual yaw is zero; for a receive pose sampled later it keeps the yaw the vessel turned
    // through since transmit -- which a plain roll/pitch leveling would wrongly discard.
    const Rotation<float> vessel_rotation =
        get_vessel_rotation(sensor_data, reference_heading_in_degrees);

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

    return datastructures::SensorPose(target.name, x, y, z, pose_rotation, false);
}

datastructures::SensorPose SensorConfiguration::compute_target_pose(
    std::string_view                                 target_id,
    const datastructures::Sensordata&                sensor_data,
    float                                            reference_heading_in_degrees,
    std::string_view                                 subarray_id,
    const std::optional<datastructures::SensorPose>& subarray_pose) const
{
    // Resolve the (subarray-combined) target pose and delegate to the SensorPose overload; keep
    // the result named after the requested target_id (independent of the stored pose name).
    auto pose = compute_target_pose(get_target(target_id, subarray_id, subarray_pose),
                                    sensor_data,
                                    reference_heading_in_degrees);
    pose.name = std::string(target_id);
    return pose;
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

    const auto  vessel_rotation = get_vessel_rotation(sensor_data, reference_heading_in_degrees);
    const float z               = at_waterline ? _waterline_offset : _offsets_position_source.z;
    return vessel_rotation.rotate(_offsets_position_source.x, _offsets_position_source.y, z);
}

// ----- get/set target offsets -----
const datastructures::SensorPose& SensorConfiguration::get_target(std::string_view target_id) const
{
    // more specific error message
    auto it = _target_offsets.find(target_id);
    if (it != _target_offsets.end())
        return it->second;

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

datastructures::SensorPose SensorConfiguration::combine_target_subarray(
    const datastructures::SensorPose& target,
    const datastructures::SensorPose& subarray)
{
    // The subarray offset lives in the target (array) frame: rotate it into the vessel frame by the
    // target installation and add to the target position; compose rotations only if the subarray
    // tilts.
    const auto                 offset = target.rotation.rotate(subarray.x, subarray.y, subarray.z);
    datastructures::SensorPose combined = target;
    combined.x += offset[0];
    combined.y += offset[1];
    combined.z += offset[2];
    combined.name = fmt::format("{} [{}]", combined.name, subarray.name);
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
            continue; // orphan subarrays (target not registered yet) -> combined on the fly on
                      // demand
        auto& out = _target_subarray_poses[target_id];
        for (const auto& [subarray_id, subarray] : subarrays)
            out[subarray_id] = combine_target_subarray(target_it->second, subarray);
    }
    _subarray_poses_cached = true;
}

// ----- transducer channel functions -----

bool SensorConfiguration::has_transducer_channel(std::string_view channel_id) const
{
    return _transducer_channel_id_to_trx.contains(channel_id);
}

void SensorConfiguration::register_transducer_channel(
    std::string_view                channel_id,
    std::string_view                tx_id,
    std::string_view                rx_id,
    std::string_view                trx_id,
    std::string_view                tx_default_sub,
    std::string_view                rx_default_sub,
    std::string_view                trx_default_sub,
    const std::vector<std::string>& tx_sector_subarrays)
{
    invalidate_hash_cache();
    const std::string key(channel_id);

    TransducerTransmitChannel& tx = _transducer_channel_id_to_tx[key];
    tx.tx_id                      = tx_id;
    tx.default_subarray           = tx_default_sub;
    tx.sector_subarrays           = tx_sector_subarrays;

    auto& rx            = _transducer_channel_id_to_rx[key];
    rx.first            = rx_id;
    rx.second           = rx_default_sub;
    auto& trx           = _transducer_channel_id_to_trx[key];
    trx.first           = trx_id;
    trx.second          = trx_default_sub;
}

void SensorConfiguration::unregister_transducer_channel(std::string_view channel_id)
{
    invalidate_hash_cache();
    const std::string key(channel_id);
    _transducer_channel_id_to_tx.erase(key);
    _transducer_channel_id_to_rx.erase(key);
    _transducer_channel_id_to_trx.erase(key);
}

void SensorConfiguration::unregister_all_transducer_channels()
{
    invalidate_hash_cache();
    _transducer_channel_id_to_tx.clear();
    _transducer_channel_id_to_rx.clear();
    _transducer_channel_id_to_trx.clear();
}

std::pair<std::string, std::string> SensorConfiguration::get_transducer_transmit_id(
    std::string_view      channel_id,
    std::optional<size_t> sector) const
{
    auto it = _transducer_channel_id_to_tx.find(channel_id);
    if (it == _transducer_channel_id_to_tx.end())
        throw std::out_of_range(
            fmt::format("ERROR[SensorConfiguration::get_transducer_transmit_id]: no transducer "
                        "channel '{}' is registered",
                        channel_id));

    const TransducerTransmitChannel& tx = it->second;

    // No sector requested, or no per-sector subarrays registered -> use the default subarray.
    if (!sector.has_value() || tx.sector_subarrays.empty())
        return { tx.tx_id, tx.default_subarray };

    // Per-sector subarrays are registered -> return the subarray of the requested sector.
    if (*sector >= tx.sector_subarrays.size())
        throw std::out_of_range(fmt::format(
            "ERROR[SensorConfiguration::get_transducer_transmit_id]: transmit sector {} is out of "
            "range for channel '{}' ({} sector subarrays registered)",
            *sector,
            channel_id,
            tx.sector_subarrays.size()));

    return { tx.tx_id, tx.sector_subarrays[*sector] };
}

const std::pair<std::string, std::string>& SensorConfiguration::get_transducer_receive_id(
    std::string_view channel_id) const
{
    auto it = _transducer_channel_id_to_rx.find(channel_id);
    if (it == _transducer_channel_id_to_rx.end())
        throw std::out_of_range(
            fmt::format("ERROR[SensorConfiguration::get_transducer_receive_id]: no transducer "
                        "channel '{}' is registered",
                        channel_id));
    return it->second;
}

const std::pair<std::string, std::string>& SensorConfiguration::get_transducer_transmit_receive_id(
    std::string_view channel_id) const
{
    auto it = _transducer_channel_id_to_trx.find(channel_id);
    if (it == _transducer_channel_id_to_trx.end())
        throw std::out_of_range(fmt::format(
            "ERROR[SensorConfiguration::get_transducer_transmit_receive_id]: no transducer "
            "channel '{}' is registered",
            channel_id));
    return it->second;
}

datastructures::SensorPose SensorConfiguration::get_transducer_transmit_target(
    std::string_view      channel_id,
    std::optional<size_t> sector) const
{
    const auto [target_id, subarray_id] = get_transducer_transmit_id(channel_id, sector);
    return get_target(target_id, subarray_id);
}

datastructures::SensorPose SensorConfiguration::get_transducer_receive_target(
    std::string_view channel_id) const
{
    const auto& [target_id, subarray_id] = get_transducer_receive_id(channel_id);
    return get_target(target_id, subarray_id);
}

datastructures::SensorPose SensorConfiguration::get_transducer_transmit_receive_target(
    std::string_view channel_id) const
{
    const auto& [target_id, subarray_id] = get_transducer_transmit_receive_id(channel_id);
    return get_target(target_id, subarray_id);
}

datastructures::SensorPose SensorConfiguration::get_target(
    std::string_view                                 target_id,
    std::string_view                                 subarray_id,
    const std::optional<datastructures::SensorPose>& subarray_pose) const
{
    const auto& target =
        get_target(target_id); // throws a descriptive error if the target is unknown

    if (subarray_pose.has_value())
        return combine_target_subarray(target,
                                       *subarray_pose); // custom offset -> combine on the fly

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

const SensorConfiguration::t_SensorPoseMap& SensorConfiguration::get_targets() const
{
    return _target_offsets;
}

void SensorConfiguration::remove_target(std::string_view target_id)
{
    invalidate_hash_cache();
    const std::string key(target_id);
    _target_offsets.erase(key);
    _target_subarray_offsets.erase(key);
}

void SensorConfiguration::remove_targets()
{
    invalidate_hash_cache();
    _target_offsets.clear();
    _target_subarray_offsets.clear();
    add_target("0", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

bool SensorConfiguration::has_target(std::string_view target_id) const
{
    return _target_offsets.contains(target_id);
}

void SensorConfiguration::add_target(std::string_view                  target_id,
                                     const datastructures::SensorPose& target_offsets)
{
    invalidate_hash_cache();
    _target_offsets[std::string(target_id)] = target_offsets;
}

void SensorConfiguration::add_target(std::string_view target_id,
                                     float            x,
                                     float            y,
                                     float            z,
                                     float            yaw,
                                     float            pitch,
                                     float            roll)
{
    add_target(target_id, datastructures::SensorPose(target_id, x, y, z, yaw, pitch, roll));
}

void SensorConfiguration::add_targets(const t_SensorPoseMap& targets)
{
    for (const auto& target : targets)
        add_target(target.first, target.second);
}

// ----- target subarray offsets -----

std::pair<SensorConfiguration::t_SensorPoseMap, SensorConfiguration::t_SensorPoseMap>
SensorConfiguration::get_model_subarray_offsets(std::string_view model_name)
{
    return navigation::get_model_subarray_offsets(model_name);
}

void SensorConfiguration::add_target_subarray(std::string_view                  target_id,
                                              std::string_view                  subarray_id,
                                              const datastructures::SensorPose& subarray_offsets)
{
    invalidate_hash_cache();
    _target_subarray_offsets[std::string(target_id)][std::string(subarray_id)] = subarray_offsets;
}

void SensorConfiguration::set_target_subarrays(std::string_view       target_id,
                                               const t_SensorPoseMap& subarrays)
{
    invalidate_hash_cache();
    if (subarrays.empty())
        _target_subarray_offsets.erase(std::string(target_id));
    else
        _target_subarray_offsets[std::string(target_id)] = subarrays;
}

bool SensorConfiguration::has_target_subarrays(std::string_view target_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    return it != _target_subarray_offsets.end() && !it->second.empty();
}

bool SensorConfiguration::has_target_subarray(std::string_view target_id,
                                              std::string_view subarray_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    return it != _target_subarray_offsets.end() && it->second.contains(subarray_id);
}

const datastructures::SensorPose& SensorConfiguration::get_target_subarray(
    std::string_view target_id,
    std::string_view subarray_id) const
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

const SensorConfiguration::t_SensorPoseMap& SensorConfiguration::get_target_subarrays(
    std::string_view target_id) const
{
    auto it = _target_subarray_offsets.find(target_id);
    if (it == _target_subarray_offsets.end())
        throw std::out_of_range(fmt::format(
            "ERROR[SensorConfiguration::get_target_subarrays]: target '{}' has no subarray offsets",
            target_id));
    return it->second;
}

std::vector<std::string> SensorConfiguration::get_target_subarray_ids(
    std::string_view target_id) const
{
    std::vector<std::string> ids;
    auto                     it = _target_subarray_offsets.find(target_id);
    if (it != _target_subarray_offsets.end())
        for (const auto& [subarray_id, offsets] : it->second)
            ids.push_back(subarray_id);
    return ids;
}

void SensorConfiguration::remove_target_subarrays(std::string_view target_id)
{
    invalidate_hash_cache();
    _target_subarray_offsets.erase(std::string(target_id));
}

// ----- system metadata -----
void SensorConfiguration::set_model_name(std::string name)
{
    invalidate_hash_cache();
    _model_name = std::move(name);
}
std::string SensorConfiguration::get_model_name() const
{
    return _model_name;
}

void SensorConfiguration::set_transducer_configuration(std::string cfg)
{
    invalidate_hash_cache();
    _transducer_configuration = std::move(cfg);
}
std::string SensorConfiguration::get_transducer_configuration() const
{
    return _transducer_configuration;
}

void SensorConfiguration::set_printer_style(bool row_per_target)
{
    _printer_style_a = row_per_target;
}
bool SensorConfiguration::get_printer_style() const
{
    return _printer_style_a;
}

// ----- get/set sensor offsets -----
void SensorConfiguration::set_attitude_source(std::string_view name,
                                              float            yaw,
                                              float            pitch,
                                              float            roll)
{
    invalidate_hash_cache();
    _offsets_attitude_source = datastructures::SensorPose(name, 0.0, 0.0, 0.0, yaw, pitch, roll);
}
void SensorConfiguration::set_attitude_source(const datastructures::SensorPose& sensor_offsets)
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
void SensorConfiguration::set_heading_source(const datastructures::SensorPose& sensor_offsets)
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
void SensorConfiguration::set_position_source(const datastructures::SensorPose& sensor_offsets)
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

std::vector<std::string> SensorConfiguration::get_target_ids() const
{
    std::vector<std::string> target_ids;
    for (const auto& target : _target_offsets)
        target_ids.push_back(target.first);
    return target_ids;
}

// ----- file I/O -----

void SensorConfiguration::to_stream(std::ostream& os) const
{
    using tools::classhelper::stream::container_to_stream;

    // iterate over _target_offsets to write them to the stream
    unsigned int num_targets = _target_offsets.size();
    os.write(reinterpret_cast<const char*>(&num_targets), sizeof(num_targets));

    for (const auto& target : _target_offsets)
    {
        container_to_stream(os, target.first);
        target.second.to_stream(os);
    }

    _offsets_attitude_source.to_stream(os);
    _offsets_heading_source.to_stream(os);
    _offsets_position_source.to_stream(os);
    _offsets_depth_source.to_stream(os);
    os.write(reinterpret_cast<const char*>(&_waterline_offset), sizeof(_waterline_offset));
    os.write(reinterpret_cast<const char*>(&_position_source_motion_compensated),
             sizeof(_position_source_motion_compensated));

    // subarray offsets: map<target_id, map<subarray_id, SensorPose>>
    unsigned int num_sub_targets = _target_subarray_offsets.size();
    os.write(reinterpret_cast<const char*>(&num_sub_targets), sizeof(num_sub_targets));
    for (const auto& [target_id, subarrays] : _target_subarray_offsets)
    {
        container_to_stream(os, target_id);
        unsigned int num_subarrays = subarrays.size();
        os.write(reinterpret_cast<const char*>(&num_subarrays), sizeof(num_subarrays));
        for (const auto& [subarray_id, offsets] : subarrays)
        {
            container_to_stream(os, subarray_id);
            offsets.to_stream(os);
        }
    }

    container_to_stream(os, _model_name);
    container_to_stream(os, _transducer_configuration);

    unsigned int num_transducer_channels = _transducer_channel_id_to_trx.size();
    os.write(reinterpret_cast<const char*>(&num_transducer_channels),
             sizeof(num_transducer_channels));
    for (const auto& [channel_id, trx_ref] : _transducer_channel_id_to_trx)
    {
        container_to_stream(os, channel_id);

        // transmit: id + default subarray + per-sector subarrays
        const TransducerTransmitChannel& tx = _transducer_channel_id_to_tx.at(channel_id);
        container_to_stream(os, tx.tx_id);
        container_to_stream(os, tx.default_subarray);
        unsigned int num_sectors = tx.sector_subarrays.size();
        os.write(reinterpret_cast<const char*>(&num_sectors), sizeof(num_sectors));
        for (const auto& sector_subarray : tx.sector_subarrays)
            container_to_stream(os, sector_subarray);

        const auto& rx = _transducer_channel_id_to_rx.at(channel_id);
        container_to_stream(os, rx.first);
        container_to_stream(os, rx.second);
        container_to_stream(os, trx_ref.first);
        container_to_stream(os, trx_ref.second);
    }
}

SensorConfiguration SensorConfiguration::from_stream(std::istream& is)
{
    using datastructures::SensorPose;
    using tools::classhelper::stream::container_from_stream;

    SensorConfiguration obj;

    unsigned int num_targets;
    is.read(reinterpret_cast<char*>(&num_targets), sizeof(num_targets));
    while (num_targets--)
    {
        std::string target_id                     = container_from_stream<std::string>(is);
        SensorPose  target_offsets                = SensorPose::from_stream(is);
        obj._target_offsets[std::move(target_id)] = std::move(target_offsets);
    }

    obj._offsets_attitude_source = SensorPose::from_stream(is);
    obj._offsets_heading_source  = SensorPose::from_stream(is);
    obj._offsets_position_source = SensorPose::from_stream(is);
    obj._offsets_depth_source    = SensorPose::from_stream(is);
    is.read(reinterpret_cast<char*>(&obj._waterline_offset), sizeof(obj._waterline_offset));
    is.read(reinterpret_cast<char*>(&obj._position_source_motion_compensated),
            sizeof(obj._position_source_motion_compensated));

    unsigned int num_sub_targets;
    is.read(reinterpret_cast<char*>(&num_sub_targets), sizeof(num_sub_targets));
    while (num_sub_targets--)
    {
        std::string  target_id = container_from_stream<std::string>(is);
        unsigned int num_subarrays;
        is.read(reinterpret_cast<char*>(&num_subarrays), sizeof(num_subarrays));
        t_SensorPoseMap subarrays;
        while (num_subarrays--)
        {
            std::string subarray_id           = container_from_stream<std::string>(is);
            subarrays[std::move(subarray_id)] = SensorPose::from_stream(is);
        }
        obj._target_subarray_offsets[std::move(target_id)] = std::move(subarrays);
    }

    obj._model_name               = container_from_stream<std::string>(is);
    obj._transducer_configuration = container_from_stream<std::string>(is);

    unsigned int num_transducer_channels = 0;
    is.read(reinterpret_cast<char*>(&num_transducer_channels), sizeof(num_transducer_channels));
    while (num_transducer_channels--)
    {
        const std::string channel_id = container_from_stream<std::string>(is);

        TransducerTransmitChannel tx;
        tx.tx_id                 = container_from_stream<std::string>(is);
        tx.default_subarray      = container_from_stream<std::string>(is);
        unsigned int num_sectors = 0;
        is.read(reinterpret_cast<char*>(&num_sectors), sizeof(num_sectors));
        tx.sector_subarrays.reserve(num_sectors);
        while (num_sectors--)
            tx.sector_subarrays.push_back(container_from_stream<std::string>(is));
        obj._transducer_channel_id_to_tx[channel_id] = std::move(tx);

        auto& rx   = obj._transducer_channel_id_to_rx[channel_id];
        rx.first   = container_from_stream<std::string>(is);
        rx.second  = container_from_stream<std::string>(is);
        auto& trx  = obj._transducer_channel_id_to_trx[channel_id];
        trx.first  = container_from_stream<std::string>(is);
        trx.second = container_from_stream<std::string>(is);
    }

    return obj;
}

bool SensorConfiguration::operator==(const SensorConfiguration& other) const
{
    return _target_offsets == other._target_offsets &&
           _offsets_attitude_source == other._offsets_attitude_source &&
           _offsets_heading_source == other._offsets_heading_source &&
           _offsets_position_source == other._offsets_position_source &&
           _offsets_depth_source == other._offsets_depth_source &&
           _waterline_offset == other._waterline_offset &&
           _position_source_motion_compensated == other._position_source_motion_compensated &&
           _target_subarray_offsets == other._target_subarray_offsets &&
           _model_name == other._model_name &&
           _transducer_configuration == other._transducer_configuration &&
           _transducer_channel_id_to_trx == other._transducer_channel_id_to_trx &&
           _transducer_channel_id_to_tx == other._transducer_channel_id_to_tx &&
           _transducer_channel_id_to_rx == other._transducer_channel_id_to_rx;
}

tools::classhelper::ObjectPrinter SensorConfiguration::__printer__(unsigned int float_precision,
                                                                   bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "SensorConfiguration", float_precision, superscript_exponents);

    // Registered transducer channels: the transmit / receive / transmit-receive target ids (and
    // their default subarray, shown as "target (subarray)") each channel_id maps to, plus the per
    // transmit-sector subarrays. Query (keyed by channel_id) via get_transducer_transmit_id,
    // get_transducer_receive_id and get_transducer_transmit_receive_id.
    auto fmt_ref = [](const std::pair<std::string, std::string>& ref) {
        return ref.second.empty() ? ref.first : fmt::format("{} ({})", ref.first, ref.second);
    };
    auto fmt_tx = [](const TransducerTransmitChannel& tx) {
        return tx.default_subarray.empty() ? tx.tx_id
                                           : fmt::format("{} [{}]", tx.tx_id, tx.default_subarray);
    };
    std::vector<std::vector<std::string>> transducer_channels;
    for (const auto& [channel_id, trx_ref] : _transducer_channel_id_to_trx)
    {
        const TransducerTransmitChannel& tx = _transducer_channel_id_to_tx.at(channel_id);
        std::string                      sectors;
        for (size_t i = 0; i < tx.sector_subarrays.size(); ++i)
        {
            if (i)
                sectors += "\n";
            sectors += tx.sector_subarrays[i];
        }
        transducer_channels.push_back({ channel_id,
                                        fmt_tx(tx),
                                        sectors,
                                        fmt_ref(_transducer_channel_id_to_rx.at(channel_id)),
                                        fmt_ref(trx_ref) });
    }
    if (!transducer_channels.empty())
        printer.register_table(
            "Registered transducers (get_transducer_[transmit|receive|transmit_receive]_id)",
            { "channel_id", "transmit_id", "transmit_sectors", "receive_id", "transmit_receive_id" },
            transducer_channels);

    auto fnum       = [&](float v) { return fmt::format("{:.{}f}", v, float_precision); };
    auto pose_cells = [&](const datastructures::SensorPose& p) {
        return std::vector<std::string>{ fnum(p.x),     fnum(p.y),       fnum(p.z),
                                         fnum(p.yaw()), fnum(p.pitch()), fnum(p.roll()) };
    };
    auto make_row = [&](const std::string& label, const datastructures::SensorPose& p) {
        std::vector<std::string> row   = { label };
        auto                     cells = pose_cells(p);
        row.insert(row.end(), cells.begin(), cells.end());
        return row;
    };

    // Stack similar records as an aligned table. Two styles, selectable via set_printer_style /
    // print(optionA=...): style A = one row per record; style B = the transposed layout (fields
    // x/y/z/yaw/pitch/roll as rows, records as columns) which keeps an explanation last column.
    const std::vector<std::string> explanation = { "explanation", "forward, m", "starboard, m",
                                                   "down, m",     "yaw, deg",   "pitch, deg",
                                                   "roll, deg" };
    auto                           add_table = [&](std::string_view                      title,
                         const std::string&                    first_column,
                         std::vector<std::vector<std::string>> rows) {
        if (rows.empty())
            return;
        if (_printer_style_a)
            printer.register_table(
                title, { first_column, "x", "y", "z", "yaw", "pitch", "roll" }, rows);
        else
        {
            rows.push_back(explanation);
            printer.register_table(
                title, { "field", "x", "y", "z", "yaw", "pitch", "roll" }, rows, true);
        }
    };

    std::vector<std::vector<std::string>> targets;
    for (const auto& [id, pose] : _target_offsets)
        targets.push_back(make_row(id, pose));
    add_table("Target offsets", "target", std::move(targets));

    add_table("Sensor offsets",
              "sensor",
              { make_row("attitude", _offsets_attitude_source),
                make_row("compass", _offsets_heading_source),
                make_row("position", _offsets_position_source),
                make_row("depth", _offsets_depth_source) });

    std::vector<std::vector<std::string>> subarrays;
    for (const auto& [target_id, subs] : _target_subarray_offsets)
        for (const auto& [subarray_id, pose] : subs)
            subarrays.push_back(make_row(target_id + " / " + subarray_id, pose));
    add_table("Subarray offsets", "target / subarray", std::move(subarrays));

    printer.register_section("System");
    printer.register_value("waterline_offset", _waterline_offset, "m");
    printer.register_string("position_motion_compensated",
                            _position_source_motion_compensated ? "true" : "false",
                            "position already re reference point");
    if (!_model_name.empty())
        printer.register_string("model", _model_name, "");
    if (!_transducer_configuration.empty())
        printer.register_string("configuration", _transducer_configuration, "");

    return printer;
}

xxh::hash_t<64> SensorConfiguration::binary_hash() const
{
    if (!_cached_binary_hash.has_value())
    {
        xxh::hash3_state_t<64>               hash;
        boost::iostreams::stream<XXHashSink> stream(hash);
        this->to_stream(stream);
        stream.flush();
        _cached_binary_hash = hash.digest();
    }
    return *_cached_binary_hash;
}

std::size_t hash_value(const SensorConfiguration& object)
{
    return object.binary_hash();
}

} // namespace navigation
} // namespace themachinethatgoesping

std::size_t std::hash<themachinethatgoesping::navigation::SensorConfiguration>::operator()(
    const themachinethatgoesping::navigation::SensorConfiguration& object) const
{
    return object.binary_hash();
}
