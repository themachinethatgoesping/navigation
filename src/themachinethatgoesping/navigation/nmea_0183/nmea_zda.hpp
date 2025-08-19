// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_zda.doc.hpp"

#include <string>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "nmea_base.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA ZDA datagram contains the universal time code (UTC), get_day, get_month, get_year
and local time zone offsets.
 *
 */
class NMEA_ZDA : public NMEA_Base
{

  public:
    /**
     * @brief Construct a new nmea zda object from an existing NMEA_Base datagram
     *
     * @param base Underlying NMEA_Base datagram
     * @param check Check if the NMEA string is valid
     */
    NMEA_ZDA(NMEA_Base base, bool check = false);

    std::string get_utc_time_string() const { return std::string(get_field(0)); }
    int         get_day() const { return get_field_as_int(1); }
    int         get_month() const { return get_field_as_int(2); }
    int         get_year() const { return get_field_as_int(3); }
    int         get_local_zone_hours() const { return get_field_as_int(4); }
    int         get_local_zone_minutes() const { return get_field_as_int(5); }

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
    std::string to_date_string(std::string format = std::string("%z__%d-%m-%Y__%H:%M:%S")) const;

    // ----- binary streaming -----
    // this has to be explicit, because otherwise the compiler will use the base class version
    static NMEA_ZDA from_stream(std::istream& is);

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_ZDA)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
