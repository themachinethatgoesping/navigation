// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocation.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
Geolocation::Geolocation(float z, float yaw, float pitch, float roll)
    : z(z)
    , rotation(yaw, pitch, roll)
{
}

Geolocation::Geolocation(float z, tools::rotationfunctions::Rotation<float> rotation)
    : z(z)
    , rotation(rotation)
{
}

// ----- yaw/pitch/roll accessors -----
float Geolocation::yaw() const { return rotation.ypr()[0]; }
float Geolocation::pitch() const { return rotation.ypr()[1]; }
float Geolocation::roll() const { return rotation.ypr()[2]; }

void Geolocation::set_ypr(float yaw, float pitch, float roll)
{
    rotation = tools::rotationfunctions::Rotation<float>(yaw, pitch, roll);
}
void Geolocation::set_yaw(float yaw)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(yaw, ypr[1], ypr[2]);
}
void Geolocation::set_pitch(float pitch)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(ypr[0], pitch, ypr[2]);
}
void Geolocation::set_roll(float roll)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(ypr[0], ypr[1], roll);
}

// ----- operators -----
bool Geolocation::operator!=(const Geolocation& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool Geolocation::operator==(const Geolocation& rhs) const
{
    return tools::helper::approx(z, rhs.z) && rotation == rhs.rotation;
}

// ----- file I/O -----
Geolocation Geolocation::from_stream(std::istream& is)
{
    Geolocation data;

    is.read(reinterpret_cast<char*>(&data.z), sizeof(float));
    data.rotation = tools::rotationfunctions::Rotation<float>::from_stream(is);

    return data;
}

void Geolocation::to_stream(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&z), sizeof(float));
    rotation.to_stream(os);
}

// ----- printer -----
tools::classhelper::ObjectPrinter Geolocation::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("Geolocation (struct)", float_precision, superscript_exponents);

    const auto ypr = rotation.ypr();
    printer.register_value("z", z, "positive downwards, m");
    printer.register_value("yaw", ypr[0], "90 ° at east");
    printer.register_value("pitch", ypr[1], "° positive bow up");
    printer.register_value("roll", ypr[2], "° positive port up");

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping