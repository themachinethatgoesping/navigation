// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordata.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// Constructor implementations
Sensordata::Sensordata(float depth, float heave, float heading, float pitch, float roll)
    : depth(depth)
    , heave(heave)
    , heading(heading)
    , pitch(pitch)
    , roll(roll)
{
}

// Operator implementations
bool Sensordata::operator!=(const Sensordata& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool Sensordata::operator==(const Sensordata& rhs) const
{
    if (tools::helper::approx(depth, rhs.depth))
        if (tools::helper::approx(heave, rhs.heave))
            if (tools::helper::approx(heading, rhs.heading))
                if (tools::helper::approx(pitch, rhs.pitch))
                    if (tools::helper::approx(roll, rhs.roll))
                        return true;

    return false;
}

// I/O implementations
Sensordata Sensordata::from_stream(std::istream& is)
{
    Sensordata data;

    is.read(reinterpret_cast<char*>(&data.depth), 5 * sizeof(float));

    return data;
}

void Sensordata::to_stream(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&depth), 5 * sizeof(float));
}

// Printer implementation
tools::classhelper::ObjectPrinter Sensordata::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("Sensordata (struct)", float_precision, superscript_exponents);

    printer.register_value("depth", depth, "positive downwards, m");
    printer.register_value("heave", heave, "positive upwards, m");
    printer.register_value("heading", heading, "0° is north, 90 ° is east");
    printer.register_value("pitch", pitch, "° positive bow up");
    printer.register_value("roll", roll, "° positive port up");

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping