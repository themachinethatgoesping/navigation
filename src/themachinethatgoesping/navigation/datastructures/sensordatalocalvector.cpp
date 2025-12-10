// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatalocalvector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<double> SensordataLocalVector::get_northings() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.northing);
    }
    return result;
}

std::vector<double> SensordataLocalVector::get_eastings() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.easting);
    }
    return result;
}

std::vector<float> SensordataLocalVector::get_depths() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.depth);
    }
    return result;
}

std::vector<float> SensordataLocalVector::get_heaves() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heave);
    }
    return result;
}

std::vector<float> SensordataLocalVector::get_headings() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heading);
    }
    return result;
}

std::vector<float> SensordataLocalVector::get_pitches() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.pitch);
    }
    return result;
}

std::vector<float> SensordataLocalVector::get_rolls() const
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
SensordataLocalVector SensordataLocalVector::from_stream(std::istream& is)
{
    SensordataLocalVector result;
    result.read_from_stream(is);
    return result;
}

void SensordataLocalVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensordataLocalVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "SensordataLocalVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
