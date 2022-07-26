// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helpers.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "../navtools.hpp"
#include "sensordata.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// foorwad declarations for location conversions
struct SensorDataLocal; // defined in sensordatalocal.hpp

/**
 * @brief A structure to store a georeferenced data and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 * Unlike SensorData, this structure stores UTM coordinates.
 *
 */
struct SensorDataUTM
{
    double gps_northing = 0.0; ///< in m, positive northwards
    double gps_easting  = 0.0; ///< in m, positive eastwards
    int    gps_zone     = 0;   ///< UTM/UPS zone number
    bool   gps_northern_hemisphere =
        true;                 ///< if true: northern hemisphere, else: southern hemisphere
    double gps_z       = 0.0; ///< in m, positive downwards
    double heave_heave = 0.0; ///< from heave sensor, will be added to gps_z in m, positive upwards
    double compass_heading =
        NAN; ///< from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is east
    double imu_yaw   = 0.0; ///< from motion sensor, in °, 0° is north, 90° is east
    double imu_pitch = 0.0; ///< from motion sensor, in °, positive means bow up
    double imu_roll  = 0.0; ///< from motion sensor, in °, positive means port up

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    SensorDataUTM() = default;

    /**
     * @brief Construct an SensorDataUTM object from an existing SensorData object (this allows
     * for implicit conversion from SensorData class)
     *
     */
    SensorDataUTM(const SensorData& data, int setzone = -1)
        : SensorDataUTM(from_sensordata(data, setzone))
    {
    }

    /**
     * @brief Construct an SensorDataUTM object from an existing SensorDataLocal object (using a
     * known zone and hemisphere)
     *
     * @param data_local
     * @param gps_zone UTM/UPS zone number
     * @param gps_northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param offset_northing in m, is added to northing coordinate
     * @param offset_easting in m, is added to easting coordinate
     */
    SensorDataUTM(const SensorDataLocal& data_local,
                  int                    gps_zone,
                  bool                   gps_northern_hemisphere,
                  double                 offset_northing = 0.0,
                  double                 offset_easting  = 0.0); // defined in sensordatalocal.hpp

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
        : gps_northing(gps_northing)
        , gps_easting(gps_easting)
        , gps_zone(gps_zone)
        , gps_northern_hemisphere(gps_northern_hemisphere)
        , gps_z(gps_z)
        , heave_heave(heave_heave)
        , compass_heading(compass_heading)
        , imu_yaw(imu_yaw)
        , imu_pitch(imu_pitch)
        , imu_roll(imu_roll)
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
        if (tools::helpers::approx(gps_northing, rhs.gps_northing))
            if (tools::helpers::approx(gps_easting, rhs.gps_easting))
                if (gps_zone == rhs.gps_zone)
                    if (gps_northern_hemisphere == rhs.gps_northern_hemisphere)
                        if (tools::helpers::approx(gps_z, rhs.gps_z))
                            if (tools::helpers::approx(heave_heave, rhs.heave_heave))
                                if (tools::helpers::approx(compass_heading, rhs.compass_heading))
                                    if (tools::helpers::approx(imu_yaw, rhs.imu_yaw))
                                        if (tools::helpers::approx(imu_pitch, rhs.imu_pitch))
                                            if (tools::helpers::approx(imu_roll, rhs.imu_roll))
                                                return true;

        return false;
    }
    /**
     * @brief Convert a utm sensordata to a unprojected data
     *
     * @param data_utm
     * @return SensorData
     */
    static SensorData to_sensordata(const SensorDataUTM& data_utm)
    {
        SensorData data(0,
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
     * @brief Construct convert a SensorData Object to UTM
     *
     * @param data valid SensorData object
     * @param setzone set a prefered UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return SensorDataUTM
     */
    static SensorDataUTM from_sensordata(const SensorData& data, int setzone = -1)
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
        s.value8b(gps_northing);
        s.value8b(gps_easting);
        s.value4b(gps_zone);
        s.value1b(gps_northern_hemisphere);
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
        tools::classhelpers::ObjectPrinter printer("SensorDataUTM");

        printer.register_value("gps_northing", gps_northing, "positive northwards, m");
        printer.register_value("gps_easting", gps_easting, "positive eastwards, m");
        printer.register_value("gps_zone", gps_zone);
        printer.register_value("gps_northern_hemisphere", gps_northern_hemisphere);
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
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorDataUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

// backwards conversion
inline SensorData::SensorData(const SensorDataUTM& data_utm)
    : SensorData(SensorDataUTM::to_sensordata(data_utm))
{
}

} // namespace datastructures
} // namespace naviation
} // namespace themachinethatgoesping