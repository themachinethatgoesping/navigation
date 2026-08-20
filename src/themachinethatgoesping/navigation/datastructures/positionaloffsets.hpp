// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge GEOMAR Helmholtz
// Centre for Ocean Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban,
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/positionaloffsets.doc.hpp"

#include <iostream>
#include <string>
#include <string_view>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/rotation.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store positional offsets (e.g. of a sensor) relative to
 * the vessel coordinate system
 *
 */
struct PositionalOffsets
{
    std::string name;      ///< The name of the sensor
    float       x = 0.0;   ///< in m, positive forward
    float       y = 0.0;   ///< in m, positive starboard
    float       z = 0.0;   ///< in m, positive downwards
    /// yaw/pitch/roll offsets (°); exposed via yaw()/pitch()/roll()
    tools::rotationfunctions::Rotation<float> rotation;

    /// if true, the yaw/pitch/roll offsets are already applied to the associated sensor data
    /// stream (e.g. Kongsberg .all logs the attitude/heading already corrected for the sensor
    /// mounting offsets). In that case the SensorConfiguration must not re-apply them when
    /// computing the vessel rotation. If false (default), the offsets still have to be applied.
    bool ypr_offsets_applied = false;

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    PositionalOffsets() = default;

    /**
     * @brief Construct a new PositionalOffsets object
     *
     * @param name The name of the sensor
     * @param x in m, positive forward
     * @param y in m, positive starboard
     * @param z in m, positive downwards
     * @param yaw positive means clockwise rotation
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     * @param ypr_offsets_applied if true, the yaw/pitch/roll offsets are already applied to the
     *        associated sensor data (default: false)
     */
    PositionalOffsets(std::string_view name,
                      float            x,
                      float            y,
                      float            z,
                      float            yaw,
                      float            pitch,
                      float            roll,
                      bool             ypr_offsets_applied = false);

    /**
     * @brief Construct a new PositionalOffsets object from a Rotation
     *
     * @param name The name of the sensor
     * @param x in m, positive forward
     * @param y in m, positive starboard
     * @param z in m, positive downwards
     * @param rotation yaw/pitch/roll offset orientation
     * @param ypr_offsets_applied if true, the offsets are already applied (default: false)
     */
    PositionalOffsets(std::string_view                          name,
                      float                                     x,
                      float                                     y,
                      float                                     z,
                      tools::rotationfunctions::Rotation<float> rotation,
                      bool                                      ypr_offsets_applied = false);

    /// @brief yaw in °, positive means clockwise rotation
    float yaw() const;
    /// @brief pitch in °, positive means bow up
    float pitch() const;
    /// @brief roll in °, positive means port up
    float roll() const;

    /// @brief set yaw, pitch and roll (°) at once
    void set_ypr(float yaw, float pitch, float roll);
    /// @brief set yaw (°), keeping pitch and roll
    void set_yaw(float yaw);
    /// @brief set pitch (°), keeping yaw and roll
    void set_pitch(float pitch);
    /// @brief set roll (°), keeping yaw and pitch
    void set_roll(float roll);

    /**
     * @brief Construct a new PositionalOffsets object from a transmitter and receiver unit
     *
     * @param tx Multibeam transmitter offsets
     * @param rx Multibeam receiver offsets
     * @param name Name of the newly constructed transceiver offsets
     * @return Transceiver PositionalOffsets
     */
    static PositionalOffsets from_txrx(const PositionalOffsets& tx,
                                       const PositionalOffsets& rx,
                                       std::string              name);

    bool operator!=(const PositionalOffsets& rhs) const;
    bool operator==(const PositionalOffsets& rhs) const;

  public:
    // ----- file I/O -----
    static PositionalOffsets from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(PositionalOffsets)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping