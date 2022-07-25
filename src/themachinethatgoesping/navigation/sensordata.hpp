// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helpers.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "navtools.hpp"

namespace themachinethatgoesping {
namespace navigation {

// foorwad declarations for location conversions
struct SensorDataUTM; // defined in sensordatautm.hpp

/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 *
 */
struct SensorData
{
    double latitude  = 0.0; ///< in °, positive northwards
    double longitude = 0.0; ///< in °, positive eastwards
    double z         = 0.0; ///< in m, positive downwards
    double heave     = 0.0; ///< from heave sensor, will be added to z in m, positive upwards
    double heading = NAN; ///< from compass, replaces yaw if not NAN, in °, 0° is north, 90° is east
    double yaw     = 0.0; ///< from motion sensor, in °, 0° is north, 90° is east
    double pitch = 0.0;   ///< from motion sensor, in °, positive means bow up
    double roll  = 0.0;   ///< from motion sensor, in °, positive means port up

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    SensorData() = default;

    /**
     * @brief Construct an SensorData object from an existing SensorDataUTM object (this allows
     * for implicit conversion from SensorDataUTM class)
     *
     */
    // SensorData(const SensorDataUTM& location_utm); // defined in sensordatautm.hpp

    /**
     * @brief Construct a new SensorData object
     *
     * @param latitude in °, positive northwards
     * @param longitude in °, positive eastwards
     * @param z in m, positive downwards
     * @param heave from heave sensor, will be added to z in m, positive upwards
     * @param heading from compass, replaces yaw if not NAN, in °, 0° is north, 90° is east
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    SensorData(double latitude,
               double longitude,
               double z,
               double heave,
               double heading,
               double yaw,
               double pitch,
               double roll)
        : latitude(latitude)
        , longitude(longitude)
        , z(z)
        , heave(heave)
        , heading(heading)
        , yaw(yaw)
        , pitch(pitch)
        , roll(roll)
    {
    }

    /**
     * @brief Construct a new SensorData object from a string
     *
     * @param str string containing the location in the format "latitude,longitude,z,yaw,pitch,roll"
     */
    bool operator!=(const SensorData& rhs) const { return !(operator==(rhs)); }

    /**
     * @brief Check if two SensorData objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensorData& rhs) const
    {
        if (tools::helpers::approx(latitude, rhs.latitude))
             if (tools::helpers::approx(longitude, rhs.longitude))
                 if (tools::helpers::approx(z, rhs.z))
                     if (tools::helpers::approx(heave, rhs.heave))
                         if (tools::helpers::approx(heading, rhs.heading))
                             if (tools::helpers::approx(yaw, rhs.yaw))
                                 if (tools::helpers::approx(pitch, rhs.pitch))
                                     if (tools::helpers::approx(roll, rhs.roll))
                                        return true;

        return false;
    }

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.value8b(latitude);
        s.value8b(longitude);
        s.value8b(z);
        s.value8b(heave);
        s.value8b(heading);
        s.value8b(yaw);
        s.value8b(pitch);
        s.value8b(roll);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("SensorData");

        printer.register_string(
            "latitude",
            navtools::latitude_to_string(latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''N/S");
        printer.register_string(
            "longitude",
            navtools::longitude_to_string(latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''E/W");
        printer.register_value("z", z, "positive downwards, m");
        printer.register_value("heave", heave, "positive upwards, m");

        if (std::isnan(heading))
        {
            printer.register_value("heading", heading, "90 ° at east (invalid)");
            printer.register_value("yaw", yaw, "90 ° at east (used");
        }
        else
        {
            printer.register_value("heading", heading, "90 ° at east (valid)");
            printer.register_value("yaw", yaw, "90 ° at east (unused");
        }
        printer.register_value("pitch", pitch, "° positve bow up");
        printer.register_value("roll", roll, "° positive port up");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorData)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

} // namespace naviation
} // namespace themachinethatgoesping