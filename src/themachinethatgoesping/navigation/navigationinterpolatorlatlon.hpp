// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/navigationinterpolatorlatlon.doc.hpp"

#include <themachinethatgoesping/tools/classhelper/classversion.hpp>
#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>


#include "datastructures.hpp"
#include "i_navigationinterpolator.hpp"
#include "sensorconfiguration.hpp"

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
                                    tools::vectorinterpolators::t_extr_mode::extrapolate) override
    {
        I_NavigationInterpolator::set_extrapolation_mode(extrapolation_mode);

        _interpolator_latitude.set_extrapolation_mode(extrapolation_mode);
        _interpolator_longitude.set_extrapolation_mode(extrapolation_mode);
    }

  public:
    /**
     * @brief Construct a new i navigationinterpolator interface
     *
     * @param sensor_configuration sensor configuration used for this navigation interpolator
     * @param extrapolation_mode extrapolate, fail or nearest
     */

    NavigationInterpolatorLatLon(SensorConfiguration sensor_configuration = SensorConfiguration(),
                                 tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                     tools::vectorinterpolators::t_extr_mode::extrapolate)
        : I_NavigationInterpolator(std::move(sensor_configuration), extrapolation_mode)
    {
        set_extrapolation_mode(extrapolation_mode);
    }

    /**
     * @brief Construct a new Navigation Interpolator Lat Lon object from a base Interpolator
     *
     * @param base Base I_NavigationInterpolator object
     */
    explicit NavigationInterpolatorLatLon(I_NavigationInterpolator base)
        : I_NavigationInterpolator(std::move(base))
    {
        set_extrapolation_mode(base.interpolator_depth().get_extrapolation_mode());
    }

    virtual ~NavigationInterpolatorLatLon() = default;

    //----- operators -----
    bool operator==(const NavigationInterpolatorLatLon& other) const
    {

        return _interpolator_latitude == other._interpolator_latitude &&
               _interpolator_longitude == other._interpolator_longitude &&
               I_NavigationInterpolator::operator==(other);
    }
    bool operator!=(const NavigationInterpolatorLatLon& other) const { return !(*this == other); }

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
                           const std::vector<double>& longitude)
    {
        _interpolator_latitude.set_data_XY(timestamp, latitude);
        _interpolator_longitude.set_data_XY(timestamp, longitude);
    }

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
    void merge(const NavigationInterpolatorLatLon& other)
    {
        I_NavigationInterpolator::merge(other);

        // merge data
        _interpolator_latitude.insert(other._interpolator_latitude.get_data_X(),
                                      other._interpolator_latitude.get_data_Y(),
                                      true);
        _interpolator_longitude.insert(other._interpolator_longitude.get_data_X(),
                                       other._interpolator_longitude.get_data_Y(),
                                       true);
    }

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
                                                 double             timestamp) const
    {
        return _sensor_configuration.compute_target_position(target_id, get_sensor_data(timestamp));
    }

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
                                                              double             timestamp) const
    {
        return _sensor_configuration.compute_target_position(target_id, get_sensor_data(timestamp));
    }

    //----- compute the position of the target sensors -----
    /**
     * @brief Interpolate the saved sensor data for a specified timestamp stamp
     *
     * @param timestamp timestamp in seconds since epoch
     * @return data structure that contains the sensor data interpolated for the given timestamp
     * stamp
     */
    datastructures::SensordataLatLon get_sensor_data(double timestamp) const
    {
        datastructures::SensordataLatLon sensor_data;
        if (!_interpolator_depth.empty()) // default is 0.0
            sensor_data.depth = _interpolator_depth(timestamp);

        if (!_interpolator_heave.empty()) // default is 0.0
            sensor_data.heave = _interpolator_heave(timestamp);

        if (!_interpolator_heading.empty()) // default is 0.0
            sensor_data.heading = _interpolator_heading.ypr(timestamp)[0];

        if (!_interpolator_attitude.empty()) // default is 0.0. 0.0
        {
            auto ypr = _interpolator_attitude.ypr(timestamp);
            // sensor_data.imu_yaw   = ypr[0];
            sensor_data.pitch = ypr[1];
            sensor_data.roll  = ypr[2];
        }

        if (_interpolator_latitude.empty())
            throw std::runtime_error("ERROR[datastructures::SensordataLatLon]: No latitude data "
                                     "available for interpolation");

        if (_interpolator_longitude.empty())
            throw std::runtime_error("ERROR[datastructures::SensordataLatLon]: No longitude data "
                                     "available for interpolation");

        sensor_data.latitude  = _interpolator_latitude(timestamp);
        sensor_data.longitude = _interpolator_longitude(timestamp);

        return sensor_data;
    }

    bool valid() const override
    {
        return I_NavigationInterpolator::valid() &&
               (!_interpolator_latitude.empty() && !_interpolator_longitude.empty());
    }

  public:
    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer(
            this->class_name(), float_precision, superscript_exponents);

        printer.append(
            I_NavigationInterpolator::__printer__(float_precision, superscript_exponents));

        printer.register_section("Position system latitude", '*');
        printer.append(_interpolator_latitude.__printer__(float_precision, superscript_exponents),
                       true);

        printer.register_section("Position system longitude", '*');
        printer.append(_interpolator_longitude.__printer__(float_precision, superscript_exponents),
                       true);

        return printer;
    }

    // ----- file I/O -----
    static NavigationInterpolatorLatLon from_stream(std::istream& is)
    {
        tools::classhelper::read_version(is, "NavIntLatLon_V1", "NavigationInterpolatorLatLon");
        NavigationInterpolatorLatLon interpolator(I_NavigationInterpolator::from_stream(is));

        interpolator._interpolator_latitude  = interpolator._interpolator_latitude.from_stream(is);
        interpolator._interpolator_longitude = interpolator._interpolator_longitude.from_stream(is);

        return interpolator;
    }

    void to_stream(std::ostream& os) const
    {
        tools::classhelper::write_version(os, "NavIntLatLon_V1");
        I_NavigationInterpolator::to_stream(os);

        _interpolator_latitude.to_stream(os);
        _interpolator_longitude.to_stream(os);
    }

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
inline std::size_t hash_value(
    const themachinethatgoesping::navigation::NavigationInterpolatorLatLon& object)
{
    return object.binary_hash();
}

} // namespace navigation
} // namespace themachinethatgoesping

template<>
struct std::hash<themachinethatgoesping::navigation::NavigationInterpolatorLatLon>
{
    std::size_t operator()(
        const themachinethatgoesping::navigation::NavigationInterpolatorLatLon& object) const
    {
        return object.binary_hash();
    }
};


// IGNORE_DOC:__doc_themachinethatgoesping_navigation_hash_value
// IGNORE_DOC:__doc_hash_operator_call
// IGNORE_DOC:__doc_hash