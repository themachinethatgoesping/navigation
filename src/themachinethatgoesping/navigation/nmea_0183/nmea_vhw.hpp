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
 * @brief The NMEA VHW datagram contains the vessel's compass heading and the speed relative to the water.
 * 
 */
class NMEA_VHW : public NMEABase
{

  public:
  /**
   * @brief Construct a new nmea vhw object from an existing NMEABase datagram
   * 
   * @param base Underlying NMEABase datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_VHW(NMEABase&& base, bool check = false)
    : NMEABase(std::move(base))
    {
        if (check) {
            if(get_type() != "VHW")
                throw std::runtime_error("NMEA_VHW: wrong sentence type");
        }
        parse_fields();
    }

    // ----- NMEA VHW attributes -----
    double vessel_heading_true() const
    {
        return get_field_as_double(0);
    }
    double vessel_heading_magnetic() const
    {
        return get_field_as_double(2);
    }
    double speed_over_water_knots() const
    {
        return get_field_as_double(4);
    }
    double speed_over_water_kmh() const
    {
        return get_field_as_double(6);
    }

    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA VHW Datagram", float_precision);

        printer.append(NMEABase::__printer__(float_precision));

        printer.register_section("VHW attributes");
        printer.register_value("vessel_heading_true", vessel_heading_true(), "°, true");
        printer.register_value("vessel_heading_magnetic", vessel_heading_magnetic(), "°, magnetic");
        printer.register_value("speed_over_water_knots", speed_over_water_knots(), "knots");
        printer.register_value("speed_over_water_kmh", speed_over_water_kmh(), "km/h");

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_VHW)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
