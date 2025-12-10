// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationlocalvector.doc.hpp"

#include "datavector.hpp"
#include "geolocationlocal.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A class to store a vector of GeolocationLocal elements with timestamps.
 */
class GeolocationLocalVector : public DataVector<GeolocationLocal, GeolocationLocalVector>
{
    using Base = DataVector<GeolocationLocal, GeolocationLocalVector>;

  public:
    // Inherit constructors
    using Base::Base;

    // ----- component-wise access (for Python performance) -----
    /**
     * @brief Get all northing values as a vector
     * @return vector of northing values in meters
     */
    std::vector<double> get_northings() const;

    /**
     * @brief Get all easting values as a vector
     * @return vector of easting values in meters
     */
    std::vector<double> get_eastings() const;

    /**
     * @brief Get all z values (depth) as a vector
     * @return vector of z values in meters (positive downwards)
     */
    std::vector<float> get_z() const;

    /**
     * @brief Get all yaw values as a vector
     * @return vector of yaw values in degrees
     */
    std::vector<float> get_yaw() const;

    /**
     * @brief Get all pitch values as a vector
     * @return vector of pitch values in degrees
     */
    std::vector<float> get_pitch() const;

    /**
     * @brief Get all roll values as a vector
     * @return vector of roll values in degrees
     */
    std::vector<float> get_roll() const;

    // ----- file I/O -----
    static GeolocationLocalVector from_stream(std::istream& is);
    void                          to_stream(std::ostream& os) const;

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const;

    // -- class helper function macros --
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeolocationLocalVector)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
