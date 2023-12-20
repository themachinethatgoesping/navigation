// Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordata.doc.hpp"

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>
#include <themachinethatgoesping/tools/helper.hpp>
#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "../navtools.hpp"
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
    float depth   = 0.0; ///< in m, positive downwards
    float heave   = 0.0; ///< from heave source, will be added to depth in m, positive upwards
    float heading = 0.0; ///< from heading source in °, 0° is north, 90° is east
    float pitch   = 0.0; ///< from attitude source, in °, positive means bow up
    float roll    = 0.0; ///< from attitude source, in °, positive means port up

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
    Sensordata(float depth, float heave, float heading, float pitch, float roll)
        : depth(depth)
        , heave(heave)
        , heading(heading)
        , pitch(pitch)
        , roll(roll)
    {
    }

    bool operator!=(const Sensordata& rhs) const { return !(operator==(rhs)); }
    /**
     * @brief Check if two Sensordata objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const Sensordata& rhs) const
    {
        if (tools::helper::approx(depth, rhs.depth))
            if (tools::helper::approx(heave, rhs.heave))
                if (tools::helper::approx(heading, rhs.heading))
                    if (tools::helper::approx(pitch, rhs.pitch))
                        if (tools::helper::approx(roll, rhs.roll))
                            return true;

        return false;
    }

  public:
    // ----- file I/O -----
    static Sensordata from_stream(std::istream& is)
    {
        Sensordata data;

        is.read(reinterpret_cast<char*>(&data.depth), 5 * sizeof(float));

        return data;
    }

    void to_stream(std::ostream& os) const
    {
        os.write(reinterpret_cast<const char*>(&depth), 5 * sizeof(float));
    }

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelper::ObjectPrinter printer("Sensordata", float_precision);

        printer.register_value("depth", depth, "positive downwards, m");
        printer.register_value("heave", heave, "positive upwards, m");
        printer.register_value("heading", heading, "0° is north, 90 ° is east");
        printer.register_value("pitch", pitch, "° positive bow up");
        printer.register_value("roll", roll, "° positive port up");

        return printer;
    }

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