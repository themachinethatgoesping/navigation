// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/geolocationlatlonvector.doc.hpp"

#include <iostream>
#include <vector>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

#include "geolocationlatlon.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A structure to store a vector of georeferenced locations with timestamps.
 * Provides efficient access to individual components as vectors for Python performance.
 */
class GeolocationLatLonVector
{
    std::vector<double>             _timestamps;   ///< timestamps in seconds since epoch
    std::vector<GeolocationLatLon>  _geolocations; ///< geolocation data

  public:
    /**
     * @brief Construct an empty GeolocationLatLonVector
     */
    GeolocationLatLonVector() = default;

    /**
     * @brief Construct a GeolocationLatLonVector with pre-allocated capacity
     * @param capacity number of elements to reserve
     */
    explicit GeolocationLatLonVector(size_t capacity);

    /**
     * @brief Construct a GeolocationLatLonVector from existing data
     * @param timestamps vector of timestamps
     * @param geolocations vector of geolocations (must be same size as timestamps)
     */
    GeolocationLatLonVector(std::vector<double>            timestamps,
                            std::vector<GeolocationLatLon> geolocations);

    // ----- element access -----
    /**
     * @brief Get the number of elements
     * @return size_t number of geolocations stored
     */
    size_t size() const { return _geolocations.size(); }

    /**
     * @brief Check if the vector is empty
     * @return true if no elements are stored
     */
    bool empty() const { return _geolocations.empty(); }

    /**
     * @brief Reserve capacity for n elements
     * @param n number of elements to reserve space for
     */
    void reserve(size_t n);

    /**
     * @brief Add a geolocation with timestamp
     * @param timestamp time in seconds since epoch
     * @param geolocation the geolocation to add
     */
    void push_back(double timestamp, const GeolocationLatLon& geolocation);

    /**
     * @brief Add a geolocation with timestamp (move version)
     * @param timestamp time in seconds since epoch
     * @param geolocation the geolocation to add
     */
    void push_back(double timestamp, GeolocationLatLon&& geolocation);

    /**
     * @brief Get geolocation at index
     * @param index position in the vector
     * @return const reference to geolocation
     */
    const GeolocationLatLon& at(size_t index) const { return _geolocations.at(index); }

    /**
     * @brief Get timestamp at index
     * @param index position in the vector
     * @return timestamp value
     */
    double timestamp_at(size_t index) const { return _timestamps.at(index); }

    // ----- direct access to internal vectors -----
    const std::vector<double>&            get_timestamps() const { return _timestamps; }
    const std::vector<GeolocationLatLon>& get_geolocations() const { return _geolocations; }

    // ----- component-wise access (for Python performance) -----
    /**
     * @brief Get all latitudes as a vector
     * @return vector of latitudes in degrees
     */
    std::vector<double> get_latitudes() const;

    /**
     * @brief Get all longitudes as a vector
     * @return vector of longitudes in degrees
     */
    std::vector<double> get_longitudes() const;

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

    // ----- operators -----
    bool operator==(const GeolocationLatLonVector& other) const;
    bool operator!=(const GeolocationLatLonVector& other) const { return !(*this == other); }

    // ----- file I/O -----
    static GeolocationLatLonVector from_stream(std::istream& is);
    void to_stream(std::ostream& os) const;

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const;

    // -- class helper function macros --
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(GeolocationLatLonVector)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
