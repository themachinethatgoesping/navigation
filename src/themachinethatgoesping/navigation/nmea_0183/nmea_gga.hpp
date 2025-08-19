// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_gga.doc.hpp"

#include <string>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "nmea_base.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA GGA datagram contains time, position, and fix. Typically received from
a global navigation satellite system (GNSS device).
 *
 */
class NMEA_GGA : public NMEA_Base
{

  public:
    /**
     * @brief Construct a new nmea gga object from an existing NMEA_Base datagram
     *
     * @param base Underlying NMEA_Base datagram
     * @param check Check if the NMEA string is valid
     */
    NMEA_GGA(NMEA_Base base, bool check = false);

    // ----- NMEA GGA attributes -----
    std::string get_utc_time_string() const { return std::string(get_field(0)); }

    double get_latitude() const;
    double get_longitude() const;

    int         get_quality() const { return get_field_as_int(5); }
    std::string get_quality_explained() const;
    int    get_number_of_satellites() const { return get_field_as_int(6); }
    double get_horizontal_dilution_of_precision() const
    {
        return get_field_as_floattype<double>(7);
    }
    double get_altitude() const { return get_field_as_floattype<double>(8); }
    double get_geoidal_separation() const { return get_field_as_floattype<double>(10); }
    double get_age_of_differential_gps_data() const { return get_field_as_floattype<double>(12); }
    int    get_differential_reference_station_id() const { return get_field_as_int(13); }

    // ----- binary streaming -----
    // this has to be explicit, because otherwise the compiler will use the base class version
    static NMEA_GGA from_stream(std::istream& is);

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_GGA)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
