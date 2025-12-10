// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationutmvector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<double> GeolocationUTMVector::get_northings() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.northing);
    }
    return result;
}

std::vector<double> GeolocationUTMVector::get_eastings() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.easting);
    }
    return result;
}

std::vector<int> GeolocationUTMVector::get_utm_zones() const
{
    std::vector<int> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.utm_zone);
    }
    return result;
}

std::vector<bool> GeolocationUTMVector::get_northern_hemispheres() const
{
    std::vector<bool> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.northern_hemisphere);
    }
    return result;
}

std::vector<float> GeolocationUTMVector::get_z() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.z);
    }
    return result;
}

std::vector<float> GeolocationUTMVector::get_yaw() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.yaw);
    }
    return result;
}

std::vector<float> GeolocationUTMVector::get_pitch() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.pitch);
    }
    return result;
}

std::vector<float> GeolocationUTMVector::get_roll() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.roll);
    }
    return result;
}

// ----- file I/O -----
GeolocationUTMVector GeolocationUTMVector::from_stream(std::istream& is)
{
    GeolocationUTMVector result;
    result.read_from_stream(is);
    return result;
}

void GeolocationUTMVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter GeolocationUTMVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "GeolocationUTMVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
