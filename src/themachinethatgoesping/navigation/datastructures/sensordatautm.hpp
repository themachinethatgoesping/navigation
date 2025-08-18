// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordatautm.doc.hpp"

#include <iostream>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "sensordatalatlon.hpp"
#include "sensordatalocal.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced data and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 * Unlike SensordataLatLon, this structure stores UTM coordinates.
 *
 */
struct SensordataUTM : public SensordataLocal
{
    int  utm_zone = 0; ///< UTM/UPS zone number
    bool northern_hemisphere =
        true; ///< if true: northern hemisphere, else: southern hemisphere

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    SensordataUTM() = default;

    /**
     * @brief Construct a new Sensor Data Local object using a base sensor data object
     *
     * @param data
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    SensordataUTM(Sensordata data,
                  double     northing,
                  double     easting,
                  int        utm_zone,
                  bool       northern_hemisphere);

    /**
     * @brief Construct an SensordataUTM object from an existing SensordataLocal object (using a
     * known zone and hemisphere)
     *
     * @param data_local
     * @param utm_zone UTM/UPS zone number
     * @param northern_hemisphere if true: northern hemisphere, else: southern hemisphere
     */
    SensordataUTM(SensordataLocal data_local, int utm_zone, bool northern_hemisphere);

    /**
     * @brief Construct an SensordataUTM object from an existing SensordataLatLon object (this
     * allows for explicit conversion from SensordataLatLon class)
     *
     */
    explicit SensordataUTM(const SensordataLatLon& data, int setzone = -1);

    /**
     * @brief Construct a new SensordataUTM object
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
    SensordataUTM(double northing,
                  double easting,
                  int    utm_zone,
                  bool   northern_hemisphere,
                  float  depth,
                  float  heave,
                  float  heading,
                  float  pitch,
                  float  roll);

    bool operator!=(const SensordataUTM& rhs) const;
    /**
     * @brief Check if two SensordataUTM objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensordataUTM& rhs) const;
    /**
     * @brief Convert a utm sensordatalatlon to an unprojected data
     *
     * @param data_utm
     * @return SensordataLatLon
     */
    static SensordataLatLon to_sensordata(const SensordataUTM& data_utm);

    /**
     * @brief Construct convert a SensordataLatLon Object to UTM
     *
     * @param data valid SensordataLatLon object
     * @param setzone set a preferred UTM zone negative means automatic, zero means UPS, positive
     * means a particular UTM zone
     * @return SensordataUTM
     */
    static SensordataUTM from_sensordata(const SensordataLatLon& data, int setzone = -1);

  public:
    // ----- file I/O -----
    static SensordataUTM from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialization function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensordataUTM)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

// IGNORE_DOC:__doc_themachinethatgoesping_navigation_datastructures_SensordataLatLon
// backwards conversion - this is implemented in sensordatautm.cpp  
SensordataLatLon::SensordataLatLon(const SensordataUTM& data_utm);

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping