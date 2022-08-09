// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <themachinethatgoesping/tools/classhelpers/bitsery.hpp>
#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "datastructures.hpp"
#include "i_navigationinterpolator.hpp"
#include "sensorconfiguration.hpp"

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief The NavInterpolator class: Interpolate navigation (lat/lon) values and attitude information and transform the
 * values using the offsets specified in the sensor configuration class
 */
class NavigationInterpolatorLatLon : public I_NavigationInterpolator
{

    // LinearInterpolator for the depth in the world coordinate system
    tools::vectorinterpolators::AkimaInterpolator _interpolator_latitude;
    tools::vectorinterpolators::AkimaInterpolator _interpolator_longitude;

  public:
    void set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                    tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        I_NavigationInterpolator::set_extrapolation_mode(extrapolation_mode);

        _interpolator_latitude.set_extrapolation_mode(extrapolation_mode);
        _interpolator_longitude.set_extrapolation_mode(extrapolation_mode);
    }

  public:
    NavigationInterpolatorLatLon(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                     tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        set_extrapolation_mode(extrapolation_mode);
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
    void set_data_position_system(const std::vector<double>& unixtime,
                                  const std::vector<double>& latitude,
                                  const std::vector<double>& longitude)
    {
        _interpolator_latitude.set_data_XY(unixtime, latitude);
        _interpolator_longitude.set_data_XY(unixtime, longitude);
    }

    void set_data_position_system(const std::vector<double>& unixtime,
                                  const std::vector<double>& latitude,
                                  const std::vector<double>& longitude,
                                  double                     offset_x,
                                  double                     offset_y,
                                  double                     offset_z)
    {
        _sensor_configuration.set_offsets_position_system(offset_x, offset_y, offset_z);
        set_data_position_system(unixtime, latitude, longitude);
    }
    void set_data_position_system(const std::vector<double>&               unixtime,
                                  const std::vector<double>&               latitude,
                                  const std::vector<double>&               longitude,
                                  const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_position_system(sensor_offsets);
        set_data_position_system(unixtime, latitude, longitude);
    }
    tools::vectorinterpolators::AkimaInterpolator& interpolator_latitude()
    {
        return _interpolator_latitude;
    }
    tools::vectorinterpolators::AkimaInterpolator& interpolator_longitude()
    {
        return _interpolator_longitude;
    }


    //------------------------------------- get vessel position -----------------------------------
    /**
     * @brief Compute the position of the target "target_id" based on the sensor data "sensor_data"
     *
     * @param target_id name of the target (e.g. "MBES")
     * @param sensor_data SensorData / this structure includes no coordinate information
     * @return datastructures::GeoLocationLocal  / this structure includes latitude and east, which
     * are set relative to the sensor coordinate system center
     */
    datastructures::GeoLocationLatLon compute_target_position(const std::string& target_id,
                                                             double             timestamp)
    {
        datastructures::SensorDataLatLon sensor_data;
        if (!_interpolator_depth.empty()) // default is 0.0
            sensor_data.gps_z = _interpolator_depth(timestamp);

        if (!_interpolator_heave.empty()) // default is 0.0
            sensor_data.heave_heave = _interpolator_heave(timestamp);

        if (!_interpolator_compass.empty()) // default is NAN (means will not be used)
            sensor_data.compass_heading = _interpolator_compass.ypr(timestamp)[0];

        if (!_interpolator_attitude.empty()) // default is 0.0. 0.0, 0.0
        {
            auto ypr              = _interpolator_attitude.ypr(timestamp);
            sensor_data.imu_yaw   = ypr[0];
            sensor_data.imu_pitch = ypr[1];
            sensor_data.imu_roll  = ypr[2];
        }

        sensor_data.gps_latitude  = _interpolator_latitude(timestamp);
        sensor_data.gps_longitude = _interpolator_longitude(timestamp);

        return _sensor_configuration.compute_target_position(target_id, sensor_data);
    }

  public:
    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NavigationInterpolatorLatLon", float_precision);

        printer.append(I_NavigationInterpolator::__printer__(float_precision));

        printer.register_section("Position system latitude", '*');
        printer.append(_interpolator_latitude.__printer__(float_precision), true);

        printer.register_section("Position system longitude", '*');
        printer.append(_interpolator_longitude.__printer__(float_precision), true);

        return printer;
    }

  private:

    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        // serialize base class
        s.ext(*this, bitsery::ext::BaseClass<I_NavigationInterpolator>{});

        // data
        s.object(_interpolator_latitude);
        s.object(_interpolator_longitude);
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NavigationInterpolatorLatLon)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace navigation
} // namespace themachinethatgoesping
