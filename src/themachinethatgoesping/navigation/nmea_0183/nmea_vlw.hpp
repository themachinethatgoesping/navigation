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
 * @brief The NMEA VLW datagram contains the distance of the vessel traveled by the vessel.
 * 
 */
class NMEA_VLW : public NMEABase
{

  public:
  /**
   * @brief Construct a new nmea vlw object from an existing NMEABase datagram
   * 
   * @param base Underlying NMEABase datagram
   * @param check Check if the NMEA string is valid
   */
    NMEA_VLW(NMEABase&& base, bool check = false)
    : NMEABase(std::move(base))
    {
        if (check) {
            if(get_type() != "VLW")
                throw std::runtime_error("NMEA_VLW: wrong sentence type");
        }
        parse_fields();
    }

    // ----- NMEA VLW attributes -----
    double total_water_distance_nautical_miles() const
    {
        return get_field_as_double(0);
    }
    double trip_water_distance_nautical_miles() const
    {
        return get_field_as_double(2);
    }
    double total_ground_distance_nautical_miles() const
    {
        if (_fields.size() < 5)
            return 0.0;
        return get_field_as_double(4);
    }
    double trip_ground_distance_nautical_miles() const
    {
        if (_fields.size() < 7)
            return 0.0;
        return get_field_as_double(6);
    }

    

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA VLW Datagram", float_precision);

        printer.append(NMEABase::__printer__(float_precision));

        printer.register_section("VLW attributes");
        printer.register_value("total_water_distance_nautical_miles", total_water_distance_nautical_miles(),"nm");
        printer.register_value("trip_water_distance_nautical_miles", trip_water_distance_nautical_miles(),"nm");
        printer.register_value("total_ground_distance_nautical_miles", total_ground_distance_nautical_miles(),"nm");
        printer.register_value("trip_ground_distance_nautical_miles", trip_ground_distance_nautical_miles(),"nm");

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_VLW)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
