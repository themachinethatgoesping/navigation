// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "navigationinterpolatorlatlon.hpp"

#include <cctype>
#include <stdexcept>
#include <themachinethatgoesping/tools/classhelper/classversion.hpp>

namespace themachinethatgoesping {
namespace navigation {

// ----- constructors -----
NavigationInterpolatorLatLon::NavigationInterpolatorLatLon(SensorConfiguration sensor_configuration,
                                                           tools::vectorinterpolators::o_extr_mode extrapolation_mode)
    : I_NavigationInterpolator(std::move(sensor_configuration), extrapolation_mode)
{
    set_extrapolation_mode(extrapolation_mode);
}

NavigationInterpolatorLatLon::NavigationInterpolatorLatLon(I_NavigationInterpolator base)
    : I_NavigationInterpolator(std::move(base))
{
    set_extrapolation_mode(base.interpolator_depth().get_extrapolation_mode());
}

// ----- set extrapolation mode -----
void NavigationInterpolatorLatLon::set_extrapolation_mode(tools::vectorinterpolators::o_extr_mode extrapolation_mode)
{
    I_NavigationInterpolator::set_extrapolation_mode(extrapolation_mode);

    _interpolator_latitude.set_extrapolation_mode(extrapolation_mode);
    _interpolator_longitude.set_extrapolation_mode(extrapolation_mode);
}

// ----- operators -----
bool NavigationInterpolatorLatLon::operator==(const NavigationInterpolatorLatLon& other) const
{
    return _interpolator_latitude == other._interpolator_latitude &&
           _interpolator_longitude == other._interpolator_longitude &&
           I_NavigationInterpolator::operator==(other);
}

bool NavigationInterpolatorLatLon::operator!=(const NavigationInterpolatorLatLon& other) const 
{ 
    return !(*this == other); 
}

// ----- set sensor data -----
void NavigationInterpolatorLatLon::set_data_position(const std::vector<double>& timestamp,
                                                     const std::vector<double>& latitude,
                                                     const std::vector<double>& longitude)
{
    invalidate_hash_cache();
    _interpolator_latitude.set_data_XY(timestamp, latitude);
    _interpolator_longitude.set_data_XY(timestamp, longitude);
}

// ----- merge interpolators -----
void NavigationInterpolatorLatLon::merge(const NavigationInterpolatorLatLon& other)
{
    // Note: I_NavigationInterpolator::merge already calls invalidate_hash_cache()
    I_NavigationInterpolator::merge(other);

    // merge data
    _interpolator_latitude.insert(other._interpolator_latitude.get_data_X(),
                                  other._interpolator_latitude.get_data_Y(),
                                  true);
    _interpolator_longitude.insert(other._interpolator_longitude.get_data_X(),
                                   other._interpolator_longitude.get_data_Y(),
                                   true);
}

// ----- compute the position of the target sensors -----
datastructures::GeolocationLatLon NavigationInterpolatorLatLon::operator()(const std::string& target_id,
                                                                           double             timestamp) const
{
    return _sensor_configuration.compute_target_position(target_id, get_sensor_data(timestamp));
}

datastructures::GeolocationLatLonVector NavigationInterpolatorLatLon::operator()(
    const std::string&         target_id,
    const std::vector<double>& timestamps,
    int                        mp_cores) const
{
    datastructures::GeolocationLatLonVector result;
    result.timestamps() = timestamps;
    result.data().resize(timestamps.size());

    const auto n = static_cast<long>(timestamps.size());

#pragma omp parallel for num_threads(mp_cores)
    for (long i = 0; i < n; ++i)
    {
        result.data()[i] = compute_target_position(target_id, timestamps[i]);
    }

    return result;
}

datastructures::GeolocationLatLonVector NavigationInterpolatorLatLon::operator()(
    const std::string&            target_id,
    const xt::xtensor<double, 1>& timestamps,
    int                           mp_cores) const
{
    datastructures::GeolocationLatLonVector result;
    result.timestamps().assign(timestamps.begin(), timestamps.end());
    result.data().resize(timestamps.size());

    const auto n = static_cast<long>(timestamps.size());

#pragma omp parallel for num_threads(mp_cores)
    for (long i = 0; i < n; ++i)
    {
        result.data()[i] = compute_target_position(target_id, timestamps(i));
    }

    return result;
}

datastructures::GeolocationLatLon NavigationInterpolatorLatLon::compute_target_position(const std::string& target_id,
                                                                                        double             timestamp) const
{
    return _sensor_configuration.compute_target_position(target_id, get_sensor_data(timestamp));
}

datastructures::GeolocationLatLonVector NavigationInterpolatorLatLon::compute_target_position(
    const std::string&         target_id,
    const std::vector<double>& timestamps,
    int                        mp_cores) const
{
    return operator()(target_id, timestamps, mp_cores);
}

datastructures::GeolocationLatLonVector NavigationInterpolatorLatLon::compute_target_position(
    const std::string&            target_id,
    const xt::xtensor<double, 1>& timestamps,
    int                           mp_cores) const
{
    return operator()(target_id, timestamps, mp_cores);
}

datastructures::SensordataLatLon NavigationInterpolatorLatLon::get_sensor_data(double timestamp) const
{
    datastructures::SensordataLatLon sensor_data;
    if (!_interpolator_depth.empty()) // default is 0.0
        sensor_data.depth = _interpolator_depth(timestamp);

    if (!_interpolator_heave.empty()) // default is 0.0
        sensor_data.heave = _interpolator_heave(timestamp);

    if (!_interpolator_heading.empty()) // default is 0.0
        sensor_data.heading = _interpolator_heading.ypr(timestamp)[0];

    if (!_interpolator_attitude.empty()) // default is 0.0. 0.0
    {
        auto ypr = _interpolator_attitude.ypr(timestamp);
        // sensor_data.imu_yaw   = ypr[0];
        sensor_data.pitch = ypr[1];
        sensor_data.roll  = ypr[2];
    }

    if (_interpolator_latitude.empty())
        throw std::runtime_error("ERROR[datastructures::SensordataLatLon]: No latitude data "
                                 "available for interpolation");

    if (_interpolator_longitude.empty())
        throw std::runtime_error("ERROR[datastructures::SensordataLatLon]: No longitude data "
                                 "available for interpolation");

    sensor_data.latitude  = _interpolator_latitude(timestamp);
    sensor_data.longitude = _interpolator_longitude(timestamp);

    return sensor_data;
}

datastructures::SensordataLatLonVector NavigationInterpolatorLatLon::get_sensor_data(
    const std::vector<double>& timestamps,
    int                        mp_cores) const
{
    datastructures::SensordataLatLonVector result;
    result.timestamps() = timestamps;
    result.data().resize(timestamps.size());

    const auto n = static_cast<long>(timestamps.size());

#pragma omp parallel for num_threads(mp_cores)
    for (long i = 0; i < n; ++i)
    {
        result.data()[i] = get_sensor_data(timestamps[i]);
    }

    return result;
}

datastructures::SensordataLatLonVector NavigationInterpolatorLatLon::get_sensor_data(
    const xt::xtensor<double, 1>& timestamps,
    int                           mp_cores) const
{
    datastructures::SensordataLatLonVector result;
    result.timestamps().assign(timestamps.begin(), timestamps.end());
    result.data().resize(timestamps.size());

    const auto n = static_cast<long>(timestamps.size());

#pragma omp parallel for num_threads(mp_cores)
    for (long i = 0; i < n; ++i)
    {
        result.data()[i] = get_sensor_data(timestamps(i));
    }

    return result;
}

bool NavigationInterpolatorLatLon::valid() const
{
    return I_NavigationInterpolator::valid() &&
           (!_interpolator_latitude.empty() && !_interpolator_longitude.empty());
}

// ----- get sampled timestamps -----
xt::xtensor<double, 1> NavigationInterpolatorLatLon::get_sampled_timestamps(
    double                downsample_interval,
    double                max_gap,
    std::set<std::string> sensor_names) const
{
    std::vector<xt::xtensor<double, 1>> timestamp_vectors;
    for (const auto& sensor_name : sensor_names)
    {
        // make a lowercase copy of the sensor name for case-insensitive comparison
        std::string key = sensor_name;
        for (auto& ch : key)
        {
            ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }

        if (key == "latitude")
        {
            timestamp_vectors.push_back(
                _interpolator_latitude.get_sampled_X(downsample_interval, max_gap));
        }
        else if (key == "longitude")
        {
            timestamp_vectors.push_back(
                _interpolator_longitude.get_sampled_X(downsample_interval, max_gap));
        }
        else if (key == "attitude")
        {
            timestamp_vectors.push_back(
                _interpolator_attitude.get_sampled_X(downsample_interval, max_gap));
        }
        else if (key == "heading")
        {
            timestamp_vectors.push_back(
                _interpolator_heading.get_sampled_X(downsample_interval, max_gap));
        }
        else if (key == "heave")
        {
            timestamp_vectors.push_back(
                _interpolator_heave.get_sampled_X(downsample_interval, max_gap));
        }
        else if (key == "depth")
        {
            timestamp_vectors.push_back(
                _interpolator_depth.get_sampled_X(downsample_interval, max_gap));
        }
        else
        {
            throw std::invalid_argument(
                "NavigationInterpolatorLatLon::get_sampled_timestamps: Unknown sensor name '" +
                sensor_name +
                "'!\nTry any of: latitude, longitude, attitude, heading, heave, depth.");
        }
    }

    if (timestamp_vectors.empty())
    {
        return xt::xtensor<double, 1>{};
    }

    const auto common_timestamps =
        tools::helper::cut_to_shared_sections(timestamp_vectors, max_gap);

    return common_timestamps.at(0);
}

// ----- printer -----
tools::classhelper::ObjectPrinter NavigationInterpolatorLatLon::__printer__(unsigned int float_precision,
                                                                             bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        this->class_name(), float_precision, superscript_exponents);

