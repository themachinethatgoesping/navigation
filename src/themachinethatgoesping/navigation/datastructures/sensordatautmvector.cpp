// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatautmvector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<double> SensordataUTMVector::get_northings() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.northing);
    }
    return result;
}

std::vector<double> SensordataUTMVector::get_eastings() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.easting);
    }
    return result;
}

std::vector<int> SensordataUTMVector::get_utm_zones() const
{
    std::vector<int> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.utm_zone);
    }
    return result;
}

std::vector<bool> SensordataUTMVector::get_northern_hemispheres() const
{
    std::vector<bool> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.northern_hemisphere);
    }
    return result;
}

std::vector<float> SensordataUTMVector::get_depths() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.depth);
    }
    return result;
}

std::vector<float> SensordataUTMVector::get_heaves() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heave);
    }
    return result;
}

std::vector<float> SensordataUTMVector::get_headings() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heading);
    }
    return result;
}

std::vector<float> SensordataUTMVector::get_pitches() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.pitch);
    }
    return result;
}

std::vector<float> SensordataUTMVector::get_rolls() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.roll);
    }
    return result;
}

// ----- file I/O -----
SensordataUTMVector SensordataUTMVector::from_stream(std::istream& is)
{
    SensordataUTMVector result;
    result.read_from_stream(is);
    return result;
}

void SensordataUTMVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensordataUTMVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "SensordataUTMVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
