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
 * @brief The NMEA GGA datagram contains time, position, and fix. Typically received from
a global navigation satellite system (GNSS device).
 * 
 */
class NMEA_GGA : public NMEABase
{

  public:
  /**
   * @brief Construct a new nmea gga object from an existing NMEABase datagram
   * 
   * @param base Underlying NMEABase datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_GGA(NMEABase&& base, bool check = false)
    : NMEABase(std::move(base))
    {
        if (check) {
            if(get_type() != "GGA")
                throw std::runtime_error("NMEA_GGA: wrong sentence type");
        }
        parse_fields();
    }

    // ----- NMEA GGA attributes -----
    std::string coordinated_universal_time() const
    {
        return std::string(get_field(0));
    }
    double latitude() const
    {
        double degrees, minutes;
        std::from_chars(get_field(1).data(), get_field(1).data() + 2, degrees);
        std::from_chars(get_field(1).data()+2, get_field(1).data() + get_field(1).size(), minutes);

        if (get_field(2) == "N" )
            return (degrees + minutes / 60);
        else return -(degrees + minutes / 60);
    }
    double longitude() const
    {
        double degrees, minutes;
        std::from_chars(get_field(3).data(), get_field(3).data() + 3, degrees);
        std::from_chars(get_field(3).data()+3, get_field(3).data() + get_field(3).size(), minutes);
        
        if (get_field(4) == "E" )
            return (degrees + minutes / 60);
        else return -(degrees + minutes / 60);
    }
    int quality() const
    {
        return get_field_as_int(5);
    }
    std::string quality_explained() const
    {
        switch (quality()) {
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
    int number_of_satellites() const
    {
        return get_field_as_int(6);
    }
    double horizontal_dilution_of_precision() const
    {
        return get_field_as_double(7);
    }
    double altitude() const
    {
        return get_field_as_double(8);
    }
    double geoidal_separation() const
    {
        return get_field_as_double(10);
    }
    double age_of_differential_gps_data() const
    {
        return get_field_as_double(12);
    }
    int differential_reference_station_id() const
    {
        return get_field_as_int(13);
    }

    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA GGA Datagram", float_precision);

        printer.append(NMEABase::__printer__(float_precision));

        printer.register_section("GGA attributes");
        printer.register_value("coordinated_universal_time", coordinated_universal_time(),"HHMMSS.SS");

        printer.register_string(
            "latitude",
            navtools::latitude_to_string(latitude(), navtools::t_latlon_format::minutes, 2),
            "ddd°mm.mm'N/S");
        printer.register_string(
            "longitude",
            navtools::longitude_to_string(longitude(), navtools::t_latlon_format::minutes, 2),
            "ddd°mm.mm'E/W");

        printer.register_value("quality", quality(),quality_explained());
        printer.register_value("number_of_satellites", number_of_satellites());
        printer.register_value("horizontal_dilution_of_precision", horizontal_dilution_of_precision());
        printer.register_value("altitude", altitude(),"m");
        printer.register_value("geoidal_separation", geoidal_separation(),"m");
        printer.register_value("age_of_differential_gps_data", age_of_differential_gps_data(),"s");
        printer.register_value("differential_reference_station_id", differential_reference_station_id());

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_GGA)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
