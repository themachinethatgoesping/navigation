// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helpers.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "geolocationlatlon.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace navdata {

// foorwad declarations for location conversions
struct GeoLocationLocal; // defined in geolocationlocal.hpp

/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 * unlike the default GeoLocation structure, this object stores utm coordinates
 */
struct GeoLocationUTM
{
    double northing            = 0.0;  ///< in m, positive northwards
    double easting             = 0.0;  ///< in m, positive eastwards
    int    zone                = 0;    ///< UTM/UPS zone number
    bool   northern_hemisphere = true; ///< if true: northern hemisphere, else: southern hemisphere
    double z                   = 0;    ///< in m, positive downwards
    double yaw                 = 0.0;  ///< in °, 0° is north, 90° is east
    double pitch               = 0.0;  ///< in °, positive means bow up
    double roll                = 0.0;  ///< in °, positive means port up

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    GeoLocationUTM() = default;

    /**
     * @brief Construct an GeoLocationUTM object from an existing GeoLocationLatLon object (this allows
     * for implicit conversion from GeoLocationLatLon class)
     *
     */
    GeoLocationUTM(const GeoLocationLatLon& location, int setzone = -1)
        : GeoLocationUTM(from_geolocation_latlon(location, setzone))
    {
    }

    /**
     * @brief Construct an GeoLocationUTM object from an existing GeoLocationLocal object (using a
     * known zone and hemisphere)
     *
     * @param location_local
     * @param zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param offset_northing in m, is added to northing coordinate
     * @param offset_easting in m, is added to easting coordinate
     */
    GeoLocationUTM(const GeoLocationLocal& location_local,
                   int                     zone,
                   bool                    northern_hemisphere,
                   double                  offset_northing = 0.0,
                   double                  offset_easting = 0.0); // defined in geolocationlocal.hpp

    /**
     * @brief Construct a new GeoLocationUTM object
     *
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    GeoLocationUTM(double northing,
                   double easting,
                   int    zone,
                   bool   northern_hemisphere,
                   double z,
                   double yaw,
                   double pitch,
                   double roll)
        : northing(northing)
        , easting(easting)
        , zone(zone)
        , northern_hemisphere(northern_hemisphere)
        , z(z)
        , yaw(yaw)
        , pitch(pitch)
        , roll(roll)
    {
    }

    bool operator!=(const GeoLocationUTM& rhs) const { return !(operator==(rhs)); }
    bool operator==(const GeoLocationUTM& rhs) const
    {
        if (tools::helpers::approx(northing, rhs.northing))
            if (tools::helpers::approx(easting, rhs.easting))
                if (zone == rhs.zone)
                    if (northern_hemisphere == rhs.northern_hemisphere)
                        if (tools::helpers::approx(z, rhs.z))
                            if (tools::helpers::approx(yaw, rhs.yaw))
                                if (tools::helpers::approx(pitch, rhs.pitch))
                                    if (tools::helpers::approx(roll, rhs.roll))
                                        return true;

        return false;
    }

    /**
     * @brief Convert a utm geolocationlatlon to a unprojected location
     *
     * @param location_utm
     * @return GeoLocationLatLon
     */
    static GeoLocationLatLon to_geolocation_latlon(const GeoLocationUTM& location_utm)
    {
        GeoLocationLatLon location(
            0, 0, location_utm.z, location_utm.yaw, location_utm.pitch, location_utm.roll);

        GeographicLib::UTMUPS::Reverse(location_utm.zone,
                                       location_utm.northern_hemisphere,
                                       location_utm.easting,
                                       location_utm.northing,
                                       location.latitude,
                                       location.longitude);

        return location;
    }

    /**
     * @brief Construct convert a GeoLocationLatLon Object to UTM
     *
     * @param location valid GeoLocationLatLon object
     * @param setzone set a prefered UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return GeoLocationUTM
     */
    static GeoLocationUTM from_geolocation_latlon(const GeoLocationLatLon& location, int setzone = -1)
    {
        GeoLocationUTM location_utm(
            0, 0, 0, 0, location.z, location.yaw, location.pitch, location.roll);

        GeographicLib::UTMUPS::Forward(location.latitude,
                                       location.longitude,
                                       location_utm.zone,
                                       location_utm.northern_hemisphere,
                                       location_utm.easting,
                                       location_utm.northing,
                                       setzone);

        return location_utm;
    }

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.value8b(northing);
        s.value8b(easting);
        s.value4b(zone);
        s.value1b(northern_hemisphere);
        s.value8b(z);
        s.value8b(yaw);
        s.value8b(pitch);
        s.value8b(roll);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("GeoLocationUTM");

        printer.register_value("northing", northing, "positive northwards, m");
        printer.register_value("easting", easting, "positive eastwards, m");
        printer.register_value("zone", zone);
        printer.register_value("northern_hemisphere", northern_hemisphere);
        printer.register_value("z", z, "positive downwards, m");
        printer.register_value("yaw", yaw, "90 ° at east");
        printer.register_value("pitch", pitch, "° positve bow up");
        printer.register_value("roll", roll, "° positive port up");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeoLocationUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

// backwards conversion
inline GeoLocationLatLon::GeoLocationLatLon(const GeoLocationUTM& location_utm)
    : GeoLocationLatLon(GeoLocationUTM::to_geolocation_latlon(location_utm))
{
}

} // namespace navdata
} // namespace naviation
} // namespace themachinethatgoesping