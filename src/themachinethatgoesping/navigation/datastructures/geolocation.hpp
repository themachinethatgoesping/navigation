// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocation.doc.hpp"

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a georeferenced location and attitude (e.g. of a sensor)
 * This structure does not store any coordinates except the depth (z)
 *
 */
struct Geolocation
{
    float z     = 0;   ///< in m, positive downwards
    float yaw   = 0.0; ///< in °, 0° is north, 90° is east
    float pitch = 0.0; ///< in °, positive means bow up
    float roll  = 0.0; ///< in °, positive means port up

    /**
     * @brief Construct a new Position object
     *
     */
    Geolocation() = default;

    /**
     * @brief Construct a new Geolocation object
     *
     * @param z in m, positive downwards
     * @param yaw in °, 0° is north, 90° is east
     * @param pitch in °, positive means bow up
     * @param roll in °, positive means port up
     */
    Geolocation(float z, float yaw, float pitch, float roll);

    /**
     * @brief Construct a new Geolocation object from a string
     *
     * @param str string containing the location in the format "latitude,longitude,z,yaw,pitch,roll"
     */
    bool operator!=(const Geolocation& rhs) const;

    /**
     * @brief Check if two Geolocation objects are equal
     *
     * @param rhs
     * @return true if equal
     * @return false if not equal
     */
    bool operator==(const Geolocation& rhs) const;

  public:
    // ----- file I/O -----
    static Geolocation from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(Geolocation)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping