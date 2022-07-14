// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge GEOMAR Helmholtz Centre for Ocean Research
// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/helpers.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief A structure to store positional offsets (e.g. of a sensor) relative to the vessel coordinate system
 *
 */
struct PositionalOffsets
{
    double x     = 0.0; ///< in m, positive foorward
    double y     = 0.0; ///< in m, positive starboard
    double z     = 0.0; ///< in m, positive downwards
    double yaw   = 0.0; ///< in °, 0° is north, 90° is east
    double pitch = 0.0; ///< in °, positive means bow up
    double roll  = 0.0; ///< in °, positive means port up

    /**
     * @brief Construct a new Sensor Position object (all offsets set to 0)
     *
     */
    PositionalOffsets() = default;

    /**
     * @brief Construct a new PositionalOffsets object
     *
     * @param x in m, positive foorward
     * @param y in m, positive starboard
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    PositionalOffsets(double x, double y, double z, double yaw, double pitch, double roll)
        : x(x)
        , y(y)
        , z(z)
        , yaw(yaw)
        , pitch(pitch)
        , roll(roll)
    {
    }

    bool operator!=(const PositionalOffsets& rhs) const { return !(operator==(rhs)); }
    bool operator==(const PositionalOffsets& rhs) const
    {
        if (tools::helpers::approx(x, rhs.x))
            if (tools::helpers::approx(y, rhs.y))
                if (tools::helpers::approx(z, rhs.z))
                    if (tools::helpers::approx(yaw, rhs.yaw))
                        if (tools::helpers::approx(pitch, rhs.pitch))
                            if (tools::helpers::approx(roll, rhs.roll))
                                return true;

        return false;
    }

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.value8b(x);
        s.value8b(y);
        s.value8b(z);
        s.value8b(yaw);
        s.value8b(pitch);
        s.value8b(roll);
    }

  public:
    tools::classhelpers::ObjectPrinter __printer__() const
    {
        tools::classhelpers::ObjectPrinter printer("PositionalOffsets");

        printer.register_value("x", x, "positive forwards, m");
        printer.register_value("y", y, "positive starboard, m");
        printer.register_value("z", z, "positive downwards, m");
        printer.register_value("yaw", yaw, "90 ° at east");
        printer.register_value("pitch", pitch, "° positve bow up");
        printer.register_value("roll", roll, "° positive port up");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(PositionalOffsets)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

} // namespace naviation
} // namespace themachinethatgoesping