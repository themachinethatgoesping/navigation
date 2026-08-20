// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordata.doc.hpp"

#include <iostream>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/rotation.hpp>

#include "positionaloffsets.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced location and attitude data from different sensors
 * (e.g. IMU, etc.)
 * No gps coordinates are stored in this structure (only depth).
 *
 */
struct Sensordata
{
    float depth = 0.0; ///< in m, positive downwards
    float heave = 0.0; ///< from heave source, will be added to depth in m, positive upwards
    /// combined heading/pitch/roll; exposed via heading()/pitch()/roll()
    tools::rotationfunctions::Rotation<float> rotation;

    /**
     * @brief Construct a new Sensordata object
     *
     */
    Sensordata() = default;

    /**
     * @brief Construct a new Sensordata object
     *
     * @param depth from depth source, in m, positive downwards
     * @param heave from heave sensor, will be added to depth in m, positive upwards
     * @param heading from heading source, in °, 0° is north, 90° is east
     * @param pitch from attitude source, in °, positive means bow up
     * @param roll from attitude source, in °, positive means port up
     */
    Sensordata(float depth, float heave, float heading, float pitch, float roll);

    /**
     * @brief Construct a new Sensordata object from depth, heave and a Rotation
     *
     * @param depth in m, positive downwards
     * @param heave from heave sensor, added to depth in m, positive upwards
     * @param rotation combined heading/pitch/roll orientation
     */
    Sensordata(float depth, float heave, tools::rotationfunctions::Rotation<float> rotation);

    /// @brief heading from heading source in °, 0° is north, 90° is east
    float heading() const;
    /// @brief pitch from attitude source in °, positive means bow up
    float pitch() const;
    /// @brief roll from attitude source in °, positive means port up
    float roll() const;

    /// @brief set heading, pitch and roll (°) at once
    void set_ypr(float heading, float pitch, float roll);
    /// @brief set heading (°), keeping pitch and roll
    void set_heading(float heading);
    /// @brief set pitch (°), keeping heading and roll
    void set_pitch(float pitch);
    /// @brief set roll (°), keeping heading and pitch
    void set_roll(float roll);

    bool operator!=(const Sensordata& rhs) const;
    /**
     * @brief Check if two Sensordata objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const Sensordata& rhs) const;

  public:
    // ----- file I/O -----
    static Sensordata from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialization function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(Sensordata)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping