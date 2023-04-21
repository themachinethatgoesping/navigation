// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge GEOMAR Helmholtz
// Centre for Ocean Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban,
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/positionaloffsets.doc.hpp"

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>
#include <themachinethatgoesping/tools/helper.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

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
    std::string name;        ///< The name of the sensor
    double      x     = 0.0; ///< in m, positive forward
    double      y     = 0.0; ///< in m, positive starboard
    double      z     = 0.0; ///< in m, positive downwards
    double      yaw   = 0.0; ///< in °, positive means clockwise rotation
    double      pitch = 0.0; ///< in °, positive means bow up
    double      roll  = 0.0; ///< in °, positive means port up

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
     */
    PositionalOffsets(std::string_view name,
                      double           x,
                      double           y,
                      double           z,
                      double           yaw,
                      double           pitch,
                      double           roll)
        : name(std::string(name))
        , x(x)
        , y(y)
        , z(z)
        , yaw(yaw)
        , pitch(pitch)
        , roll(roll)
    {
    }

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
                                       std::string              name)
    {
        PositionalOffsets trx;

        trx.name = std::move(name);

        /* x,y,z are the average of tx and rx */
        trx.x = (tx.x + rx.x) * 0.5;
        trx.y = (tx.y + rx.y) * 0.5;
        trx.z = (tx.z + rx.z) * 0.5;

        /* take pitch and yaw from tx and roll from rx*/
        trx.pitch = tx.pitch;
        trx.yaw   = tx.yaw; // not sure about this one ...
        trx.roll  = rx.roll;

        return trx;
    }

    bool operator!=(const PositionalOffsets& rhs) const { return !(operator==(rhs)); }
    bool operator==(const PositionalOffsets& rhs) const
    {
        if (name == rhs.name)
            if (tools::helper::approx(x, rhs.x))
                if (tools::helper::approx(y, rhs.y))
                    if (tools::helper::approx(z, rhs.z))
                        if (tools::helper::approx(yaw, rhs.yaw))
                            if (tools::helper::approx(pitch, rhs.pitch))
                                if (tools::helper::approx(roll, rhs.roll))
                                    return true;

        return false;
    }

  public:
    // ----- file I/O -----
    static PositionalOffsets from_stream(std::istream& is)
    {
        PositionalOffsets data;

        data.name = tools::classhelper::stream::container_from_stream<std::string>(is);

        is.read(reinterpret_cast<char*>(&data.x), 6 * sizeof(double));

        return data;
    }

    void to_stream(std::ostream& os) const
    {
        tools::classhelper::stream::container_to_stream(os, name);

        os.write(reinterpret_cast<const char*>(&x), 6 * sizeof(double));
    }

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelper::ObjectPrinter printer("PositionalOffsets", float_precision);

        printer.register_string("name", name, "The name of the sensor");
        printer.register_value("x", x, "positive forwards, m");
        printer.register_value("y", y, "positive starboard, m");
        printer.register_value("z", z, "positive downwards, m");
        printer.register_value("yaw", yaw, "° positive means clockwise rotation");
        printer.register_value("pitch", pitch, "° positive means bow up");
        printer.register_value("roll", roll, "° positive means port up");

        return printer;
    }

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