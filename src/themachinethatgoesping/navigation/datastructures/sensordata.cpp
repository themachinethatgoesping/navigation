// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordata.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
Sensordata::Sensordata(float depth, float heave, float heading, float pitch, float roll)
    : depth(depth)
    , heave(heave)
    , rotation(heading, pitch, roll)
{
}

Sensordata::Sensordata(float depth, float heave, tools::rotationfunctions::Rotation<float> rotation)
    : depth(depth)
    , heave(heave)
    , rotation(rotation)
{
}

// ----- heading/pitch/roll accessors -----
float Sensordata::heading() const { return rotation.ypr()[0]; }
float Sensordata::pitch() const { return rotation.ypr()[1]; }
float Sensordata::roll() const { return rotation.ypr()[2]; }

void Sensordata::set_ypr(float heading, float pitch, float roll)
{
    rotation = tools::rotationfunctions::Rotation<float>(heading, pitch, roll);
}
void Sensordata::set_heading(float heading)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(heading, ypr[1], ypr[2]);
}
void Sensordata::set_pitch(float pitch)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(ypr[0], pitch, ypr[2]);
}
void Sensordata::set_roll(float roll)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(ypr[0], ypr[1], roll);
}

// ----- operators -----
bool Sensordata::operator!=(const Sensordata& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool Sensordata::operator==(const Sensordata& rhs) const
{
    using tools::helper::approx;
    return approx(depth, rhs.depth) && approx(heave, rhs.heave) && rotation == rhs.rotation;
}

// ----- file I/O -----
Sensordata Sensordata::from_stream(std::istream& is)
{
    Sensordata data;

    is.read(reinterpret_cast<char*>(&data.depth), 2 * sizeof(float));
    data.rotation = tools::rotationfunctions::Rotation<float>::from_stream(is);

    return data;
}

void Sensordata::to_stream(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&depth), 2 * sizeof(float));
    rotation.to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter Sensordata::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("Sensordata (struct)", float_precision, superscript_exponents);

    const auto ypr = rotation.ypr();
    printer.register_value("depth", depth, "positive downwards, m");
    printer.register_value("heave", heave, "positive upwards, m");
    printer.register_value("heading", ypr[0], "0° is north, 90 ° is east");
    printer.register_value("pitch", ypr[1], "° positive bow up");
    printer.register_value("roll", ypr[2], "° positive port up");

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping