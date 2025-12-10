// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationvector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<float> GeolocationVector::get_z() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.z);
    }
    return result;
}

std::vector<float> GeolocationVector::get_yaw() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.yaw);
    }
    return result;
}

std::vector<float> GeolocationVector::get_pitch() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& geo : _data)
    {
        result.push_back(geo.pitch);
    }
    return result;
}

std::vector<float> GeolocationVector::get_roll() const
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
GeolocationVector GeolocationVector::from_stream(std::istream& is)
{
    GeolocationVector result;
    result.read_from_stream(is);
    return result;
}

void GeolocationVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter GeolocationVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "GeolocationVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
