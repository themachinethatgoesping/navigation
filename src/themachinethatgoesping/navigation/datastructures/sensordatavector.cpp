// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatavector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<float> SensordataVector::get_depths() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.depth);
    }
    return result;
}

std::vector<float> SensordataVector::get_heaves() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heave);
    }
    return result;
}

std::vector<float> SensordataVector::get_headings() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heading);
    }
    return result;
}

std::vector<float> SensordataVector::get_pitches() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.pitch);
    }
    return result;
}

std::vector<float> SensordataVector::get_rolls() const
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
SensordataVector SensordataVector::from_stream(std::istream& is)
{
    SensordataVector result;
    result.read_from_stream(is);
    return result;
}

void SensordataVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensordataVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "SensordataVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
