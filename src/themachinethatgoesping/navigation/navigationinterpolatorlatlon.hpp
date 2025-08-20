// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/navigationinterpolatorlatlon.doc.hpp"

#include <vector>
#include <string>
#include <iostream>

#include <themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp>

#include "datastructures.hpp"
#include "i_navigationinterpolator.hpp"

// forward declarations
namespace themachinethatgoesping {
    namespace tools {
        namespace classhelper {
            class ObjectPrinter;
        }
    }
}

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief The NavInterpolator class: Interpolate navigation (lat/lon) values and attitude
 * information and transform the values using the offsets specified in the sensor configuration
 * class
 */
class NavigationInterpolatorLatLon : public I_NavigationInterpolator
{
    // LinearInterpolator for the depth in the world coordinate system
    tools::vectorinterpolators::AkimaInterpolator<double>
        _interpolator_latitude; ///< interpolator for the latitude data
    tools::vectorinterpolators::AkimaInterpolator<double>
        _interpolator_longitude; ///< interpolator for the longitude data

  protected:
    std::string class_name() const override { return "NavigationInterpolatorLatLon"; }

  public:
    /**
     * @brief Set the extrapolation mode for all interpolators
     *
     * @param extrapolation_mode extrapolate, fail or nearest
     */
    void set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                    tools::vectorinterpolators::t_extr_mode::extrapolate) override;

  public:
    /**
     * @brief Construct a new i navigationinterpolator interface
     *
     * @param sensor_configuration sensor configuration used for this navigation interpolator
     * @param extrapolation_mode extrapolate, fail or nearest
     */

    NavigationInterpolatorLatLon(SensorConfiguration sensor_configuration = SensorConfiguration(),
                                 tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                     tools::vectorinterpolators::t_extr_mode::extrapolate);

    /**
     * @brief Construct a new Navigation Interpolator Lat Lon object from a base Interpolator
     *
     * @param base Base I_NavigationInterpolator object
     */
    explicit NavigationInterpolatorLatLon(I_NavigationInterpolator base);

    virtual ~NavigationInterpolatorLatLon() = default;

    //----- operators -----
    bool operator==(const NavigationInterpolatorLatLon& other) const;
    bool operator!=(const NavigationInterpolatorLatLon& other) const;

    //----- set sensor data -----
    /**
     * @brief Set the data of the position system (latitude, longitude)
     *
     * @param timestamp in seconds since epoch
     * @param latitude latitude in °
     * @param longitude longitude in °
     */
    void set_data_position(const std::vector<double>& timestamp,
                           const std::vector<double>& latitude,
                           const std::vector<double>& longitude);

    /**
     * @brief direct reference to the latitude interpolator object
     *
     * @return interpolator_latitude&
     */
    auto& interpolator_latitude() { return _interpolator_latitude; }

    /**
     * @brief direct reference to the longitude interpolator object
     *
     * @return interpolator_longitude&
     */
    auto& interpolator_longitude() { return _interpolator_longitude; }

    //----- merge interpolators -----
    /**
     * @brief see documentation of I_NavigationInterpolator::merge
     */
    void merge(const NavigationInterpolatorLatLon& other);

    //----- compute the position of the target sensors -----
    /**
     * @brief Compute the position of the target "target_id" based on the sensor data for the given
     * timestamp stamp
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param timestamp timestamp in seconds since epoch
     * @return data structure that contains the position of the target in the world coordinate
     * system
     */
    datastructures::GeolocationLatLon operator()(const std::string& target_id,
                                                 double             timestamp) const;

    /**
     * @brief Compute the position of the target "target_id" based on the sensor data for the given
     * timestamp stamp
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param timestamp timestamp in seconds since epoch
     * @return data structure that contains the position of the target in the world coordinate
     * system
     */
    datastructures::GeolocationLatLon compute_target_position(const std::string& target_id,
                                                              double             timestamp) const;

    //----- compute the position of the target sensors -----
    /**
     * @brief Interpolate the saved sensor data for a specified timestamp stamp
     *
     * @param timestamp timestamp in seconds since epoch
     * @return data structure that contains the sensor data interpolated for the given timestamp
     * stamp
     */
    datastructures::SensordataLatLon get_sensor_data(double timestamp) const;

    bool valid() const override;

  public:
    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const;

    // ----- file I/O -----
    static NavigationInterpolatorLatLon from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NavigationInterpolatorLatLon)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

/**
 * @brief Boost hash function
 *
 * @param object object to hash
 * @return std::size_t
 */
std::size_t hash_value(
    const themachinethatgoesping::navigation::NavigationInterpolatorLatLon& object);

} // namespace navigation
} // namespace themachinethatgoesping

template<>
struct std::hash<themachinethatgoesping::navigation::NavigationInterpolatorLatLon>
{
    std::size_t operator()(
        const themachinethatgoesping::navigation::NavigationInterpolatorLatLon& object) const;
};

// IGNORE_DOC:__doc_themachinethatgoesping_navigation_hash_value
// IGNORE_DOC:__doc_hash_operator_call
// IGNORE_DOC:__doc_hash