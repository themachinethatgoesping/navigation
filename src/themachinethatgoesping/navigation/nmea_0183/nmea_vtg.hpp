// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <string>
#include <charconv>

#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>

#include "nmeabase.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA VBW datagram contains the vessels course and speed over ground.
 * 
 */
class NMEA_VTG : public NMEABase
{

  public:
  /**
   * @brief Construct a new nmea vtg object from an existing NMEABase datagram
   * 
   * @param base Underlying NMEABase datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_VTG(NMEABase&& base, bool check = false)
    : NMEABase(std::move(base))
    {
        if (check) {
            if(get_type() != "VTG")
                throw std::runtime_error("NMEA_VTG: wrong sentence type");
        }
        parse_fields();
    }

    // ----- NMEA VTG attributes -----
    double course_over_ground_degrees_true() const
    {
        return get_field_as_double(0);
    }
    double course_over_ground_degrees_magnetic() const
    {
        return get_field_as_double(2);
    }
    double speed_over_ground_knots() const
    {
        return get_field_as_double(4);
    }
    double speed_over_ground_kmh() const
    {
        return get_field_as_double(6);
    }

    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA VTG Datagram", float_precision);

        printer.append(NMEABase::__printer__(float_precision));

        printer.register_section("VTG attributes");
        printer.register_value("course_over_ground_degrees_true", course_over_ground_degrees_true(),"° (true)");
        printer.register_value("course_over_ground_degrees_magnetic", course_over_ground_degrees_magnetic(),"° (magnetic)");
        printer.register_value("speed_over_ground_knots", speed_over_ground_knots(),"knots");
        printer.register_value("speed_over_ground_kmh", speed_over_ground_kmh(),"km/h");

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_VTG)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
