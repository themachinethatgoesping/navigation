// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief A structure to set sensor or target offsets relative to the vessel coordinate system
 *
 */
struct SensorOffsets
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
    SensorOffsets() = default;

    /**
     * @brief Construct a new SensorOffsets object
     *
     * @param x in m, positive foorward
     * @param y in m, positive starboard
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    SensorOffsets(double x, double y, double z, double yaw, double pitch, double roll)
        : x(x)
        , y(y)
        , z(z)
        , yaw(yaw)
        , pitch(pitch)
        , roll(roll)
    {
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
    classhelpers::ObjectPrinter __printer__() const
    {
        classhelpers::ObjectPrinter printer("SensorOffsets");

        printer.register_enum("x", x, "m");
        printer.register_enum("y", y, "m");
        printer.register_enum("z", z, "m");
        printer.register_enum("yaw", yaw, "°");
        printer.register_enum("pitch", pitch, "°");
        printer.register_enum("roll", roll, "°");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensorOffsets)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__
};

} // namespace naviation
} // namespace themachinethatgoesping