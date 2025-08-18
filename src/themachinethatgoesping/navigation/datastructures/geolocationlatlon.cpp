// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationlatlon.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

#include "../navtools.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
GeolocationLatLon::GeolocationLatLon(Geolocation location, double latitude, double longitude)
    : Geolocation(std::move(location))
    , latitude(latitude)
    , longitude(longitude)
{
}

GeolocationLatLon::GeolocationLatLon(double latitude,
                                    double longitude,
                                    float  z,
                                    float  yaw,
                                    float  pitch,
                                    float  roll)
    : Geolocation(z, yaw, pitch, roll)
    , latitude(latitude)
    , longitude(longitude)
{
}

// ----- operators -----
bool GeolocationLatLon::operator!=(const GeolocationLatLon& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool GeolocationLatLon::operator==(const GeolocationLatLon& other) const
{
    if (Geolocation::operator==(other))
        if (tools::helper::approx(latitude, other.latitude))
            if (tools::helper::approx(longitude, other.longitude))
                return true;

    return false;
}

// ----- file I/O -----
GeolocationLatLon GeolocationLatLon::from_stream(std::istream& is)
{
    GeolocationLatLon data(Geolocation::from_stream(is), 0., 0.);

    is.read(reinterpret_cast<char*>(&data.latitude), 2 * sizeof(double));

    return data;
}

void GeolocationLatLon::to_stream(std::ostream& os) const
{
    Geolocation::to_stream(os);
    os.write(reinterpret_cast<const char*>(&latitude), 2 * sizeof(double));
}

// ----- printer -----
tools::classhelper::ObjectPrinter GeolocationLatLon::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("GeolocationLatLon (struct)", float_precision, superscript_exponents);

    printer.register_string(
        "latitude",
        navtools::latitude_to_string(latitude, navtools::t_latlon_format::seconds, 1),
        "ddd°mm',ss.s''N/S");
    printer.register_string(
        "longitude",
        navtools::longitude_to_string(longitude, navtools::t_latlon_format::seconds, 1),
        "ddd°mm',ss.s''E/W");

    printer.append(Geolocation::__printer__(float_precision, superscript_exponents));

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping