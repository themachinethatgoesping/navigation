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
#include "sensordatalatlon.hpp"
#include "sensordatalocal.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace navdata {

/**
 * @brief A structure to store a georeferenced data and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 * Unlike SensorDataLatLon, this structure stores UTM coordinates.
 *
 */
struct SensorDataUTM : public SensorDataLocal
{
    int  gps_zone = 0; ///< UTM/UPS zone number
    bool gps_northern_hemisphere =
        true; ///< if true: northern hemisphere, else: southern hemisphere

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    SensorDataUTM() = default;

    /**
     * @brief Construct a new Sensor Data Local object using a base sensor data object
     *
     * @param data
     * @param gps_northing in m, positive northwards
     * @param gps_easting in m, positive eastwards
     * @param gps_zone UTM/UPS zone number
     * @param gps_northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    SensorDataUTM(const SensorData& data,
                  double            gps_northing,
                  double            gps_easting,
                  int               gps_zone,
                  bool              gps_northern_hemisphere)
        : SensorDataLocal(data, gps_northing, gps_easting)
        , gps_zone(gps_zone)
        , gps_northern_hemisphere(gps_northern_hemisphere)
    {
    }

    /**
     * @brief Construct an SensorDataUTM object from an existing SensorDataLocal object (using a
     * known zone and hemisphere)
     *
     * @param data_local
     * @param gps_zone UTM/UPS zone number
     * @param gps_northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    SensorDataUTM(const SensorDataLocal& data_local, int gps_zone, bool gps_northern_hemisphere)
        : SensorDataLocal(data_local)
        , gps_zone(gps_zone)
        , gps_northern_hemisphere(gps_northern_hemisphere)
    {
    }

    /**
     * @brief Construct an SensorDataUTM object from an existing SensorDataLatLon object (this
     * allows for implicit conversion from SensorDataLatLon class)
     *
     */
    SensorDataUTM(const SensorDataLatLon& data, int setzone = -1)
        : SensorDataUTM(from_sensordata(data, setzone))
    {
    }

    /**
     * @brief Construct a new SensorDataUTM object
     *
     * @param gps_northing in m, positive northwards
     * @param gpd_easting in m, positive eastwards
     * @param gps_zone UTM/UPS zone number
     * @param gps_northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param gps_z in m, positive downwards
     * @param heave_heave from heave sensor, will be added to gps_z in m, positive upwards
     * @param compass_heading from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is
     * east
     * @param imu_yaw in °, 0° is north, 90° is east
     * @param imu_pitch in °, positive means bow up
     * @param imu_roll in °, positive means port up
     */
    SensorDataUTM(double gps_northing,
                  double gps_easting,
                  int    gps_zone,
                  bool   gps_northern_hemisphere,
                  double gps_z,
                  double heave_heave,
                  double compass_heading,
                  double imu_yaw,
                  double imu_pitch,
                  double imu_roll)
        : SensorDataLocal(gps_northing,
                          gps_easting,
                          gps_z,
                          heave_heave,
                          compass_heading,
                          imu_yaw,
                          imu_pitch,
                          imu_roll)
        , gps_zone(gps_zone)
        , gps_northern_hemisphere(gps_northern_hemisphere)
    {
    }

    bool operator!=(const SensorDataUTM& rhs) const { return !(operator==(rhs)); }
    /**
     * @brief Check if two SensorDataUTM objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensorDataUTM& rhs) const
    {
        if (SensorDataLocal::operator==(rhs))
            if (gps_zone == rhs.gps_zone)
                if (gps_northern_hemisphere == rhs.gps_northern_hemisphere)
                    return true;

        return false;
    }
    /**
     * @brief Convert a utm sensordatalatlon to a unprojected data
     *
     * @param data_utm
     * @return SensorDataLatLon
     */
    static SensorDataLatLon to_sensordata(const SensorDataUTM& data_utm)
    {
        SensorDataLatLon data(0,
                              0,
                              data_utm.gps_z,
                              data_utm.heave_heave,
                              data_utm.compass_heading,
                              data_utm.imu_yaw,
                              data_utm.imu_pitch,
                              data_utm.imu_roll);

        GeographicLib::UTMUPS::Reverse(data_utm.gps_zone,
                                       data_utm.gps_northern_hemisphere,
                                       data_utm.gps_easting,
                                       data_utm.gps_northing,
                                       data.gps_latitude,
                                       data.gps_longitude);

        return data;
    }

    /**
     * @brief Construct convert a SensorDataLatLon Object to UTM
     *
     * @param data valid SensorDataLatLon object
     * @param setzone set a prefered UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return SensorDataUTM
     */
    static SensorDataUTM from_sensordata(const SensorDataLatLon& data, int setzone = -1)
    {
        SensorDataUTM data_utm(0,
                               0,
                               0,
                               0,
                               data.gps_z,
                               data.heave_heave,
                               data.compass_heading,
                               data.imu_yaw,
                               data.imu_pitch,
                               data.imu_roll);

        GeographicLib::UTMUPS::Forward(data.gps_latitude,
                                       data.gps_longitude,
                                       data_utm.gps_zone,
                                       data_utm.gps_northern_hemisphere,
                                       data_utm.gps_easting,
                                       data_utm.gps_northing,
                                       setzone);

        return data_utm;
    }

  private:
    // serialigps_zation support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.ext(*this, bitsery::ext::BaseClass<SensorDataLocal>{});
        s.value4b(gps_zone);
        s.value1b(gps_northern_hemisphere);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("SensorDataUTM");

        auto base_printer = SensorDataLocal::__printer__();
        base_printer.remove_sections();
        printer.append(base_printer);
        printer.register_value("gps_zone", gps_zone, "", 2);
        printer.register_value("gps_northern_hemisphere", gps_northern_hemisphere, "", 3);

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialigps_ze function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorDataUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

// backwards conversion
inline SensorDataLatLon::SensorDataLatLon(const SensorDataUTM& data_utm)
    : SensorDataLatLon(SensorDataUTM::to_sensordata(data_utm))
{
}

} // namespace navdata
} // namespace naviation
} // namespace themachinethatgoesping