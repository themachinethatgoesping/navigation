// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_rmc.doc.hpp"

#include <string>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "nmea_base.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA RMC datagram contains time, date, position, course and speed data. Typically
received from a global navigation satellite system (GNSS device).
 *
 */
class NMEA_RMC : public NMEA_Base
{

  public:
    /**
     * @brief Construct a new nmea rmc object from an existing NMEA_Base datagram
     *
     * @param base Underlying NMEA_Base datagram
     * @param check Check if the NMEA string is valid
     */
    NMEA_RMC(NMEA_Base base, bool check = false);

    // ----- NMEA RMC attributes -----
    std::string get_utc_time_string() const { return std::string(get_field(0)); }
    bool        get_status() const { return get_field(1) == "A"; }

    double get_latitude() const;
    double get_longitude() const;

    double get_speed_over_ground_knots() const { return get_field_as_floattype<double>(6); }
    double get_course_over_ground_degrees_true() const { return get_field_as_floattype<double>(7); }
    std::string get_utc_date_string() const { return std::string(get_field(8)); }
    double      get_magnetic_variation() const { return get_field_as_floattype<double>(9); }
    char        get_mode() const;
    std::string get_mode_explained() const;

    // ----- conversions -----
    /**
     * @brief Convert the datagram into a unixtime stamp
     *
     * @return unixtime (seconds since 1970-01-01 00:00:00 UTC)
     */
    double to_timestamp() const;

    /**
     * @brief Convert the datagram into a date time string
     *        Note: this function uses to_timestamp()
     *
     * @param format Format string (see
     * https://howardhinnant.github.io/date/date.html#to_stream_formatting)
     * @return date time string
     */
    std::string to_date_string(const std::string& format = "%z__%d-%m-%Y__%H:%M:%S") const;

    // ----- binary streaming -----
    // this has to be explicit, because otherwise the compiler will use the base class version
    static NMEA_RMC from_stream(std::istream& is);

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_RMC)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
