// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationlatlonvector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<double> GeolocationLatLonVector::get_latitudes() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.latitude);
    }
    return result;
}

std::vector<double> GeolocationLatLonVector::get_longitudes() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.longitude);
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_z() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.z);
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_yaw() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.yaw());
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_pitch() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.pitch());
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_roll() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.roll());
    }
    return result;
}

// ----- file I/O -----
GeolocationLatLonVector GeolocationLatLonVector::from_stream(std::istream& is)
{
    GeolocationLatLonVector result;
    result.read_from_stream(is);
    return result;
}

void GeolocationLatLonVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter GeolocationLatLonVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "GeolocationLatLonVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
