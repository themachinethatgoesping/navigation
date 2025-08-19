// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_vtg.doc.hpp"

#include <string>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "nmea_base.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

/**
 * @brief The NMEA VBW datagram contains the vessels course and speed over ground.
 *
 */
class NMEA_VTG : public NMEA_Base
{

  public:
    /**
     * @brief Construct a new nmea vtg object from an existing NMEA_Base datagram
     *
     * @param base Underlying NMEA_Base datagram
     * @param check Check if the NMEA string is valid
     */
    NMEA_VTG(NMEA_Base base, bool check = false);

    // ----- NMEA VTG attributes -----
    double get_course_over_ground_degrees_true() const { return get_field_as_floattype<double>(0); }
    double get_course_over_ground_degrees_magnetic() const
    {
        return get_field_as_floattype<double>(2);
    }
    double get_speed_over_ground_knots() const { return get_field_as_floattype<double>(4); }
    double get_speed_over_ground_kmh() const { return get_field_as_floattype<double>(6); }

    char get_mode() const;
    std::string get_mode_explained() const;

    // ----- binary streaming -----
    // this has to be explicit, because otherwise the compiler will use the base class version
    static NMEA_VTG from_stream(std::istream& is);

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_VTG)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
