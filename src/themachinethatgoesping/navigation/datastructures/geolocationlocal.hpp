// Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationlocal.doc.hpp"

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>

#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools/helper/approx.hpp>

// #include "geolocationutm.hpp"

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
    GeolocationLocal(Geolocation location, double northing, double easting)
        : Geolocation(std::move(location))
        , northing(northing)
        , easting(easting)
    {
    }

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
                     float roll)
        : Geolocation(z, yaw, pitch, roll)
        , northing(northing)
        , easting(easting)
    {
    }

    bool operator!=(const GeolocationLocal& rhs) const { return !(operator==(rhs)); }
    bool operator==(const GeolocationLocal& rhs) const
    {
        if (Geolocation::operator==(rhs))
            if (tools::helper::approx(northing, rhs.northing))
                if (tools::helper::approx(easting, rhs.easting))
                    return true;

        return false;
    }

  public:
    // ----- file I/O -----
    static GeolocationLocal from_stream(std::istream& is)
    {
        GeolocationLocal data(Geolocation::from_stream(is), 0., 0.);

        is.read(reinterpret_cast<char*>(&data.northing), 2 * sizeof(double));

        return data;
    }

    void to_stream(std::ostream& os) const
    {
        Geolocation::to_stream(os);
        os.write(reinterpret_cast<const char*>(&northing), 2 * sizeof(double));
    }

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer("GeolocationLocal (struct)", float_precision, superscript_exponents);

        printer.register_value("northing", northing, "positive northwards, m");
        printer.register_value("easting", easting, "positive eastwards, m");

        printer.append(Geolocation::__printer__(float_precision, superscript_exponents));

        return printer;
    }

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