    printer.append(
        I_NavigationInterpolator::__printer__(float_precision, superscript_exponents));

    printer.register_section("Position system latitude", '*');
    printer.append(_interpolator_latitude.__printer__(float_precision, superscript_exponents),
                   true);

    printer.register_section("Position system longitude", '*');
    printer.append(_interpolator_longitude.__printer__(float_precision, superscript_exponents),
                   true);

    return printer;
}

// ----- file I/O -----
NavigationInterpolatorLatLon NavigationInterpolatorLatLon::from_stream(std::istream& is)
{
    tools::classhelper::read_version(is, "NavIntLatLon_V1", "NavigationInterpolatorLatLon");
    NavigationInterpolatorLatLon interpolator(I_NavigationInterpolator::from_stream(is));

    interpolator._interpolator_latitude  = interpolator._interpolator_latitude.from_stream(is);
    interpolator._interpolator_longitude = interpolator._interpolator_longitude.from_stream(is);

    return interpolator;
}

void NavigationInterpolatorLatLon::to_stream(std::ostream& os) const
{
    tools::classhelper::write_version(os, "NavIntLatLon_V1");
    I_NavigationInterpolator::to_stream(os);

    _interpolator_latitude.to_stream(os);
    _interpolator_longitude.to_stream(os);
}

// ----- hash function -----
std::size_t hash_value(const themachinethatgoesping::navigation::NavigationInterpolatorLatLon& object)
{
    return object.binary_hash();
}

} // namespace navigation
} // namespace themachinethatgoesping

// ----- std::hash specialization -----
std::size_t std::hash<themachinethatgoesping::navigation::NavigationInterpolatorLatLon>::operator()(
    const themachinethatgoesping::navigation::NavigationInterpolatorLatLon& object) const
{
    return object.binary_hash();
}