// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationutm.doc.hpp"

#include <iostream>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "geolocationlatlon.hpp"
#include "geolocationlocal.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 * unlike the default Geolocation structure, this object stores utm coordinates
 */
struct GeolocationUTM : public GeolocationLocal
{
    int  utm_zone = 0; ///< UTM/UPS zone number
    bool northern_hemisphere =
        true; ///< if true: northern hemisphere, else: southern hemisphere

    /**
     * @brief Construct a new Sensor Position object
     *
     */
    GeolocationUTM() = default;

    /**
     * @brief Construct an GeolocationUTM object from an existing GeolocationLocal object (using a
     * known zone and hemisphere)
     *
     * @param location_local
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    GeolocationUTM(const GeolocationLocal& location_local,
                   int                     utm_zone,
                   bool                    northern_hemisphere);

    /**
     * @brief Construct an GeolocationUTM object from an existing GeolocationLatLon object (this
     * allows for explicit conversion from GeolocationLatLon class)
     *
     */
    explicit GeolocationUTM(const GeolocationLatLon& location, int setzone = -1);

    /**
     * @brief Construct a new GeolocationUTM object
     *
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    GeolocationUTM(double northing,
                   double easting,
                   int    utm_zone,
                   bool   northern_hemisphere,
                   float z,
                   float yaw,
                   float pitch,
                   float roll);

    bool operator!=(const GeolocationUTM& rhs) const;
    bool operator==(const GeolocationUTM& rhs) const;

    /**
     * @brief Convert a utm geolocationlatlon to an unprojected location
     *
     * @param location_utm
     * @return GeolocationLatLon
     */
    static GeolocationLatLon to_geolocation_latlon(const GeolocationUTM& location_utm);

    /**
     * @brief Construct convert a GeolocationLatLon Object to UTM
     *
     * @param location valid GeolocationLatLon object
     * @param setzone set a preferred UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return GeolocationUTM
     */
    static GeolocationUTM from_geolocation_latlon(const GeolocationLatLon& location,
                                                  int                      setzone = -1);

  public:
    // ----- file I/O -----
    static GeolocationUTM from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeolocationUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

// IGNORE_DOC:__doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon
// backwards conversion - this is implemented in geolocationutm.cpp
GeolocationLatLon::GeolocationLatLon(const GeolocationUTM& location_utm);

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping