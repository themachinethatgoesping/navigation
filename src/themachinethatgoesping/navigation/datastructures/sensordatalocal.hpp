// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <bitsery/ext/inheritance.h>

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helper.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "../navtools.hpp"
#include "sensordata.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced data and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 * Unlike SensorDataUTM, this structure stores coordinates without zone and hemisphere information.
 *
 */
struct SensorDataLocal : public SensorData
{
    double gps_northing = 0.0; /// in m, positive northwards
    double gps_easting  = 0.0; /// in m, positive eastwards

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    SensorDataLocal() = default;

    /**
     * @brief Construct a new Sensor Data Local object using a base sensor data object
     *
     * @param data
     * @param gps_northing in m, positive northwards
     * @param gps_easting in m, positive eastwards
     */
    SensorDataLocal(const SensorData& data, double gps_northing, double gps_easting)
        : SensorData(data)
        , gps_northing(gps_northing)
        , gps_easting(gps_easting)
    {
    }

    /**
     * @brief Construct a new SensorDataLocal object
     *
     * @param gps_northing in m, positive northwards
     * @param gpd_easting in m, positive eastwards
     * @param gps_z in m, positive downwards
     * @param heave_heave from heave sensor, will be added to gps_z in m, positive upwards
     * @param compass_heading from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is
     * east
     * @param imu_yaw in °, 0° is north, 90° is east
     * @param imu_pitch in °, positive means bow up
     * @param imu_roll in °, positive means port up
     */
    SensorDataLocal(double gps_northing,
                    double gps_easting,
                    double gps_z,
                    double heave_heave,
                    double compass_heading,
                    double imu_yaw,
                    double imu_pitch,
                    double imu_roll)
        : SensorData(gps_z, heave_heave, compass_heading, imu_yaw, imu_pitch, imu_roll)
        , gps_northing(gps_northing)
        , gps_easting(gps_easting)
    {
    }

    bool operator!=(const SensorDataLocal& rhs) const { return !(operator==(rhs)); }
    /**
     * @brief Check if two SensorDataLocal objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensorDataLocal& rhs) const
    {
        if (SensorData::operator==(rhs))
            if (tools::helper::approx(gps_northing, rhs.gps_northing))
                if (tools::helper::approx(gps_easting, rhs.gps_easting))
                    return true;

        return false;
    }

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.ext(*this, bitsery::ext::BaseClass<SensorData>{});
        s.value8b(gps_northing);
        s.value8b(gps_easting);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("SensorDataLocal", float_precision);

        printer.register_value("gps_northing", gps_northing, "positive northwards, m");
        printer.register_value("gps_easting", gps_easting, "positive eastwards, m");

        printer.append(SensorData::__printer__(float_precision));

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialization function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorDataLocal)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping