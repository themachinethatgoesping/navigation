// Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordatautm.doc.hpp"

#include <GeographicLib/UTMUPS.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>
#include <themachinethatgoesping/tools/helper.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "../navtools.hpp"
#include "sensordatalatlon.hpp"
#include "sensordatalocal.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced data and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 * Unlike SensorDataLatLon, this structure stores UTM coordinates.
 *
 */
struct SensorDataUTM : public SensorDataLocal
{
    int  utm_zone = 0; ///< UTM/UPS zone number
    bool northern_hemisphere =
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
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    SensorDataUTM(SensorData data,
                  double     northing,
                  double     easting,
                  int        utm_zone,
                  bool       northern_hemisphere)
        : SensorDataLocal(std::move(data), northing, easting)
        , utm_zone(utm_zone)
        , northern_hemisphere(northern_hemisphere)
    {
    }

    /**
     * @brief Construct an SensorDataUTM object from an existing SensorDataLocal object (using a
     * known zone and hemisphere)
     *
     * @param data_local
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    SensorDataUTM(SensorDataLocal data_local, int utm_zone, bool northern_hemisphere)
        : SensorDataLocal(std::move(data_local))
        , utm_zone(utm_zone)
        , northern_hemisphere(northern_hemisphere)
    {
    }

    /**
     * @brief Construct an SensorDataUTM object from an existing SensorDataLatLon object (this
     * allows for explicit conversion from SensorDataLatLon class)
     *
     */
    explicit SensorDataUTM(const SensorDataLatLon& data, int setzone = -1)
        : SensorDataUTM(from_sensordata(data, setzone))
    {
    }

    /**
     * @brief Construct a new SensorDataUTM object
     *
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     * @param depth in m, positive downwards
     * @param heave is added to depth in m, positive upwards
     * @param heading in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    SensorDataUTM(double northing,
                  double easting,
                  int    utm_zone,
                  bool   northern_hemisphere,
                  float  depth,
                  float  heave,
                  float  heading,
                  float  pitch,
                  float  roll)
        : SensorDataLocal(northing, easting, depth, heave, heading, pitch, roll)
        , utm_zone(utm_zone)
        , northern_hemisphere(northern_hemisphere)
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
            if (utm_zone == rhs.utm_zone)
                if (northern_hemisphere == rhs.northern_hemisphere)
                    return true;

        return false;
    }
    /**
     * @brief Convert a utm sensordatalatlon to an unprojected data
     *
     * @param data_utm
     * @return SensorDataLatLon
     */
    static SensorDataLatLon to_sensordata(const SensorDataUTM& data_utm)
    {
        SensorDataLatLon data(
            0, 0, data_utm.depth, data_utm.heave, data_utm.heading, data_utm.pitch, data_utm.roll);

        GeographicLib::UTMUPS::Reverse(data_utm.utm_zone,
                                       data_utm.northern_hemisphere,
                                       data_utm.easting,
                                       data_utm.northing,
                                       data.latitude,
                                       data.longitude);

        return data;
    }

    /**
     * @brief Construct convert a SensorDataLatLon Object to UTM
     *
     * @param data valid SensorDataLatLon object
     * @param setzone set a preferred UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return SensorDataUTM
     */
    static SensorDataUTM from_sensordata(const SensorDataLatLon& data, int setzone = -1)
    {
        SensorDataUTM data_utm(
            0, 0, 0, 0, data.depth, data.heave, data.heading, data.pitch, data.roll);

        GeographicLib::UTMUPS::Forward(data.latitude,
                                       data.longitude,
                                       data_utm.utm_zone,
                                       data_utm.northern_hemisphere,
                                       data_utm.easting,
                                       data_utm.northing,
                                       setzone);

        return data_utm;
    }

  public:
    // ----- file I/O -----
    static SensorDataUTM from_stream(std::istream& is)
    {
        SensorDataUTM data(SensorDataLocal::from_stream(is), 0, 0);

        is.read(reinterpret_cast<char*>(&data.utm_zone), sizeof(int));
        is.read(reinterpret_cast<char*>(&data.northern_hemisphere), sizeof(bool));

        return data;
    }

    void to_stream(std::ostream& os) const
    {
        SensorDataLocal::to_stream(os);

        os.write(reinterpret_cast<const char*>(&utm_zone), sizeof(int));
        os.write(reinterpret_cast<const char*>(&northern_hemisphere), sizeof(bool));
    }

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelper::ObjectPrinter printer("SensorDataUTM", float_precision);

        auto base_printer = SensorDataLocal::__printer__(float_precision);
        base_printer.remove_sections();
        printer.append(base_printer);
        printer.register_value("utm_zone", utm_zone, "", 2);
        printer.register_value("northern_hemisphere", northern_hemisphere, "", 3);

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialization function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorDataUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

// IGNORE_DOC: __doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon
// backwards conversion
inline SensorDataLatLon::SensorDataLatLon(const SensorDataUTM& data_utm)
    : SensorDataLatLon(SensorDataUTM::to_sensordata(data_utm))
{
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping