// Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationutm.doc.hpp"

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>
#include <themachinethatgoesping/tools/helper.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

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
                   bool                    northern_hemisphere)
        : GeolocationLocal(location_local)
        , utm_zone(utm_zone)
        , northern_hemisphere(northern_hemisphere)
    {
    }

    /**
     * @brief Construct an GeolocationUTM object from an existing GeolocationLatLon object (this
     * allows for explicit conversion from GeolocationLatLon class)
     *
     */
    explicit GeolocationUTM(const GeolocationLatLon& location, int setzone = -1)
        : GeolocationUTM(from_geolocation_latlon(location, setzone))
    {
    }

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
                   float roll)
        : GeolocationLocal(northing, easting, z, yaw, pitch, roll)
        , utm_zone(utm_zone)
        , northern_hemisphere(northern_hemisphere)
    {
    }

    bool operator!=(const GeolocationUTM& rhs) const { return !(operator==(rhs)); }
    bool operator==(const GeolocationUTM& rhs) const
    {
        if (GeolocationLocal::operator==(rhs))
            if (utm_zone == rhs.utm_zone)
                if (northern_hemisphere == rhs.northern_hemisphere)
                    return true;

        return false;
    }

    /**
     * @brief Convert a utm geolocationlatlon to an unprojected location
     *
     * @param location_utm
     * @return GeolocationLatLon
     */
    static GeolocationLatLon to_geolocation_latlon(const GeolocationUTM& location_utm)
    {
        GeolocationLatLon location(
            0, 0, location_utm.z, location_utm.yaw, location_utm.pitch, location_utm.roll);

        GeographicLib::UTMUPS::Reverse(location_utm.utm_zone,
                                       location_utm.northern_hemisphere,
                                       location_utm.easting,
                                       location_utm.northing,
                                       location.latitude,
                                       location.longitude);

        return location;
    }

    /**
     * @brief Construct convert a GeolocationLatLon Object to UTM
     *
     * @param location valid GeolocationLatLon object
     * @param setzone set a preferred UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return GeolocationUTM
     */
    static GeolocationUTM from_geolocation_latlon(const GeolocationLatLon& location,
                                                  int                      setzone = -1)
    {
        GeolocationUTM location_utm(
            0, 0, 0, 0, location.z, location.yaw, location.pitch, location.roll);

        GeographicLib::UTMUPS::Forward(location.latitude,
                                       location.longitude,
                                       location_utm.utm_zone,
                                       location_utm.northern_hemisphere,
                                       location_utm.easting,
                                       location_utm.northing,
                                       setzone);

        return location_utm;
    }

  public:
    // ----- file I/O -----
    static GeolocationUTM from_stream(std::istream& is)
    {
        GeolocationUTM data(GeolocationLocal::from_stream(is), 0, 0);

        is.read(reinterpret_cast<char*>(&data.utm_zone), sizeof(int));
        is.read(reinterpret_cast<char*>(&data.northern_hemisphere), sizeof(bool));

        return data;
    }

    void to_stream(std::ostream& os) const
    {
        GeolocationLocal::to_stream(os);

        os.write(reinterpret_cast<const char*>(&utm_zone), sizeof(int));
        os.write(reinterpret_cast<const char*>(&northern_hemisphere), sizeof(bool));
    }

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer("GeolocationUTM (struct)", float_precision, superscript_exponents);

        auto base_printer = GeolocationLocal::__printer__(float_precision, superscript_exponents);
        base_printer.remove_sections();
        printer.append(base_printer);
        printer.register_value("utm_zone", utm_zone, "", 2);
        printer.register_value("northern_hemisphere", northern_hemisphere, "", 3);

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeolocationUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

// IGNORE_DOC: __doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon
// backwards conversion
inline GeolocationLatLon::GeolocationLatLon(const GeolocationUTM& location_utm)
    : GeolocationLatLon(GeolocationUTM::to_geolocation_latlon(location_utm))
{
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping