// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_gll.doc.hpp"

#include <string>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

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
    NMEA_GLL(NMEA_Base base, bool check = false);

    // ----- NMEA GLL attributes -----
    double get_latitude() const;
    double get_longitude() const;

    std::string get_utc_time_string() const { return std::string(get_field(4)); }
    bool        get_status() const { return get_field(5) == "A"; }

    char get_mode() const;
    std::string get_mode_explained() const;

    // ----- binary streaming -----
    // this has to be explicit, because otherwise the compiler will use the base class version
    static NMEA_GLL from_stream(std::istream& is);

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_GLL)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
