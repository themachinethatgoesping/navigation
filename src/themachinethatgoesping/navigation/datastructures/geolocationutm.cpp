// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationutm.hpp"

#include <GeographicLib/UTMUPS.hpp>

#include "geolocationlatlon.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
GeolocationUTM::GeolocationUTM(const GeolocationLocal& location_local,
                              int                     utm_zone,
                              bool                    northern_hemisphere)
    : GeolocationLocal(location_local)
    , utm_zone(utm_zone)
    , northern_hemisphere(northern_hemisphere)
{
}

GeolocationUTM::GeolocationUTM(const GeolocationLatLon& location, int setzone)
    : GeolocationUTM(from_geolocation_latlon(location, setzone))
{
}

GeolocationUTM::GeolocationUTM(double northing,
                              double easting,
                              int    utm_zone,
                              bool   northern_hemisphere,
                              float z,
                              float yaw,
                              float pitch,
                              float roll)
    : GeolocationLocal(northing, easting, z, yaw, pitch, roll)
    , utm_zone(utm_zone)
    , northern_hemisphere(northern_hemisphere)
{
}

// ----- operators -----
bool GeolocationUTM::operator!=(const GeolocationUTM& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool GeolocationUTM::operator==(const GeolocationUTM& rhs) const
{
    if (GeolocationLocal::operator==(rhs))
        if (utm_zone == rhs.utm_zone)
            if (northern_hemisphere == rhs.northern_hemisphere)
                return true;

    return false;
}

// ----- static conversion functions -----
GeolocationLatLon GeolocationUTM::to_geolocation_latlon(const GeolocationUTM& location_utm)
{
    GeolocationLatLon location(
        0, 0, location_utm.z, location_utm.yaw, location_utm.pitch, location_utm.roll);

    GeographicLib::UTMUPS::Reverse(location_utm.utm_zone,
                                   location_utm.northern_hemisphere,
                                   location_utm.easting,
                                   location_utm.northing,
                                   location.latitude,
                                   location.longitude);

    return location;
}

GeolocationUTM GeolocationUTM::from_geolocation_latlon(const GeolocationLatLon& location,
                                                      int                      setzone)
{
    GeolocationUTM location_utm(
        0, 0, 0, 0, location.z, location.yaw, location.pitch, location.roll);

    GeographicLib::UTMUPS::Forward(location.latitude,
                                   location.longitude,
                                   location_utm.utm_zone,
                                   location_utm.northern_hemisphere,
                                   location_utm.easting,
                                   location_utm.northing,
                                   setzone);

    return location_utm;
}

// ----- file I/O -----
GeolocationUTM GeolocationUTM::from_stream(std::istream& is)
{
    GeolocationUTM data(GeolocationLocal::from_stream(is), 0, 0);

    is.read(reinterpret_cast<char*>(&data.utm_zone), sizeof(int));
    is.read(reinterpret_cast<char*>(&data.northern_hemisphere), sizeof(bool));

    return data;
}

void GeolocationUTM::to_stream(std::ostream& os) const
{
    GeolocationLocal::to_stream(os);

    os.write(reinterpret_cast<const char*>(&utm_zone), sizeof(int));
    os.write(reinterpret_cast<const char*>(&northern_hemisphere), sizeof(bool));
}

// ----- printer -----
tools::classhelper::ObjectPrinter GeolocationUTM::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("GeolocationUTM (struct)", float_precision, superscript_exponents);

    auto base_printer = GeolocationLocal::__printer__(float_precision, superscript_exponents);
    base_printer.remove_sections();
    printer.append(base_printer);
    printer.register_value("utm_zone", utm_zone, "", 2);
    printer.register_value("northern_hemisphere", northern_hemisphere, "", 3);

    return printer;
}

// ----- backwards conversion implementation -----
GeolocationLatLon::GeolocationLatLon(const GeolocationUTM& location_utm)
    : GeolocationLatLon(GeolocationUTM::to_geolocation_latlon(location_utm))
{
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping