// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "navigationinterpolatorlocal.hpp"

#include <cctype>
#include <stdexcept>
#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

namespace themachinethatgoesping {
namespace navigation {

// ----- constructors -----
NavigationInterpolatorLocal::NavigationInterpolatorLocal(SensorConfiguration sensor_configuration,
                                                         tools::vectorinterpolators::o_extr_mode extrapolation_mode)
    : I_NavigationInterpolator(std::move(sensor_configuration), extrapolation_mode)
{
    set_extrapolation_mode(extrapolation_mode);
}

NavigationInterpolatorLocal::NavigationInterpolatorLocal(I_NavigationInterpolator base)
    : I_NavigationInterpolator(std::move(base))
{
    set_extrapolation_mode(base.interpolator_depth().get_extrapolation_mode());
}

// ----- set extrapolation mode -----
void NavigationInterpolatorLocal::set_extrapolation_mode(tools::vectorinterpolators::o_extr_mode extrapolation_mode)
{
    I_NavigationInterpolator::set_extrapolation_mode(extrapolation_mode);

    _interpolator_northing.set_extrapolation_mode(extrapolation_mode);
    _interpolator_easting.set_extrapolation_mode(extrapolation_mode);
}

// ----- operators -----
bool NavigationInterpolatorLocal::operator==(const NavigationInterpolatorLocal& other) const
{
    return _interpolator_northing == other._interpolator_northing &&
           _interpolator_easting == other._interpolator_easting &&
           I_NavigationInterpolator::operator==(other);
}

bool NavigationInterpolatorLocal::operator!=(const NavigationInterpolatorLocal& other) const 
{ 
    return !(*this == other); 
}

// ----- set sensor data -----
void NavigationInterpolatorLocal::set_data_position(const std::vector<double>& timestamp,
                                                    const std::vector<double>& northing,
                                                    const std::vector<double>& easting)
{
    _interpolator_northing.set_data_XY(timestamp, northing);
    _interpolator_easting.set_data_XY(timestamp, easting);
}

void NavigationInterpolatorLocal::set_data_position(const std::vector<double>& timestamp,
                                                    const std::vector<double>& northing,
                                                    const std::vector<double>& easting,
                                                    std::string_view           name,
                                                    float                      offset_x,
                                                    float                      offset_y,
                                                    float                      offset_z)
{
    _sensor_configuration.set_position_source(name, offset_x, offset_y, offset_z);
    set_data_position(timestamp, northing, easting);
}

void NavigationInterpolatorLocal::set_data_position(const std::vector<double>&               timestamp,
                                                    const std::vector<double>&               northing,
                                                    const std::vector<double>&               easting,
                                                    const datastructures::PositionalOffsets& sensor_offsets)
{
    _sensor_configuration.set_position_source(sensor_offsets);
    set_data_position(timestamp, northing, easting);
}

// ----- merge interpolators -----
void NavigationInterpolatorLocal::merge(const NavigationInterpolatorLocal& other)
{
    I_NavigationInterpolator::merge(other);

    // merge data
    _interpolator_northing.insert(other._interpolator_northing.get_data_X(),
                                  other._interpolator_northing.get_data_Y(),
                                  true);
    _interpolator_easting.insert(other._interpolator_easting.get_data_X(),
                                 other._interpolator_easting.get_data_Y(),
                                 true);
}

// ----- compute the position of the target sensors -----
datastructures::GeolocationLocal NavigationInterpolatorLocal::compute_target_position(const std::string& target_id,
                                                                                       double             timestamp) const
{
    return _sensor_configuration.compute_target_position(target_id, get_sensor_data(timestamp));
}

datastructures::GeolocationLocalVector NavigationInterpolatorLocal::compute_target_position(
    const std::string&         target_id,
    const std::vector<double>& timestamps,
    int                        mp_cores) const
{
    datastructures::GeolocationLocalVector result;
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

datastructures::GeolocationLocalVector NavigationInterpolatorLocal::compute_target_position(
    const std::string&            target_id,
    const xt::xtensor<double, 1>& timestamps,
    int                           mp_cores) const
{
    datastructures::GeolocationLocalVector result;
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

datastructures::SensordataLocal NavigationInterpolatorLocal::get_sensor_data(double timestamp) const
{
    datastructures::SensordataLocal sensor_data;
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

    sensor_data.northing = _interpolator_northing(timestamp);
    sensor_data.easting  = _interpolator_easting(timestamp);

    return sensor_data;
}

datastructures::SensordataLocalVector NavigationInterpolatorLocal::get_sensor_data(
    const std::vector<double>& timestamps,
    int                        mp_cores) const
{
    datastructures::SensordataLocalVector result;
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

datastructures::SensordataLocalVector NavigationInterpolatorLocal::get_sensor_data(
    const xt::xtensor<double, 1>& timestamps,
    int                           mp_cores) const
{
    datastructures::SensordataLocalVector result;
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

bool NavigationInterpolatorLocal::valid() const
{
    return I_NavigationInterpolator::valid() &&
           (!_interpolator_northing.empty() && !_interpolator_easting.empty());
}

// ----- get sampled timestamps -----
xt::xtensor<double, 1> NavigationInterpolatorLocal::get_sampled_timestamps(
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

        if (key == "northing")
        {
            timestamp_vectors.push_back(
                _interpolator_northing.get_sampled_X(downsample_interval, max_gap));
        }
        else if (key == "easting")
        {
            timestamp_vectors.push_back(
                _interpolator_easting.get_sampled_X(downsample_interval, max_gap));
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
                "NavigationInterpolatorLocal::get_sampled_timestamps: Unknown sensor name '" +
                sensor_name +
                "'!\nTry any of: northing, easting, attitude, heading, heave, depth.");
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
tools::classhelper::ObjectPrinter NavigationInterpolatorLocal::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(this->class_name(), float_precision, superscript_exponents);

    printer.append(I_NavigationInterpolator::__printer__(float_precision, superscript_exponents));

    printer.register_section("Position system northing", '*');
    printer.append(_interpolator_northing.__printer__(float_precision, superscript_exponents), true);

    printer.register_section("Position system easting", '*');
    printer.append(_interpolator_easting.__printer__(float_precision, superscript_exponents), true);

    return printer;
}

// ----- file I/O -----
NavigationInterpolatorLocal NavigationInterpolatorLocal::from_stream(std::istream& is)
{
    tools::classhelper::read_version(is, "NavIntLocal_V1", "NavigationInterpolatorLocal");
    NavigationInterpolatorLocal interpolator(I_NavigationInterpolator::from_stream(is));

    interpolator._interpolator_northing = interpolator._interpolator_northing.from_stream(is);
    interpolator._interpolator_easting  = interpolator._interpolator_easting.from_stream(is);

    return interpolator;
}

void NavigationInterpolatorLocal::to_stream(std::ostream& os) const
{
    tools::classhelper::write_version(os, "NavIntLocal_V1");
    I_NavigationInterpolator::to_stream(os);

    _interpolator_northing.to_stream(os);
    _interpolator_easting.to_stream(os);
}

} // namespace navigation
} // namespace themachinethatgoesping