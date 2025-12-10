// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatallatlonvector.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- component-wise access -----
std::vector<double> SensordataLatLonVector::get_latitudes() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.latitude);
    }
    return result;
}

std::vector<double> SensordataLatLonVector::get_longitudes() const
{
    std::vector<double> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.longitude);
    }
    return result;
}

std::vector<float> SensordataLatLonVector::get_depths() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.depth);
    }
    return result;
}

std::vector<float> SensordataLatLonVector::get_heaves() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heave);
    }
    return result;
}

std::vector<float> SensordataLatLonVector::get_headings() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.heading);
    }
    return result;
}

std::vector<float> SensordataLatLonVector::get_pitches() const
{
    std::vector<float> result;
    result.reserve(_data.size());
    for (const auto& sd : _data)
    {
        result.push_back(sd.pitch);
    }
    return result;
}

std::vector<float> SensordataLatLonVector::get_rolls() const
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
SensordataLatLonVector SensordataLatLonVector::from_stream(std::istream& is)
{
    SensordataLatLonVector result;
    result.read_from_stream(is);
    return result;
}

void SensordataLatLonVector::to_stream(std::ostream& os) const
{
    write_to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensordataLatLonVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "SensordataLatLonVector", float_precision, superscript_exponents);

    add_base_info_to_printer(printer);

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
