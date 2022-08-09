// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "datastructures.hpp"
#include "sensorconfiguration.hpp"

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief The NavInterpolator class: Interpolate attitude information and transform the
 * values using the offsets specified in the sensor configuration class
 * This is an interface class that specifies attitude information but not the position
 */
class I_NavigationInterpolator
{
  protected:
    SensorConfiguration _sensor_configuration; ///< sensor configuration that stores the offsets

    // SlerpInterpolator that stores timestamp, roll, pitch, yaw -> Attitude of Vessel on the Water
    tools::vectorinterpolators::SlerpInterpolator _interpolator_attitude; ///< interpolator that stores attitude data (yaw, pitch and roll) yaw is only used if the compass data is NAN [°]
    tools::vectorinterpolators::SlerpInterpolator _interpolator_compass; ///< interpolator that stores compass data (yaw) [°]

    // LinearInterpolator for the depth in the world coordinate system
    tools::vectorinterpolators::AkimaInterpolator _interpolator_heave; ///< interpolator that stores heave data (relative change in depth, positive upwards) [m]
    tools::vectorinterpolators::AkimaInterpolator _interpolator_depth; ///< interpolator that stores depth data (depth, positive downwards) [m] 

  public:
    /**
     * @brief Construct a new i navigationinterpolator interface
     * 
     * @param extrapolation_mode extrapolate, fail or nearest
     */
    I_NavigationInterpolator(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                               tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        set_extrapolation_mode(extrapolation_mode);
    }
    virtual ~I_NavigationInterpolator() = default;

    // ----- set extrapolation mode -----
    /**
     * @brief Set the extrapolation mode for the attitude, compass, heave and depth interpolators
     * 
     * @param extrapolation_mode extrapolate, fail or nearest
     */
    virtual void set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                            tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        _interpolator_attitude.set_extrapolation_mode(extrapolation_mode);
        _interpolator_compass.set_extrapolation_mode(extrapolation_mode);

