// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_zda.hpp"

#include <themachinethatgoesping/tools/timeconv.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_ZDA::NMEA_ZDA(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "ZDA")
            throw std::runtime_error(
                fmt::format("NMEA_ZDA: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

double NMEA_ZDA::to_timestamp() const
{
    try
    {
        using themachinethatgoesping::tools::timeconv::datestring_to_unixtime;

        std::string time_string   = _sentence.substr(7, _sentence.size() - 8);
        double      unixtime      = datestring_to_unixtime(time_string, "%H%M%S,%d,%m,%Y");
        auto        field_hours   = get_field(4);
        auto        field_minutes = get_field(4);
        if (!field_hours.empty() && field_hours != "00")
        {
            // int hours;
            // std::from_chars(field_hours.data(), field_hours.data() + field_hours.size(),
            // hours); unixtime += 3600 * hours;
            unixtime += 3600 * std::stoi(std::string(field_hours));
        }
        if (!field_minutes.empty() && field_minutes != "00")
        {
            // int minutes;
            // std::from_chars(field_minutes.data(), field_minutes.data() +
            // field_minutes.size(),
            //                 minutes);
            // unixtime += 60 * minutes;
            unixtime += 60 * std::stoi(std::string(field_minutes));
        }

        return unixtime;
    }
    catch (...)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
}

std::string NMEA_ZDA::to_date_string(std::string format) const
{
    using themachinethatgoesping::tools::timeconv::unixtime_to_datestring;
    return unixtime_to_datestring(to_timestamp(), 2, format);
}

NMEA_ZDA NMEA_ZDA::from_stream(std::istream& is)
{
    return NMEA_ZDA(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_ZDA::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA ZDA Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("ZDA attributes");
    printer.register_value("utc_time_string", get_utc_time_string(), "HHMMSS.SS");
    printer.register_value("day", get_day());
    printer.register_value("month", get_month());
    printer.register_value("year", get_year());
    printer.register_value("local_zone_hours", get_local_zone_hours());
    printer.register_value("local_zone_minutes", get_local_zone_minutes());

    printer.register_section("Converted attributes");
    printer.register_value("timestamp", std::to_string(to_timestamp()), "unixtime");
    printer.register_value("date_string", to_date_string());

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping