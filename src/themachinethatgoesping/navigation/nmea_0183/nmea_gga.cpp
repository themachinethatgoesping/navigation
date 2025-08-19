// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_gga.hpp"

#include "../navtools.hpp"
#include "helper.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_GGA::NMEA_GGA(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "GGA")
            throw std::runtime_error(
                fmt::format("NMEA_GGA: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

double NMEA_GGA::get_latitude() const
{
    if (get_field(2) == "N")
        return nmea_latitude_field_to_double(get_field(1));
    else
        return -nmea_latitude_field_to_double(get_field(1));
}

double NMEA_GGA::get_longitude() const
{
    if (get_field(4) == "E")
        return nmea_longitude_field_to_double(get_field(3));
    else
        return -nmea_longitude_field_to_double(get_field(3));
}

std::string NMEA_GGA::get_quality_explained() const
{
    switch (get_quality())
    {
        case 0:
            return "invalid";
        case 1:
            return "GPS fix";
        case 2:
            return "DGPS fix";
        case 3:
            return "PPS fix";
        case 4:
            return "RTK fix";
        case 5:
            return "Float RTK";
        case 6:
            return "estimated (dead reckoning) fix";
        case 7:
            return "manual input mode";
        case 8:
            return "simulation mode";
        default:
            return "unknown";
    }
}

NMEA_GGA NMEA_GGA::from_stream(std::istream& is)
{
    return NMEA_GGA(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_GGA::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA GGA Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("GGA attributes");
    printer.register_value("utc_time_string", get_utc_time_string(), "HHMMSS.SS");

    printer.register_string(
        "latitude",
        navtools::latitude_to_string(get_latitude(), navtools::t_latlon_format::minutes, 2),
        "ddd°mm.mm'N/S");
    printer.register_string(
        "longitude",
        navtools::longitude_to_string(get_longitude(), navtools::t_latlon_format::minutes, 2),
        "ddd°mm.mm'E/W");

    printer.register_value("quality", get_quality(), get_quality_explained());
    printer.register_value("number_of_satellites", get_number_of_satellites());
    printer.register_value("horizontal_dilution_of_precision",
                           get_horizontal_dilution_of_precision());
    printer.register_value("altitude", get_altitude(), "m");
    printer.register_value("geoidal_separation", get_geoidal_separation(), "m");
    printer.register_value(
        "age_of_differential_gps_data", get_age_of_differential_gps_data(), "s");
    printer.register_value("differential_reference_station_id",
                           get_differential_reference_station_id());

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping