// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helpers.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "geolocation.hpp"
#include "geolocationutm.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace navdata {


/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 * unlike the default GeoLocation structure, this object stores local northing and easting
 * coordinates. These coordintaes can be converted to UTM coordinates if the zone and hemisphere are
 * known.
 */
struct GeoLocationLocal
{
    double northing = 0.0; ///< in m, positive northwards
    double easting  = 0.0; ///< in m, positive eastwards
    double z        = 0;   ///< in m, positive downwards
    double yaw      = 0.0; ///< in °, 0° is north, 90° is east
    double pitch    = 0.0; ///< in °, positive means bow up
    double roll     = 0.0; ///< in °, positive means port up

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    GeoLocationLocal() = default;

    /**
     * @brief Construct an GeoLocationLocal object from an existing GeoLocation object (this allows
     * for implicit conversion from GeoLocation class)
     *
     */
    GeoLocationLocal(const GeoLocationUTM& location_utm,
                     double                offset_northing = 0,
                     double                offset_easting  = 0)
        : GeoLocationLocal(from_geolocationutm(location_utm,
                                               offset_northing,
                                               offset_easting))
    {
    }

    /**
     * @brief Construct a new GeoLocationLocal object
     *
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    GeoLocationLocal(double northing,
                     double easting,
                     double z,
                     double yaw,
                     double pitch,
                     double roll)
        : northing(northing)
        , easting(easting)
        , z(z)
        , yaw(yaw)
        , pitch(pitch)
        , roll(roll)
    {
    }

    bool operator!=(const GeoLocationLocal& rhs) const { return !(operator==(rhs)); }
    bool operator==(const GeoLocationLocal& rhs) const
    {
        if (tools::helpers::approx(northing, rhs.northing))
            if (tools::helpers::approx(easting, rhs.easting))
                if (tools::helpers::approx(z, rhs.z))
                    if (tools::helpers::approx(yaw, rhs.yaw))
                        if (tools::helpers::approx(pitch, rhs.pitch))
                            if (tools::helpers::approx(roll, rhs.roll))
                                return true;

        return false;
    }

    /**
     * @brief Convert a utm geolocation to a unprojected location
     *
     * @param location_local
     * @param zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param offset_northing in m, is added to northing coordinate
     * @param offset_easting in m, is added to easting coordinate
     * @return GeoLocationUTM
     */
    static GeoLocation to_geolocationutm(const GeoLocationLocal& location_local,
                                         int                     zone,
                                         bool                    northern_hemisphere,
                                         double                  offset_northing = 0,
                                         double                  offset_easting  = 0)
    {
        GeoLocationUTM location_utm(location_local.northing + offset_northing,
                                    location_local.easting + offset_easting,
                                    zone,
                                    northern_hemisphere,
                                    location_local.z,
                                    location_local.yaw,
                                    location_local.pitch,
                                    location_local.roll);

        return location_utm;
    }

    /**
     * @brief Construct convert a GeoLocationUTM Object to local (stripping zone and hemisphere)
     *
     * @param location_utm valid GeoLocation object
     * @param offset_northing in m, is substracted from northing coordinate
     * @param offset_easting in m, is substracted fromeasting coordinate
     * @return GeoLocationLocal
     */
    static GeoLocationLocal from_geolocationutm(const GeoLocationUTM& location_utm,
                                                double                offset_northing = 0,
                                                double                offset_easting  = 0)
    {
        GeoLocationLocal location_local(location_utm.northing - offset_northing,
                                      location_utm.easting - offset_easting,
                                      location_utm.z,
                                      location_utm.yaw,
                                      location_utm.pitch,
                                      location_utm.roll);

        return location_local;
    }

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.value8b(northing);
        s.value8b(easting);
        s.value8b(z);
        s.value8b(yaw);
        s.value8b(pitch);
        s.value8b(roll);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("GeoLocationLocal");

        printer.register_value("northing", northing, "positive northwards, m");
        printer.register_value("easting", easting, "positive eastwards, m");
        printer.register_value("z", z, "positive downwards, m");
        printer.register_value("yaw", yaw, "90 ° at east");
        printer.register_value("pitch", pitch, "° positve bow up");
        printer.register_value("roll", roll, "° positive port up");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeoLocationLocal)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

// backwards conversion
inline GeoLocationUTM::GeoLocationUTM(const GeoLocationLocal& location_local,
                                      int                     zone,
                                      bool                    northern_hemisphere,
                                      double                  offset_northing,
                                      double                  offset_easting)
    : GeoLocationUTM(GeoLocationLocal::to_geolocationutm(location_local,
                                                      zone,
                                                      northern_hemisphere,
                                                      offset_northing,
                                                      offset_easting))
{
}

} // namespace datastrcutures
} // namespace naviation
} // namespace themachinethatgoesping