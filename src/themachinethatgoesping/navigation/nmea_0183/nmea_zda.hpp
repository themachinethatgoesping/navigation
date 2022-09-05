// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <string>
#include <charconv>

#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/timeconv.hpp>

#include "nmeabase.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA ZDA datagram contains the universal time code (UTC), day, month, year
and local time zone offsets.
 * 
 */
class NMEA_ZDA : public NMEABase
{

  public:
  /**
   * @brief Construct a new nmea zda object from an existing NMEABase datagram
   * 
   * @param base Underlying NMEABase datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_ZDA(NMEABase&& base, bool check = false)
    : NMEABase(std::move(base))
    {
        if (check) {
            if(get_type() != "ZDA")
                throw std::runtime_error("NMEA_ZDA: wrong sentence type");
        }
        parse_fields();
    }

    std::string coordinated_universal_time() const
    {
        return std::string(get_field(0));
    }
    int day() const
    {
        return get_field_as_int(1);
    }
    int month() const
    {
        return get_field_as_int(2);
    }
    int year() const
    {
        return get_field_as_int(3);
    }   
    int local_zone_hours() const
    {
        return get_field_as_int(4);
    }
    int local_zone_minutes() const
    {
        return get_field_as_int(5);
    }

    /**
     * @brief Convert the datagram into a unixtime stamp
     * 
     * @return unixtime (seconds since 1970-01-01 00:00:00 UTC)
     */
    double to_timestamp() const
    {
        using themachinethatgoesping::tools::timeconv::datestring_to_unixtime;

        std::string time_string = _sentence.substr(7, 23) + _sentence.substr(31, 2);
        //112619.00,14,12,2017,00,00
        double timestamp = datestring_to_unixtime(time_string, "%H%M%S,%d,%m,%Y,%z");
        return timestamp;
    }

    /**
     * @brief Convert the datagram into a date time string
     *        Note: this function uses to_timestamp()
     * 
     * @param format Format string (see https://howardhinnant.github.io/date/date.html#to_stream_formatting)
     * @return date time string
     */
    std::string to_date_string(std::string format= std::string("%z__%d-%m-%Y__%H:%M:%S")) const
    {
        using themachinethatgoesping::tools::timeconv::unixtime_to_datestring;
        return unixtime_to_datestring(to_timestamp(),2,format);
    }
    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA ZDA Datagram", float_precision);

        printer.append(NMEABase::__printer__(float_precision));

        printer.register_section("ZDA attributes");
        printer.register_value("coordinated_universal_time", coordinated_universal_time(),"HHMMSS.SS");
        printer.register_value("day", day());
        printer.register_value("month", month());
        printer.register_value("year", year());
        printer.register_value("local_zone_hours", local_zone_hours());
        printer.register_value("local_zone_minutes", local_zone_minutes());

        printer.register_section("Converted attributes");
        printer.register_value("timestamp", std::to_string(to_timestamp()), "unixtime");
        printer.register_value("date_string", to_date_string());

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_ZDA)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
