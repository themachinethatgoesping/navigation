// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools/classhelpers.hpp

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

};

} // namespace naviation
} // namespace themachinethatgoesping