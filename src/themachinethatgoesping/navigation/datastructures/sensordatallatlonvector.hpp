// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensordatallatlonvector.doc.hpp"

#include "datavector.hpp"
#include "sensordatalatlon.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A class to store a vector of SensordataLatLon elements with timestamps.
 */
class SensordataLatLonVector : public DataVector<SensordataLatLon, SensordataLatLonVector>
{
    using Base = DataVector<SensordataLatLon, SensordataLatLonVector>;

  public:
    // Inherit constructors
    using Base::Base;

    // ----- component-wise access (for Python performance) -----
    /**
     * @brief Get all latitude values as a vector
     * @return vector of latitude values in degrees
     */
    std::vector<double> get_latitudes() const;

    /**
     * @brief Get all longitude values as a vector
     * @return vector of longitude values in degrees
     */
    std::vector<double> get_longitudes() const;

    /**
     * @brief Get all depth values as a vector
     * @return vector of depth values in meters (positive downwards)
     */
    std::vector<float> get_depths() const;

    /**
     * @brief Get all heave values as a vector
     * @return vector of heave values in meters
     */
    std::vector<float> get_heaves() const;

    /**
     * @brief Get all heading values as a vector
     * @return vector of heading values in degrees
     */
    std::vector<float> get_headings() const;

    /**
     * @brief Get all pitch values as a vector
     * @return vector of pitch values in degrees
     */
    std::vector<float> get_pitches() const;

    /**
     * @brief Get all roll values as a vector
     * @return vector of roll values in degrees
     */
    std::vector<float> get_rolls() const;

    // ----- file I/O -----
    static SensordataLatLonVector from_stream(std::istream& is);
    void                          to_stream(std::ostream& os) const;

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const;

    // -- class helper function macros --
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SensordataLatLonVector)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
