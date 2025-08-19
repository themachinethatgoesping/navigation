// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_gst.doc.hpp"

#include <string>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "nmea_base.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA GST datagram contains Position error statistics. Typically received from
 * a global navigation satellite system (GNSS device).
 *
 */
class NMEA_GST : public NMEA_Base
{

  public:
    /**
     * @brief Construct a new nmea GST object from an existing NMEA_Base datagram
     *
     * @param base Underlying NMEA_Base datagram
     * @param check Check if the NMEA string is valid
     */
    NMEA_GST(NMEA_Base base, bool check = false);

    // ----- NMEA GST attributes -----
    std::string get_utc_time_string() const { return std::string(get_field(0)); }
    double      get_psuedorange_rms() const { return get_field_as_floattype<double>(1); }
    double      get_semimajor_error() const { return get_field_as_floattype<double>(2); }
    double      get_semiminor_error() const { return get_field_as_floattype<double>(3); }
    double get_semimajor_error_orientation() const { return get_field_as_floattype<double>(4); }
    double get_latitude_error_deviation() const { return get_field_as_floattype<double>(5); }
    double get_longitude_error_deviation() const { return get_field_as_floattype<double>(6); }
    double get_altitude_error_deviation() const { return get_field_as_floattype<double>(7); }

    // ----- binary streaming -----
    // this has to be explicit, because otherwise the compiler will use the base class version
    static NMEA_GST from_stream(std::istream& is);

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_GST)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
