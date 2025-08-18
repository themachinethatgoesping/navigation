// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatalatlon.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

#include "../navtools.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
SensordataLatLon::SensordataLatLon(Sensordata data, double latitude, double longitude)
    : Sensordata(std::move(data))
    , latitude(latitude)
    , longitude(longitude)
{
}

SensordataLatLon::SensordataLatLon(double latitude,
                                 double longitude,
                                 float depth,
                                 float heave,
                                 float heading,
                                 float pitch,
                                 float roll)
    : Sensordata(depth, heave, heading, pitch, roll)
    , latitude(latitude)
    , longitude(longitude)
{
}

// ----- operators -----
bool SensordataLatLon::operator!=(const SensordataLatLon& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool SensordataLatLon::operator==(const SensordataLatLon& rhs) const
{
    if (Sensordata::operator==(rhs))
        if (tools::helper::approx(latitude, rhs.latitude))
            if (tools::helper::approx(longitude, rhs.longitude))
                return true;

    return false;
}

// ----- file I/O -----
SensordataLatLon SensordataLatLon::from_stream(std::istream& is)
{
    SensordataLatLon data(Sensordata::from_stream(is), 0., 0.);

    is.read(reinterpret_cast<char*>(&data.latitude), 2 * sizeof(double));

    return data;
}

void SensordataLatLon::to_stream(std::ostream& os) const
{
    Sensordata::to_stream(os);
    os.write(reinterpret_cast<const char*>(&latitude), 2 * sizeof(double));
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensordataLatLon::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("SensordataLatLon (struct)", float_precision, superscript_exponents);

    printer.register_string(
        "latitude",
        navtools::latitude_to_string(latitude, navtools::t_latlon_format::seconds, 1),
        "ddd°mm',ss.s''N/S");
    printer.register_string(
        "longitude",
        navtools::longitude_to_string(longitude, navtools::t_latlon_format::seconds, 1),
        "ddd°mm',ss.s''E/W");

    printer.append(Sensordata::__printer__(float_precision, superscript_exponents));

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping