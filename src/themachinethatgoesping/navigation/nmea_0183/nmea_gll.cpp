// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_gll.hpp"

#include "../navtools.hpp"
#include "helper.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_GLL::NMEA_GLL(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "GLL")
            throw std::runtime_error(
                fmt::format("NMEA_GLL: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

double NMEA_GLL::get_latitude() const
{
    if (get_field(1) == "N")
        return nmea_latitude_field_to_double(get_field(0));
    else
        return -nmea_latitude_field_to_double(get_field(0));
}

double NMEA_GLL::get_longitude() const
{
    if (get_field(3) == "E")
        return nmea_longitude_field_to_double(get_field(2));
    else
        return -nmea_longitude_field_to_double(get_field(2));
}

char NMEA_GLL::get_mode() const
{
    try
    {
        return get_field(6).at(0);
    }
    catch ([[maybe_unused]] std::out_of_range& e)
    {
        return '\x00';
    }
}

std::string NMEA_GLL::get_mode_explained() const
{
    char mode = get_mode();
    if (mode == 'A')
        return "Autonomous";
    if (mode == 'D')
        return "Differential";
    if (mode == 'E')
        return "Estimated";
    if (mode == 'M')
        return "Manual";
    if (mode == 'S')
        return "Simulated";
    if (mode == 'N')
        return "Data not valid";
    return "Unknown";
}

NMEA_GLL NMEA_GLL::from_stream(std::istream& is)
{
    return NMEA_GLL(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_GLL::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA GLL Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("GLL attributes");

    printer.register_string(
        "latitude",
        navtools::latitude_to_string(get_latitude(), navtools::t_latlon_format::minutes, 2),
        "ddd°mm.mm'N/S");
    printer.register_string(
        "longitude",
        navtools::longitude_to_string(get_longitude(), navtools::t_latlon_format::minutes, 2),
        "ddd°mm.mm'E/W");

    printer.register_value("utc_time_string", get_utc_time_string(), "HHMMSS.SS");
    printer.register_value("status", this->get_status());
    printer.register_value("mode", get_mode(), get_mode_explained());

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping