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
 * @brief The NavInterpolator class: Interpolate navigation and motion information and transform the
 * values using the vessel class
 */
class NavigationInterpolator
{
    SensorConfiguration _sensor_configuration;

    // SlerpInterpolator that stores unixtime, roll, pitch, yaw -> Motion of Vessel on the Water
    tools::vectorinterpolators::SlerpInterpolator _interpolator_motion;
    tools::vectorinterpolators::SlerpInterpolator _interpolator_compass;

    // LinearInterpolator for the depth in the world koordinatesystem
    tools::vectorinterpolators::AkimaInterpolator _interpolator_heave;
    tools::vectorinterpolators::AkimaInterpolator _interpolator_depth;

  public:
    virtual void set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                            tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        _interpolator_motion.set_extrapolation_mode(extrapolation_mode);
        _interpolator_compass.set_extrapolation_mode(extrapolation_mode);

        _interpolator_heave.set_extrapolation_mode(extrapolation_mode);
        _interpolator_depth.set_extrapolation_mode(extrapolation_mode);
    }

  public:
    NavigationInterpolator()          = default;
    virtual ~NavigationInterpolator() = default;

    //----- set sensor data -----
    void set_data_depth(const std::vector<double>& unixtime, const std::vector<double>& depth)
    {
        _interpolator_depth.set_data_XY(unixtime, depth);
    }
    void set_data_depth(const std::vector<double>& unixtime,
                        const std::vector<double>& depth,
                        double                     offset_x,
                        double                     offset_y,
                        double                     offset_z)
    {
        _sensor_configuration.set_offsets_depth_sensor(offset_x, offset_y, offset_z);
        _interpolator_depth.set_data_XY(unixtime, depth);
    }
    void set_data_depth(const std::vector<double>&               unixtime,
                        const std::vector<double>&               depth,
                        const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_depth_sensor(sensor_offsets);
        _interpolator_depth.set_data_XY(unixtime, depth);
    }
    tools::vectorinterpolators::AkimaInterpolator& interpolator_depth()
    {
        return _interpolator_depth;
    }

    void set_data_heave(const std::vector<double>& unixtime, const std::vector<double>& heave)
    {
        _interpolator_heave.set_data_XY(unixtime, heave);
    }
    tools::vectorinterpolators::AkimaInterpolator& interpolator_heave()
    {
        return _interpolator_heave;
    }

    void set_data_motion_sensor(const std::vector<double>& unixtime,
                      const std::vector<double>& yaw,
                      const std::vector<double>& pitch,
                      const std::vector<double>& roll)
    {
        _interpolator_motion.set_data_XYPR(unixtime, yaw, pitch, roll);
    }
    void set_data_motion_sensor(const std::vector<double>& unixtime,
                      const std::vector<double>& yaw,
                      const std::vector<double>& pitch,
                      const std::vector<double>& roll,
                      double                     offset_yaw,
                      double                     offset_pitch,
                      double                     offset_roll)
    {
        _sensor_configuration.set_offsets_motion_sensor(offset_yaw, offset_pitch, offset_roll);
        _interpolator_motion.set_data_XYPR(unixtime, yaw, pitch, roll);
    }
    void set_data_motion_sensor(const std::vector<double>&               unixtime,
                      const std::vector<double>&               yaw,
                      const std::vector<double>&               pitch,
                      const std::vector<double>&               roll,
                      const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_motion_sensor(sensor_offsets);
        _interpolator_motion.set_data_XYPR(unixtime, yaw, pitch, roll);
    }
    void set_data_motion_sensor(const std::vector<double>& unixtime,
                     const std::vector<double>& pitch,
                     const std::vector<double>& roll)
    {
        std::vector<double> yaw(pitch.size(), 0.0);
        _interpolator_motion.set_data_XYPR(unixtime, yaw, pitch, roll);
    }
    void set_data_motion_sensor(const std::vector<double>& unixtime,
                     const std::vector<double>& pitch,
                     const std::vector<double>& roll,
                     double                     offset_yaw,
                     double                     offset_pitch,
                     double                     offset_roll)
    {
        _sensor_configuration.set_offsets_motion_sensor(offset_yaw, offset_pitch, offset_roll);
        std::vector<double> yaw(pitch.size(), 0.0);
        _interpolator_motion.set_data_XYPR(unixtime, yaw, pitch, roll);
    }
    void set_data_motion_sensor(const std::vector<double>&               unixtime,
                     const std::vector<double>&               pitch,
                     const std::vector<double>&               roll,
                     const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_motion_sensor(sensor_offsets);
        std::vector<double> yaw(pitch.size(), 0.0);
        _interpolator_motion.set_data_XYPR(unixtime, yaw, pitch, roll);
    }
    tools::vectorinterpolators::SlerpInterpolator& interpolator_motion() { return _interpolator_motion; }

    void set_data_compass(const std::vector<double>& unixtime, const std::vector<double>& heading)
    {
        std::vector<double> pr(heading.size(), 0.0);
        _interpolator_compass.set_data_XYPR(unixtime, heading, pr, pr);
    }
    void set_data_compass(const std::vector<double>& unixtime,
                          const std::vector<double>& heading,
                          double                     offset_heading)
    {
        std::vector<double> pr(heading.size(), 0.0);
        _sensor_configuration.set_offsets_compass(offset_heading);
        _interpolator_compass.set_data_XYPR(unixtime, heading, pr, pr);
    }
    void set_data_compass(const std::vector<double>&               unixtime,
                          const std::vector<double>&               heading,
                          const datastructures::PositionalOffsets& sensor_offsets)
    {
        std::vector<double> pr(heading.size(), 0.0);
        _sensor_configuration.set_offsets_compass(sensor_offsets);
        _interpolator_compass.set_data_XYPR(unixtime, heading, pr, pr);
    }
    tools::vectorinterpolators::SlerpInterpolator& interpolator_compass()
    {
        return _interpolator_compass;
    }

    //----- pass through functions -----
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

    void add_target(const std::string&                       target_id,
                    const datastructures::PositionalOffsets& target_offsets)
    {
        _sensor_configuration.add_target(target_id, target_offsets);
    }

    //------------------------------------- set vessel functions ----------------------------------
    void set_sensor_configuration(const SensorConfiguration& sensor_configuration)
    {
        _sensor_configuration = sensor_configuration;
    }

    SensorConfiguration& sensor_configuration() { return _sensor_configuration; }

    //------------------------------------- get vessel position -----------------------------------
    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorData / this structure includes no coordinate information
     * @return datastructures::GeoLocationLocal  / this structure includes northing and east, which
     * are set relative to the sensor coordinate system center
     */
    datastructures::GeoLocationLocal compute_target_position(const std::string& target_id,
                                                             double             timestamp)
    {
        datastructures::SensorData sensor_data;
        sensor_data.gps_z           = _interpolator_depth(timestamp);
        sensor_data.heave_heave     = _interpolator_heave(timestamp);
        sensor_data.compass_heading = _interpolator_compass.ypr(timestamp)[0];

        auto ypr              = _interpolator_motion.ypr(timestamp);
        sensor_data.imu_yaw   = ypr[0];
        sensor_data.imu_pitch = ypr[1];
        sensor_data.imu_roll  = ypr[2];

        return _sensor_configuration.compute_target_position(target_id, sensor_data);
    }
};

} // namespace navigation
} // namespace themachinethatgoesping
