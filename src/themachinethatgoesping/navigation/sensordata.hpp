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
 * @brief A structure to store a georeferenced location and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 *
 */
struct SensorData
{
    double gps_latitude  = 0.0; ///< in °, positive northwards
    double gps_longitude = 0.0; ///< in °, positive eastwards
    double gps_z         = 0.0; ///< in m, positive downwards
    double heave_heave     = 0.0; ///< from heave sensor, will be added to gps_z in m, positive upwards
    double compass_heading = NAN; ///< from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is east
    double imu_yaw     = 0.0; ///< from motion sensor, in °, 0° is north, 90° is east
    double imu_pitch = 0.0;   ///< from motion sensor, in °, positive means bow up
    double imu_roll  = 0.0;   ///< from motion sensor, in °, positive means port up

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
     * @param gps_latitude in °, positive northwards
     * @param gps_longitude in °, positive eastwards
     * @param gps_z in m, positive downwards
     * @param heave_heave from heave sensor, will be added to gps_z in m, positive upwards
     * @param compass_heading from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is east
     * @param imu_yaw in °, 0° is north, 90° is east
     * @param imu_pitch in °, positive means bow up
     * @param imu_roll in °, positive means port up
     */
    SensorData(double gps_latitude,
               double gps_longitude,
               double gps_z,
               double heave_heave,
               double compass_heading,
               double imu_yaw,
               double imu_pitch,
               double imu_roll)
        : gps_latitude(gps_latitude)
        , gps_longitude(gps_longitude)
        , gps_z(gps_z)
        , heave_heave(heave_heave)
        , compass_heading(compass_heading)
        , imu_yaw(imu_yaw)
        , imu_pitch(imu_pitch)
        , imu_roll(imu_roll)
    {
    }

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
        if (tools::helpers::approx(gps_latitude, rhs.gps_latitude))
             if (tools::helpers::approx(gps_longitude, rhs.gps_longitude))
                 if (tools::helpers::approx(gps_z, rhs.gps_z))
                     if (tools::helpers::approx(heave_heave, rhs.heave_heave))
                         if (tools::helpers::approx(compass_heading, rhs.compass_heading))
                             if (tools::helpers::approx(imu_yaw, rhs.imu_yaw))
                                 if (tools::helpers::approx(imu_pitch, rhs.imu_pitch))
                                     if (tools::helpers::approx(imu_roll, rhs.imu_roll))
                                        return true;

        return false;
    }


  private:
    // serialigps_zation support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.value8b(gps_latitude);
        s.value8b(gps_longitude);
        s.value8b(gps_z);
        s.value8b(heave_heave);
        s.value8b(compass_heading);
        s.value8b(imu_yaw);
        s.value8b(imu_pitch);
        s.value8b(imu_roll);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("SensorData");

        printer.register_string(
            "gps_latitude",
            navtools::latitude_to_string(gps_latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''N/S");
        printer.register_string(
            "gps_longitude",
            navtools::longitude_to_string(gps_latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''E/W");
        printer.register_value("gps_z", gps_z, "positive downwards, m");
        printer.register_value("heave_heave", heave_heave, "positive upwards, m");

        if (std::isnan(compass_heading))
        {
            printer.register_value("compass_heading", compass_heading, "90 ° at east (invalid)");
            printer.register_value("imu_yaw", imu_yaw, "90 ° at east (used");
        }
        else
        {
            printer.register_value("compass_heading", compass_heading, "90 ° at east (valid)");
            printer.register_value("imu_yaw", imu_yaw, "90 ° at east (unused");
        }
        printer.register_value("imu_pitch", imu_pitch, "° positve bow up");
        printer.register_value("imu_roll", imu_roll, "° positive port up");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialigps_ze function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorData)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

} // namespace naviation
} // namespace themachinethatgoesping