        _interpolator_heave.set_extrapolation_mode(extrapolation_mode);
        _interpolator_depth.set_extrapolation_mode(extrapolation_mode);
    }

    //----- operators -----
    bool operator==(const I_NavigationInterpolator& other) const
    {
        return _sensor_configuration == other._sensor_configuration &&
               _interpolator_attitude == other._interpolator_attitude &&
               _interpolator_compass == other._interpolator_compass &&
               _interpolator_heave == other._interpolator_heave &&
               _interpolator_depth == other._interpolator_depth;
    }
    bool operator!=(const I_NavigationInterpolator& other) const { return !(*this == other); }

    //----- set sensor data -----
    /**
     * @brief Set the depth data
     * 
     * @param timestamp in seconds since epoch
     * @param depth in meters, positive downwards
     */
    void set_data_depth(const std::vector<double>& timestamp, const std::vector<double>& depth)
    {
        _interpolator_depth.set_data_XY(timestamp, depth);
    }

    /**
     * @brief Set the depth data and specify the offsets of the depth sensor
     * 
     * @param timestamp in seconds since epoch
     * @param depth in meters, positive downwards
     * @param offset_x in meters, positive forwards
     * @param offset_y in meters, positive starboard
     * @param offset_z in meters, positive downwards
     */
    void set_data_depth(const std::vector<double>& timestamp,
                        const std::vector<double>& depth,
                        double                     offset_x,
                        double                     offset_y,
                        double                     offset_z)
    {
        _sensor_configuration.set_offsets_depth_sensor(offset_x, offset_y, offset_z);
        _interpolator_depth.set_data_XY(timestamp, depth);
    }

    
    /**
     * @brief Set the depth data and specify the offsets of the depth sensor
     * 
     * @param timestamp in seconds since epoch
     * @param depth in meters, positive downwards
     * @param sensor_offsets structure that contains the depth sensor offsets
     */
    void set_data_depth(const std::vector<double>&               timestamp,
                        const std::vector<double>&               depth,
                        const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_depth_sensor(sensor_offsets);
        _interpolator_depth.set_data_XY(timestamp, depth);
    }

    /**
     * @brief direct reference to the depth data interpolator
     * 
     * @return interpolator_depth& 
     */
    tools::vectorinterpolators::AkimaInterpolator& interpolator_depth()
    {
        return _interpolator_depth;
    }

    /**
     * @brief Set the heave data
     * 
     * @param timestamp in seconds since epoch
     * @param heave in meters, positive upwards
     */
    void set_data_heave(const std::vector<double>& timestamp, const std::vector<double>& heave)
    {
        _interpolator_heave.set_data_XY(timestamp, heave);
    }

    /**
     * @brief direct reference to the depth data interpolator
     * 
     * @return interpolator_depth& 
     */
    tools::vectorinterpolators::AkimaInterpolator& interpolator_heave()
    {
        return _interpolator_heave;
    }

    /**
     * @brief Set the attitude data
     * 
     * @param timestamp in seconds since epoch
     * @param yaw in °, positive clockwise (north is 0°)
     * @param pitch in °, positive is bow up
     * @param roll in °, positive is port up
     */
    void set_data_attitude_sensor(const std::vector<double>& timestamp,
                                const std::vector<double>& yaw,
                                const std::vector<double>& pitch,
                                const std::vector<double>& roll)
    {
        _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
    }
    
    /**
     * @brief Set the attitude data and additionally specify the offsets of the attitude sensor
     * 
     * @param timestamp in seconds since epoch
     * @param yaw in °, positive clockwise (north is 0°)
     * @param pitch in °, positive is bow up
     * @param roll in °, positive is port up
     * @param offset_yaw in °, positive clockwise
     * @param offset_pitch in °, positive is bow up
     * @param offset_roll in °, positive is port up
     */
    void set_data_attitude_sensor(const std::vector<double>& timestamp,
                                const std::vector<double>& yaw,
                                const std::vector<double>& pitch,
                                const std::vector<double>& roll,
                                double                     offset_yaw,
                                double                     offset_pitch,
                                double                     offset_roll)
    {
        _sensor_configuration.set_offsets_attitude_sensor(offset_yaw, offset_pitch, offset_roll);
        _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
    }

    
    /**
     * @brief Set the attitude data and additionally specify the offsets of the attitude sensor
     * 
     * @param timestamp in seconds since epoch
     * @param yaw in °, positive clockwise (north is 0°)
     * @param pitch in °, positive is bow up
     * @param roll in °, positive is port up
     * @param sensor_offsets structure that contains the attitude sensor offsets
     */
    void set_data_attitude_sensor(const std::vector<double>&               timestamp,
                                const std::vector<double>&               yaw,
                                const std::vector<double>&               pitch,
                                const std::vector<double>&               roll,
                                const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_attitude_sensor(sensor_offsets);
        _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
    }

    /**
     * @brief Set the attitude data (no yaw)
     * 
     * @param timestamp in seconds since epoch
     * @param pitch in °, positive is bow up
     * @param roll in °, positive is port up
     */
    void set_data_attitude_sensor(const std::vector<double>& timestamp,
                                const std::vector<double>& pitch,
                                const std::vector<double>& roll)
    {
        std::vector<double> yaw(pitch.size(), 0.0);
        _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
    }

    /**
     * @brief Set the attitude data (no yaw) and additionally specify the offsets of the attitude sensor
     * 
     * @param timestamp in seconds since epoch
     * @param pitch in °, positive is bow up
     * @param roll in °, positive is port up
     * @param offset_yaw in °, positive clockwise
     * @param offset_pitch in °, positive is bow up
     * @param offset_roll in °, positive is port up
     */
    void set_data_attitude_sensor(const std::vector<double>& timestamp,
                                const std::vector<double>& pitch,
                                const std::vector<double>& roll,
                                double                     offset_yaw,
                                double                     offset_pitch,
                                double                     offset_roll)
    {
        _sensor_configuration.set_offsets_attitude_sensor(offset_yaw, offset_pitch, offset_roll);
        std::vector<double> yaw(pitch.size(), 0.0);
        _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
    }

    /**
     * @brief Set the attitude data (no yaw) and additionally specify the offsets of the attitude sensor
     * 
     * @param timestamp in seconds since epoch
     * @param pitch in °, positive is bow up
     * @param roll in °, positive is port up
     * @param sensor_offsets structure that contains the attitude sensor offsets
     */
    void set_data_attitude_sensor(const std::vector<double>&               timestamp,
                                const std::vector<double>&               pitch,
                                const std::vector<double>&               roll,
                                const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_attitude_sensor(sensor_offsets);
        std::vector<double> yaw(pitch.size(), 0.0);
        _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
    }

    /**
     * @brief direct reference to the attitude data interpolator
     * 
     * @return interpolator_attitude& 
     */
    tools::vectorinterpolators::SlerpInterpolator& interpolator_attitude()
    {
        return _interpolator_attitude;
    }

    /**
     * @brief Set the compass data
     * 
     * @param timestamp in seconds since epoch
     * @param heading in °, positive clockwise (north is 0°)
     */
    void set_data_compass(const std::vector<double>& timestamp, const std::vector<double>& heading)
    {
        std::vector<double> pr(heading.size(), 0.0);
        _interpolator_compass.set_data_XYPR(timestamp, heading, pr, pr);
    }

    /**
     * @brief Set the compass data and additionally specify the offsets of the compass sensor
     * 
     * @param timestamp in seconds since epoch
     * @param heading in °, positive clockwise (north is 0°)
     * @param offset_heading in °, positive clockwise
     */
    void set_data_compass(const std::vector<double>& timestamp,
                          const std::vector<double>& heading,
                          double                     offset_heading)
    {
        std::vector<double> pr(heading.size(), 0.0);
        _sensor_configuration.set_offsets_compass(offset_heading);
        _interpolator_compass.set_data_XYPR(timestamp, heading, pr, pr);
    }

    /**
     * @brief Set the compass data and additionally specify the offsets of the compass sensor
     * 
     * @param timestamp in seconds since epoch
     * @param heading in °, positive clockwise (north is 0°)
     * @param sensor_offsets structure that contains the compass sensor offsets
     */
    void set_data_compass(const std::vector<double>&               timestamp,
                          const std::vector<double>&               heading,
                          const datastructures::PositionalOffsets& sensor_offsets)
    {
        std::vector<double> pr(heading.size(), 0.0);
        _sensor_configuration.set_offsets_compass(sensor_offsets);
        _interpolator_compass.set_data_XYPR(timestamp, heading, pr, pr);
    }

    /**
     * @brief direct reference to the compass data interpolator
     * 
     * @return interpolator_compass& 
     */
    tools::vectorinterpolators::SlerpInterpolator& interpolator_compass()
    {
        return _interpolator_compass;
    }

    //----- pass through functions -----
    /**
     * @brief add a target sensor with positional offsets
     * 
     * @param target_id name of the target sensor
     * @param x x position of the sensor in m, positive forward
     * @param y y position of the sensor in m, positive starboard
     * @param z z position of the sensor in m, positive down
     * @param yaw yaw angle of the sensor in °, positive clockwise
     * @param pitch pitch angle of the sensor in °, positive is bow up
     * @param roll roll angle of the sensor in °, positive is port up
     */
    void add_target(const std::string& target_id,
                    double             x,
                    double             y,
                    double             z,
                    double             yaw,
                    double             pitch,
                    double             roll)
    {
        _sensor_configuration.add_target(target_id, x, y, z, yaw, pitch, roll);
    }

    /**
     * @brief add a target sensor with positional offsets
     * 
     * @param target_id name of the target sensor
     * @param sensor_offsets structure that contains the sensor position
     */
    void add_target(const std::string&                       target_id,
                    const datastructures::PositionalOffsets& target_offsets)
    {
        _sensor_configuration.add_target(target_id, target_offsets);
    }

    //------------------------------------- set vessel functions ----------------------------------
    /**
     * @brief Set the sensor configuration which contains the position of all navigation sensors and target sensors
     * 
     * @param sensor_configuration sensor configuration for the navigation interpolation
     */
    void set_sensor_configuration(const SensorConfiguration& sensor_configuration)
    {
        _sensor_configuration = sensor_configuration;
    }

    /**
     * @brief direct reference to the sensor configuration
     * 
     * @return SensorConfiguration& 
     */
    SensorConfiguration& sensor_configuration() { return _sensor_configuration; }


  public:
    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("I_NavigationInterpolator", float_precision);

        printer.register_section("Sensor offset configuration", '*');
        printer.append(_sensor_configuration.__printer__(float_precision));

        printer.register_section("Attitude data", '*');
        printer.append(_interpolator_attitude.__printer__(float_precision), true);

        printer.register_section("Compass data", '*');
        printer.append(_interpolator_compass.__printer__(float_precision), true);

        printer.register_section("Heave data", '*');
        printer.append(_interpolator_heave.__printer__(float_precision), true);

        printer.register_section("Depth data", '*');
        printer.append(_interpolator_depth.__printer__(float_precision), true);

        return printer;
    }

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        // // data
        s.object(_sensor_configuration);
        s.object(_interpolator_attitude);
        s.object(_interpolator_compass);
        s.object(_interpolator_heave);
        s.object(_interpolator_depth);
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(I_NavigationInterpolator)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace navigation
} // namespace themachinethatgoesping
