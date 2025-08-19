// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_rmc.hpp"

#include <themachinethatgoesping/tools/timeconv.hpp>

#include "../navtools.hpp"
#include "helper.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_RMC::NMEA_RMC(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "RMC")
            throw std::runtime_error(
                fmt::format("NMEA_RMC: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

double NMEA_RMC::get_latitude() const
{
    if (get_field(3) == "N")
        return nmea_latitude_field_to_double(get_field(2));
    else
        return -nmea_latitude_field_to_double(get_field(2));
}

double NMEA_RMC::get_longitude() const
{
    if (get_field(5) == "E")
        return nmea_longitude_field_to_double(get_field(4));
    else
        return -nmea_longitude_field_to_double(get_field(4));
}

char NMEA_RMC::get_mode() const
{
    try
    {
        return get_field(10).at(0);
    }
    catch ([[maybe_unused]] std::out_of_range& e)
    {
        return '\x00';
    }
}

std::string NMEA_RMC::get_mode_explained() const
{
    char mode = this->get_mode();
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

double NMEA_RMC::to_timestamp() const
{
    try
    {
        using themachinethatgoesping::tools::timeconv::datestring_to_unixtime;
        auto field_time = get_field(0);
        auto field_date = get_field(8);

        if (field_time.size() < 6 || field_date.size() < 6)
            return std::numeric_limits<double>::quiet_NaN();

        auto   date_time = get_utc_time_string() + "-" + get_utc_date_string() + '-' + "0000";
        double timestamp = datestring_to_unixtime(date_time, "%H%M%S-%d%m%y-%z");
        return timestamp;
    }
    catch (...)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
}

std::string NMEA_RMC::to_date_string(const std::string& format) const
{
    using themachinethatgoesping::tools::timeconv::unixtime_to_datestring;
    return unixtime_to_datestring(to_timestamp(), 2, format);
}

NMEA_RMC NMEA_RMC::from_stream(std::istream& is)
{
    return NMEA_RMC(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_RMC::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA RMC Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("RMC attributes");
    printer.register_value("utc_time_string", get_utc_time_string(), "HHMMSS.SS");
    printer.register_value("status", get_status());

    printer.register_string(
        "latitude",
        navtools::latitude_to_string(get_latitude(), navtools::t_latlon_format::minutes, 2),
        "ddd°mm.mm'N/S");
    printer.register_string(
        "longitude",
        navtools::longitude_to_string(get_longitude(), navtools::t_latlon_format::minutes, 2),
        "ddd°mm.mm'E/W");

    printer.register_value("speed_over_ground_knots", get_speed_over_ground_knots());
    printer.register_value("course_over_ground_degrees_true",
                           get_course_over_ground_degrees_true());
    printer.register_value("date", get_utc_date_string());
    printer.register_value("magnetic_variation", get_magnetic_variation());
    printer.register_value("mode", get_mode(), get_mode_explained());

    printer.register_section("Converted attributes");
    printer.register_value("to_timestamp", std::to_string(to_timestamp()), "unixtime");
    printer.register_value("to_date_string", to_date_string());

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping