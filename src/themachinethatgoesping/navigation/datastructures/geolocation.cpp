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
    , yaw(yaw)
    , pitch(pitch)
    , roll(roll)
{
}

// ----- operators -----
bool Geolocation::operator!=(const Geolocation& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool Geolocation::operator==(const Geolocation& rhs) const
{
    using tools::helper::approx;

    if (approx(z, rhs.z))
        if (approx(yaw, rhs.yaw))
            if (approx(pitch, rhs.pitch))
                if (approx(roll, rhs.roll))
                    return true;

    return false;
}

// ----- file I/O -----
Geolocation Geolocation::from_stream(std::istream& is)
{
    Geolocation data;

    is.read(reinterpret_cast<char*>(&data.z), 4 * sizeof(float));

    return data;
}

void Geolocation::to_stream(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&z), 4 * sizeof(float));
}

// ----- printer -----
tools::classhelper::ObjectPrinter Geolocation::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("Geolocation (struct)", float_precision, superscript_exponents);

    printer.register_value("z", z, "positive downwards, m");
    printer.register_value("yaw", yaw, "90 ° at east");
    printer.register_value("pitch", pitch, "° positive bow up");
    printer.register_value("roll", roll, "° positive port up");

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping