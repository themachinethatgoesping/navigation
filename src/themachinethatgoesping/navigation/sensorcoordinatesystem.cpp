// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensorcoordinatesystem.hpp"

namespace themachinethatgoesping {
namespace navigation {

// ----- compute_target_position -----

navdata::GeoLocationLocal SensorCoordinateSystem::compute_target_position(
    const std::string&         target_id,
    const navdata::SensorData& sensor_data) const
{
    navdata::GeoLocationLocal location;

    // first get the current roation of the vessel
    auto vessel_quat =
        get_vessel_ypr_as_quat(sensor_data, _compass_offsets, _motion_sensor_offsets);

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

    // coompute target xy
    location.northing = target_xyz[0] - positionSystem_xyz[0];
    location.easting  = target_xyz[1] - positionSystem_xyz[1];

    return location;
}

navdata::GeoLocationLocal SensorCoordinateSystem::compute_target_position(
    const std::string&              target_id,
    const navdata::SensorDataLocal& sensor_data) const
{
    auto position = compute_target_position(target_id, navdata::SensorData(sensor_data));

    // coompute target xy
    position.northing += sensor_data.gps_northing;
    position.easting += sensor_data.gps_easting;

    return position;
}

navdata::GeoLocationUTM SensorCoordinateSystem::compute_target_position(
    const std::string&            target_id,
    const navdata::SensorDataUTM& sensor_data) const
{
    auto position = compute_target_position(target_id, navdata::SensorDataLocal(sensor_data));

    return navdata::GeoLocationUTM(
        position, sensor_data.gps_zone, sensor_data.gps_northern_hemisphere);
}

navdata::GeoLocationLatLon SensorCoordinateSystem::compute_target_position(
    const std::string&               target_id,
    const navdata::SensorDataLatLon& sensor_data) const
{
    // compute position from SensorData (no x,y or lat,lon coordinates)
    // this posion is thus referenced to the gps antenna (0,0), which allows to compute
    // distance and azimuth if target towards the gps antenna
    auto position = compute_target_position(target_id, navdata::SensorData(sensor_data));

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
    return navdata::GeoLocationLatLon(position, target_lat, target_lon);
}

// ----- get/set target offsets -----
const navdata::PositionalOffsets& SensorCoordinateSystem::get_target_offsets(
    const std::string& target_id) const
{
    return _TargetOffsets.at(
        _TargetOffsetIDs.at(target_id)); // throws std::out_of_range if not found
}

const navdata::PositionalOffsets& SensorCoordinateSystem::get_target_offsets(size_t target_id) const
{
    return _TargetOffsets.at(target_id); // throws std::out_of_range if not found
}

void SensorCoordinateSystem::set_target_offsets(const std::string&                target_id,
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

void SensorCoordinateSystem::set_target_offsets(const std::string& target_id,
                                                double             x,
                                                double             y,
                                                double             z,
                                                double             yaw,
                                                double             pitch,
                                                double             roll)
{
    set_target_offsets(target_id, navdata::PositionalOffsets(x, y, z, yaw, pitch, roll));
}

} // namespace navigation
} // namespace themachinethatgoesping
