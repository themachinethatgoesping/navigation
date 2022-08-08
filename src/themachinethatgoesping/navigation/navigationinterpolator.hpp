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
    tools::vectorinterpolators::SlerpInterpolator _interpolator_ypr;
    tools::vectorinterpolators::SlerpInterpolator _interpolator_heading;

    // LinearInterpolator for the depth in the world koordinatesystem
    tools::vectorinterpolators::AkimaInterpolator _interpolator_heave;
    tools::vectorinterpolators::AkimaInterpolator _interpolator_depth;

  public:
    virtual void set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                            tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        _interpolator_ypr.set_extrapolation_mode(extrapolation_mode);
        _interpolator_heading.set_extrapolation_mode(extrapolation_mode);

        _interpolator_heave.set_extrapolation_mode(extrapolation_mode);
        _interpolator_depth.set_extrapolation_mode(extrapolation_mode);
    }

  public:
    NavigationInterpolator()
        : _interpolator_ypr()
        , _interpolator_heading()
        , _interpolator_heave()
        , _interpolator_depth()
    {
    }

    virtual ~NavigationInterpolator() = default;

    //------------------------------------- set vessel functions ----------------------------------
    void set_sensor_configuration(const SensorConfiguration& sensor_configuration)
    {
        _sensor_configuration = sensor_configuration;
    }

    SensorConfiguration get_sensor_configuration() const { return _sensor_configuration; }

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
        sensor_data.compass_heading = _interpolator_heading.ypr(timestamp)[0];

        auto ypr              = _interpolator_ypr.ypr(timestamp);
        sensor_data.imu_yaw   = ypr[0];
        sensor_data.imu_pitch = ypr[1];
        sensor_data.imu_roll  = ypr[2];

        return _sensor_configuration.compute_target_position(target_id, sensor_data);
    }
};

} // namespace navigation
} // namespace themachinethatgoesping
