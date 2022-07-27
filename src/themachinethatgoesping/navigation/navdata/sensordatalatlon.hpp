// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <bitsery/ext/inheritance.h>

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helper.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>


#include "../navtools.hpp"
#include "sensordata.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace navdata {

// foorwad declarations for location conversions
struct SensorDataUTM; // defined in sensordatautm.hpp

/**
 * @brief A structure to store a georeferenced location and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 *
 */
struct SensorDataLatLon : public SensorData
{
    double gps_latitude  = 0.0; ///< in °, positive northwards
    double gps_longitude = 0.0; ///< in °, positive eastwards
    // double gps_z         = 0.0; ///< in m, positive downwards
    // double heave_heave     = 0.0; ///< from heave sensor, will be added to gps_z in m, positive upwards
    // double compass_heading = NAN; ///< from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is east
    // double imu_yaw     = 0.0; ///< from motion sensor, in °, 0° is north, 90° is east
    // double imu_pitch = 0.0;   ///< from motion sensor, in °, positive means bow up
    // double imu_roll  = 0.0;   ///< from motion sensor, in °, positive means port up

    /**
     * @brief Construct a new SensorDataLatLon object (all offsets set to 0)
     *
     */
    SensorDataLatLon() = default;

    /**
     * @brief Construct a new Sensor Data Lat Lon object using a base sensor data object
     * 
     * @param data 
     * @param gps_latitude in °, positive northwards
     * @param gps_longitude in °, positive eastwards
     */
    SensorDataLatLon(const SensorData& data, double gps_latitude, double gps_longitude)
        : SensorData(data),
            gps_latitude(gps_latitude),
            gps_longitude(gps_longitude)
    {}

    /**
     * @brief Construct an SensorDataLatLon object from an existing SensorDataUTM object (this allows
     * for implicit conversion from SensorDataUTM class)
     *
     */
    SensorDataLatLon(const SensorDataUTM& data_utm); // defined in sensordatautm.hpp

    /**
     * @brief Construct a new SensorDataLatLon object
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
    SensorDataLatLon(double gps_latitude,
               double gps_longitude,
               double gps_z,
               double heave_heave,
               double compass_heading,
               double imu_yaw,
               double imu_pitch,
               double imu_roll)
        : SensorData(gps_z, heave_heave, compass_heading, imu_yaw, imu_pitch, imu_roll)
        , gps_latitude(gps_latitude)
        , gps_longitude(gps_longitude)
    {
    }

    bool operator!=(const SensorDataLatLon& rhs) const { return !(operator==(rhs)); }
    /**
     * @brief Check if two SensorDataLatLon objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensorDataLatLon& rhs) const
    {
        if (SensorData::operator==(rhs))
            if (tools::helper::approx(gps_latitude, rhs.gps_latitude))
                if (tools::helper::approx(gps_longitude, rhs.gps_longitude))
                                            return true;

        return false;
    }


  private:
    // serialigps_zation support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.ext(*this, bitsery::ext::BaseClass<SensorData>{});
        s.value8b(gps_latitude);
        s.value8b(gps_longitude);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("SensorDataLatLon");

        printer.register_section("coordinates");
        printer.register_string(
            "gps_latitude",
            navtools::latitude_to_string(gps_latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''N/S");
        printer.register_string(
            "gps_longitude",
            navtools::longitude_to_string(gps_latitude, navtools::t_latlon_format::seconds, 1),
            "ddd°mm',ss.s''E/W");

        printer.register_section("attitude");
        printer.append(SensorData::__printer__());

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialigps_ze function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorDataLatLon)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

} // nameespace datastrcutures
} // namespace naviation
} // namespace themachinethatgoesping