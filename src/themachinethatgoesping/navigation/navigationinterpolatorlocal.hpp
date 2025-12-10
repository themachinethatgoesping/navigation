// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/navigationinterpolatorlocal.doc.hpp"

#include <vector>
#include <string>
#include <iostream>

#include <themachinethatgoesping/tools/classhelper/classversion.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp>

#include "datastructures.hpp"
#include "i_navigationinterpolator.hpp"


namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief The NavInterpolator class: Interpolate navigation (northing/easting no zone specified)
 * values and attitude information and transform the values using the offsets specified in the
 * sensor configuration class
 */
class NavigationInterpolatorLocal : public I_NavigationInterpolator
{

    // LinearInterpolator for the depth in the world coordinate system
    tools::vectorinterpolators::AkimaInterpolator<double>
        _interpolator_northing; ///< interpolator for the northing data
    tools::vectorinterpolators::AkimaInterpolator<double>
        _interpolator_easting; ///< interpolator for the easting data

    std::string class_name() const override { return "NavigationInterpolatorLocal"; }

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
    NavigationInterpolatorLocal(SensorConfiguration                     sensor_configuration,
                                tools::vectorinterpolators::o_extr_mode extrapolation_mode =
                                    tools::vectorinterpolators::t_extr_mode::extrapolate);

    /**
     * @brief Construct a new Navigation Interpolator Lat Lon object from a base Interpolator
     *
     * @param base Base I_NavigationInterpolator object
     */
    explicit NavigationInterpolatorLocal(I_NavigationInterpolator base);

    virtual ~NavigationInterpolatorLocal() = default;

    //----- operators -----
    bool operator==(const NavigationInterpolatorLocal& other) const;
    bool operator!=(const NavigationInterpolatorLocal& other) const;

    //----- set sensor data -----
    /**
     * @brief Set the data of the position system (northing, easting)
     *
     * @param timestamp in seconds since epoch
     * @param northing northing in meters
     * @param easting easting in meters
     */
    void set_data_position(const std::vector<double>& timestamp,
                           const std::vector<double>& northing,
                           const std::vector<double>& easting);

    /**
     * @briefSet the data of the position system (northing, easting) and the offsets of the
     * position system
     *
     * @param timestamp in seconds since epoch
     * @param northing in meters
     * @param easting in meters
     * @param name of the position system
     * @param offset_x in m, positive forward
     * @param offset_y in m, positive starboard
     * @param offset_z in m, positive down
     */
    void set_data_position(const std::vector<double>& timestamp,
                           const std::vector<double>& northing,
                           const std::vector<double>& easting,
                           std::string_view           name,
                           float                      offset_x,
                           float                      offset_y,
                           float                      offset_z);

    /**
     * @briefSet the data of the position system (northing, easting) and the offsets of the
     * position system
     *
     * @param timestamp in seconds since epoch
     * @param northing in meters
     * @param easting in meters
     * @param sensor_offsets structure containing the offsets of the position system
     */
    void set_data_position(const std::vector<double>&               timestamp,
                           const std::vector<double>&               northing,
                           const std::vector<double>&               easting,
                           const datastructures::PositionalOffsets& sensor_offsets);

    /**
     * @brief direct reference to the northing interpolator object
     *
     * @return interpolator_northing&
     */
    auto& interpolator_northing() { return _interpolator_northing; }
    const auto& interpolator_northing() const { return _interpolator_northing; }

    /**
     * @brief direct reference to the easting interpolator object
     *
     * @return interpolator_easting&
     */
    auto& interpolator_easting() { return _interpolator_easting; }
    const auto& interpolator_easting() const { return _interpolator_easting; }
    //----- merge interpolators -----
    /**
     * @brief see documentation of I_NavigationInterpolator::merge
     */
    void merge(const NavigationInterpolatorLocal& other);

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
    datastructures::GeolocationLocal compute_target_position(const std::string& target_id,
                                                             double             timestamp) const;

    //----- compute the position of the target sensors -----
    /**
     * @brief Interpolate the saved sensor data for a specified timestamp stamp
     *
     * @param timestamp timestamp in seconds since epoch
     * @return data structure that contains the sensor data interpolated for the given timestamp
     * stamp
     */
    datastructures::SensordataLocal get_sensor_data(double timestamp) const;

    bool valid() const override;

  public:
    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    // ----- file I/O -----
    static NavigationInterpolatorLocal from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NavigationInterpolatorLocal)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace navigation
} // namespace themachinethatgoesping
