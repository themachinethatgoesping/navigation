// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <string>
#include <charconv>

#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/timeconv.hpp>

#include "../navtools.hpp"
#include "nmeabase.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA RMC datagram contains time, date, position, course and speed data. Typically received from
a global navigation satellite system (GNSS device).
 * 
 */
class NMEA_RMC : public NMEABase
{

  public:
  /**
   * @brief Construct a new nmea rmc object from an existing NMEABase datagram
   * 
   * @param base Underlying NMEABase datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_RMC(NMEABase&& base, bool check = false)
    : NMEABase(std::move(base))
    {
        if (check) {
            if(get_type() != "RMC")
                throw std::runtime_error("NMEA_RMC: wrong sentence type");
        }
        parse_fields();
    }

    // ----- NMEA RMC attributes -----
    std::string coordinated_universal_time() const
    {
        return std::string(get_field(0));
    }
    bool status() const
    {
        return get_field(1) == "A";
    }
    double latitude() const
    {
        double degrees, minutes;
        std::from_chars(get_field(2).data(), get_field(2).data() + 2, degrees);
        std::from_chars(get_field(2).data()+2, get_field(2).data() + get_field(2).size(), minutes);

        if (get_field(3) == "N" )
            return (degrees + minutes / 60);
        else return -(degrees + minutes / 60);
    }
    double longitude() const
    {
        double degrees, minutes;
        std::from_chars(get_field(4).data(), get_field(4).data() + 3, degrees);
        std::from_chars(get_field(4).data()+3, get_field(4).data() + get_field(4).size(), minutes);
        
        if (get_field(5) == "E" )
            return (degrees + minutes / 60);
        else return -(degrees + minutes / 60);
    }
    double speed_over_ground_knots() const
    {
        return get_field_as_double(6);
    }
    double course_over_ground_degrees_true() const
    {
        return get_field_as_double(7);
    }
    std::string date() const
    {
        return std::string(get_field(8));
    }
    double magnetic_variation() const
    {
        return get_field_as_double(9);
    }
    char mode() const
    {
        return get_field(10)[0];
    }
    std::string mode_explained() const
    {
        char mode = this->mode();
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

    // ----- conversions -----
    /**
     * @brief Convert the datagram into a unixtime stamp
     * 
     * @return unixtime (seconds since 1970-01-01 00:00:00 UTC)
     */
    double to_timestamp () const
    {
        using themachinethatgoesping::tools::timeconv::datestring_to_unixtime;
        std::string datestring = coordinated_universal_time() + '-' + date();

        return datestring_to_unixtime( datestring, "%H%M%S-%d%m%y" );
    }

    /**
     * @brief Convert the datagram into a date time string
     *        Note: this function uses to_timestamp()
     * 
     * @param format Format string (see https://howardhinnant.github.io/date/date.html#to_stream_formatting)
     * @return date time string
     */
    std::string to_date_string(const std::string& format = "%z__%d-%m-%Y__%H:%M:%S") const
    {
        using themachinethatgoesping::tools::timeconv::unixtime_to_datestring;
        return unixtime_to_datestring(to_timestamp(),2,format);
    }
    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA RMC Datagram", float_precision);

        printer.append(NMEABase::__printer__(float_precision));

        printer.register_section("RMC attributes");
        printer.register_value("coordinated_universal_time", coordinated_universal_time(),"HHMMSS.SS");
        printer.register_value("status", status());

        printer.register_string(
            "latitude",
            navtools::latitude_to_string(latitude(), navtools::t_latlon_format::minutes, 2),
            "ddd°mm.mm'N/S");
        printer.register_string(
            "longitude",
            navtools::longitude_to_string(longitude(), navtools::t_latlon_format::minutes, 2),
            "ddd°mm.mm'E/W");

        printer.register_value("speed_over_ground_knots", speed_over_ground_knots());
        printer.register_value("course_over_ground_degrees_true", course_over_ground_degrees_true());
        printer.register_value("date", date());
        printer.register_value("magnetic_variation", magnetic_variation());
        printer.register_value("mode", this->mode(),mode_explained());

        printer.register_section("Converted attributes");
        printer.register_value("to_timestamp", std::to_string(to_timestamp()), "unixtime");
        printer.register_value("to_date_string", to_date_string());
        

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_RMC)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
