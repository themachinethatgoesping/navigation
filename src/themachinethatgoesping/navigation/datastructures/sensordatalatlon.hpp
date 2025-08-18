// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordatalatlon.doc.hpp"

#include <iostream>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "sensordata.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// IGNORE_DOC:__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM
// forward declarations for location conversions
struct SensordataUTM; // defined in sensordatautm.hpp

/**
 * @brief A structure to store a georeferenced location and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 *
 */
struct SensordataLatLon : public Sensordata
{
    double latitude  = 0.0; ///< in °, positive northwards
    double longitude = 0.0; ///< in °, positive eastwards

    /**
     * @brief Construct a new SensordataLatLon object (all offsets set to 0)
     *
     */
    SensordataLatLon() = default;

    /**
     * @brief Construct a new Sensor Data Lat Lon object using a base sensor data object
     *
     * @param data
     * @param latitude in °, positive northwards
     * @param longitude in °, positive eastwards
     */
    SensordataLatLon(Sensordata data, double latitude, double longitude);

    /**
     * @brief Construct an SensordataLatLon object from an existing SensordataUTM object (this
     * allows for explicit conversion from SensordataUTM class)
     *
     */
    explicit SensordataLatLon(const SensordataUTM& data_utm); // defined in sensordatautm.hpp

    /**
     * @brief Construct a new SensordataLatLon object
     *
     * @param latitude in °, positive northwards
     * @param longitude in °, positive eastwards
     * @param depth in m, positive downwards
     * @param heave from heave sensor, will be added to depth in m, positive upwards
     * @param heading  in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    SensordataLatLon(double latitude,
                     double longitude,
                     float depth,
                     float heave,
                     float heading,
                     float pitch,
                     float roll);

    bool operator!=(const SensordataLatLon& rhs) const;
    /**
     * @brief Check if two SensordataLatLon objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensordataLatLon& rhs) const;

  public:
    // ----- file I/O -----
    static SensordataLatLon from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialization function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensordataLatLon)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping