// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordatalocal.doc.hpp"

#include <iostream>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "sensordata.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced data and attitude data from different sensors
 * (e.g. GPS, IMU, etc.)
 * Unlike SensordataUTM, this structure stores coordinates without zone and hemisphere information.
 *
 */
struct SensordataLocal : public Sensordata
{
    double northing = 0.0; ///< in m, positive northwards
    double easting  = 0.0; ///< in m, positive eastwards

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    SensordataLocal() = default;

    /**
     * @brief Construct a new Sensor Data Local object using a base sensor data object
     *
     * @param data
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     */
    SensordataLocal(Sensordata data, double northing, double easting);

    /**
     * @brief Construct a new SensordataLocal object
     *
     * @param northing in m, positive northwards
     * @param easting in m, positive eastwards
     * @param depth in m, positive downwards
     * @param heave from heave sensor, will be added to depth in m, positive upwards
     * @param heading in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    SensordataLocal(double northing,
                    double easting,
                    float depth,
                    float heave,
                    float heading,
                    float pitch,
                    float roll);

    bool operator!=(const SensordataLocal& rhs) const;
    /**
     * @brief Check if two SensordataLocal objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const SensordataLocal& rhs) const;

  public:
    // ----- file I/O -----
    static SensordataLocal from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialization function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensordataLocal)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping