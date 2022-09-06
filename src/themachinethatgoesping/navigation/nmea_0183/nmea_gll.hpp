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
#include "nmea_base.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA GLL datagram contains time, position, and status. Typically received from
a global navigation satellite system (GNSS device).
 * 
 */
class NMEA_GLL : public NMEA_Base
{

  public:
  /**
   * @brief Construct a new nmea gll object from an existing NMEA_Base datagram
   * 
   * @param base Underlying NMEA_Base datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_GLL(NMEA_Base&& base, bool check = false)
    : NMEA_Base(std::move(base))
    {
        if (check) {
            if(get_type() != "GLL")
                throw std::runtime_error("NMEA_GLL: wrong sentence type");
        }
        parse_fields();
    }

    // ----- NMEA GLL attributes -----
    double latitude() const
    {
        auto field = get_field(0);
        double degrees = std::stod(std::string(field.substr(0,2)));
        double minutes = std::stod(std::string(field.substr(2,field.size()-2)));

        if (get_field(1) == "N" )
            return (degrees + minutes / 60);
        else return -(degrees + minutes / 60);
    }
    double longitude() const
    {
        auto field = get_field(2);
        double degrees = std::stod(std::string(field.substr(0,2)));
        double minutes = std::stod(std::string(field.substr(2,field.size()-2)));
        
        if (get_field(3) == "E" )
            return (degrees + minutes / 60);
        else return -(degrees + minutes / 60);
    }

    std::string coordinated_universal_time() const
    {
        return std::string(get_field(4));
    }
    bool status() const
    {
        return get_field(5) == "A";
    }

    char mode() const
    {
        return get_field(6)[0];
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

    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA GLL Datagram", float_precision);

        printer.append(NMEA_Base::__printer__(float_precision));

        printer.register_section("GLL attributes");

        printer.register_string(
            "latitude",
            navtools::latitude_to_string(latitude(), navtools::t_latlon_format::minutes, 2),
            "ddd°mm.mm'N/S");
        printer.register_string(
            "longitude",
            navtools::longitude_to_string(longitude(), navtools::t_latlon_format::minutes, 2),
            "ddd°mm.mm'E/W");

        printer.register_value("coordinated_universal_time", coordinated_universal_time(),"HHMMSS.SS");
        printer.register_value("status", status());        
        printer.register_value("mode", this->mode(),mode_explained());

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_GLL)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
