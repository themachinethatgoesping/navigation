// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/navigationinterpolatorlatlon.doc.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <xtensor/containers/xtensor.hpp>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp>
#include <themachinethatgoesping/tools/helper/downsampling.hpp>
#include <themachinethatgoesping/tools/helper/container_intersection.hpp>

#include "datastructures.hpp"
#include "i_navigationinterpolator.hpp"

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
    void set_extrapolation_mode(tools::vectorinterpolators::o_extr_mode extrapolation_mode =
                                    tools::vectorinterpolators::t_extr_mode::extrapolate) override;

  public:
    /**
     * @brief Construct a new i navigationinterpolator interface
     *
     * @param sensor_configuration sensor configuration used for this navigation interpolator
     * @param extrapolation_mode extrapolate, fail or nearest
     */

    NavigationInterpolatorLatLon(SensorConfiguration sensor_configuration = SensorConfiguration(),
                                 tools::vectorinterpolators::o_extr_mode extrapolation_mode =
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
    auto&       interpolator_latitude() { return _interpolator_latitude; }
    const auto& interpolator_latitude() const { return _interpolator_latitude; }

    /**
     * @brief direct reference to the longitude interpolator object
     *
     * @return interpolator_longitude&
     */
    auto&       interpolator_longitude() { return _interpolator_longitude; }
    const auto& interpolator_longitude() const { return _interpolator_longitude; }

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

    // get sampled timestamps
    // ----- get sampled x -----
    xt::xtensor<XType, 1> get_sampled_timestamps(
        std::set<std::string> sensor_names        = { "latitude", "longitude" },
        double                downsample_interval = std::numeric_limits<double>::quiet_NaN(),
        double                max_gap             = std::numeric_limits<double>::quiet_NaN()) const
    {
        std::vector<xt::xtensor<XType, 1>> timestamp_vectors;
        for (const auto& sensor_name : sensor_names)
        {
            const auto name_lower = tools::helper::string_to_lower(sensor_name);
            if (name_lower == "latitude")
            {
                timestamp_vectors.push_back(_interpolator_latitude.get_data_X());
            }
            else if (name_lower == "longitude")
            {
                timestamp_vectors.push_back(_interpolator_longitude.get_data_X());
            }
            else if (name_lower == "attitude")
            {
                timestamp_vectors.push_back(_interpolator_attitude.get_data_X());
            }
            else if (name_lower == "heading")
            {
                timestamp_vectors.push_back(_interpolator_heading.get_data_X());
            }
            else if (name_lower == "heave")
            {
                timestamp_vectors.push_back(_interpolator_heave.get_data_X());
            }
            else if (name_lower == "depth")
            {
                timestamp_vectors.push_back(_interpolator_depth.get_data_X());
            }
            else
            {
                throw std::invalid_argument(
                    "NavigationInterpolatorLatLon::get_sampled_timestamps: Unknown sensor name '" +
                    sensor_name + "'!");
            }
        }

        const auto common_timestamps = tools::helper::container_intersection(timestamp_vectors);
        return tools::helper::get_value_downsampling(common_timestamps, downsample_interval, max_gap);
    }
