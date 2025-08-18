// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationlocal.doc.hpp"

#include <iostream>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "geolocation.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 * unlike the default Geolocation structure, this object stores local northing and easting
 * coordinates. These coordinates can be converted to UTM coordinates if the zone and hemisphere are
 * known.
 */
struct GeolocationLocal : public Geolocation
{
    double northing = 0.0; ///< in m, positive northwards
    double easting  = 0.0; ///< in m, positive eastwards

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    GeolocationLocal() = default;

    /**
     * @brief Construct a new GeolocationLocal object
     *
     * @param location
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     */
    GeolocationLocal(Geolocation location, double northing, double easting);

    /**
     * @brief Construct a new GeolocationLocal object
     *
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    GeolocationLocal(double northing,
                     double easting,
                     float z,
                     float yaw,
                     float pitch,
                     float roll);

    bool operator!=(const GeolocationLocal& rhs) const;
    bool operator==(const GeolocationLocal& rhs) const;

  public:
    // ----- file I/O -----
    static GeolocationLocal from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeolocationLocal)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping