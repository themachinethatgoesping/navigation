// Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationlatlon.doc.hpp"

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>

#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools/helper/approx.hpp>

#include "../navtools.hpp"
#include "geolocation.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// forward declarations for location conversions
// IGNORE_DOC:__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM
struct GeolocationUTM; // defined in geolocationutm.hpp

/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 * Unlike the base Geolocation object, this also stores latitude and longitude coordinates
 *
 */
struct GeolocationLatLon : public Geolocation
{
    double latitude  = 0.0; ///< in °, positive northwards
    double longitude = 0.0; ///< in °, positive eastwards
    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    GeolocationLatLon() = default;

    /**
     * @brief Construct a new Sensor Data Lat Lon object using a base sensor data object
     *
     * @param location
     * @param latitude in °, positive northwards
     * @param longitude in °, positive eastwards
     */
    GeolocationLatLon(Geolocation location, double latitude, double longitude)
        : Geolocation(std::move(location))
        , latitude(latitude)
        , longitude(longitude)
    {
    }

    /**
     * @brief Construct an GeolocationLatLon object from an existing GeolocationUTM object (this
     * allows for explicit conversion from GeolocationUTM class)
     *
     */
    explicit GeolocationLatLon(const GeolocationUTM& location_utm); // defined in geolocationutm.hpp

    /**
     * @brief Construct a new GeolocationLatLon object
     *
     * @param latitude in °, positive northwards
     * @param longitude in °, positive eastwards
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    GeolocationLatLon(double latitude,
                      double longitude,
                      float  z,
                      float  yaw,
                      float  pitch,
                      float  roll)
        : Geolocation(z, yaw, pitch, roll)
        , latitude(latitude)
        , longitude(longitude)
    {
    }

    /**
     * @brief Construct a new GeolocationLatLon object from a string
     *
     * @param str string containing the location in the format "latitude,longitude,z,yaw,pitch,roll"
     */
    bool operator!=(const GeolocationLatLon& rhs) const { return !(operator==(rhs)); }

    /**
     * @brief Check if two GeolocationLatLon objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const GeolocationLatLon& other) const
    {
        if (Geolocation::operator==(other))
            if (tools::helper::approx(latitude, other.latitude))
                if (tools::helper::approx(longitude, other.longitude))
                    return true;

        return false;
    }

  public:
    // ----- file I/O -----
    static GeolocationLatLon from_stream(std::istream& is)
    {
        GeolocationLatLon data(Geolocation::from_stream(is), 0., 0.);

        is.read(reinterpret_cast<char*>(&data.latitude), 2 * sizeof(double));

        return data;
    }

    void to_stream(std::ostream& os) const
    {
        Geolocation::to_stream(os);
        os.write(reinterpret_cast<const char*>(&latitude), 2 * sizeof(double));
    }

  public:
    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer("GeolocationLatLon (struct)", float_precision, superscript_exponents);

        printer.register_string(
            "latitude",
            navtools::latitude_to_string(latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''N/S");
        printer.register_string(
            "longitude",
            navtools::longitude_to_string(longitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''E/W");

        printer.append(Geolocation::__printer__(float_precision, superscript_exponents));

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeolocationLatLon)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping