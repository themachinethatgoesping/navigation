// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationlocal.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// Constructor implementations
GeolocationLocal::GeolocationLocal(Geolocation location, double northing, double easting)
    : Geolocation(std::move(location))
    , northing(northing)
    , easting(easting)
{
}

GeolocationLocal::GeolocationLocal(double northing,
                                   double easting,
                                   float z,
                                   float yaw,
                                   float pitch,
                                   float roll)
    : Geolocation(z, yaw, pitch, roll)
    , northing(northing)
    , easting(easting)
{
}

// Operator implementations
bool GeolocationLocal::operator!=(const GeolocationLocal& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool GeolocationLocal::operator==(const GeolocationLocal& rhs) const
{
    if (Geolocation::operator==(rhs))
        if (tools::helper::approx(northing, rhs.northing))
            if (tools::helper::approx(easting, rhs.easting))
                return true;

    return false;
}

// I/O implementations
GeolocationLocal GeolocationLocal::from_stream(std::istream& is)
{
    GeolocationLocal data(Geolocation::from_stream(is), 0., 0.);

    is.read(reinterpret_cast<char*>(&data.northing), 2 * sizeof(double));

    return data;
}

void GeolocationLocal::to_stream(std::ostream& os) const
{
    Geolocation::to_stream(os);
    os.write(reinterpret_cast<const char*>(&northing), 2 * sizeof(double));
}

// Printer implementation
tools::classhelper::ObjectPrinter GeolocationLocal::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("GeolocationLocal (struct)", float_precision, superscript_exponents);

    printer.register_value("northing", northing, "positive northwards, m");
    printer.register_value("easting", easting, "positive eastwards, m");

    printer.append(Geolocation::__printer__(float_precision, superscript_exponents));

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping