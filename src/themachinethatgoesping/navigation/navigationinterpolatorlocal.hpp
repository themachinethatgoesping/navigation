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
 * @brief The NavInterpolator class: Interpolate navigation and attitude information and transform the
 * values using the vessel class
 */
class NavigationInterpolatorLocal : public I_NavigationInterpolator
{

    // LinearInterpolator for the depth in the world coordinate system
    tools::vectorinterpolators::AkimaInterpolator _interpolator_northing;
    tools::vectorinterpolators::AkimaInterpolator _interpolator_easting;

  public:
    void set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                    tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        I_NavigationInterpolator::set_extrapolation_mode(extrapolation_mode);

        _interpolator_northing.set_extrapolation_mode(extrapolation_mode);
        _interpolator_easting.set_extrapolation_mode(extrapolation_mode);
    }

  public:
    NavigationInterpolatorLocal(tools::vectorinterpolators::t_extr_mode extrapolation_mode =
                                    tools::vectorinterpolators::t_extr_mode::extrapolate)
    {
        set_extrapolation_mode(extrapolation_mode);
    }
    virtual ~NavigationInterpolatorLocal() = default;

    //----- operators -----
    bool operator==(const NavigationInterpolatorLocal& other) const
    {

        return _interpolator_northing == other._interpolator_northing &&
               _interpolator_easting == other._interpolator_easting &&
               I_NavigationInterpolator::operator==(other);
    }
    bool operator!=(const NavigationInterpolatorLocal& other) const { return !(*this == other); }

    //----- set sensor data -----
    void set_data_position_system(const std::vector<double>& unixtime,
                                  const std::vector<double>& northing,
                                  const std::vector<double>& easting)
    {
        _interpolator_northing.set_data_XY(unixtime, northing);
        _interpolator_easting.set_data_XY(unixtime, easting);
    }

    void set_data_position_system(const std::vector<double>& unixtime,
                                  const std::vector<double>& northing,
                                  const std::vector<double>& easting,
                                  double                     offset_x,
                                  double                     offset_y,
                                  double                     offset_z)
    {
        _sensor_configuration.set_offsets_position_system(offset_x, offset_y, offset_z);
        _interpolator_northing.set_data_XY(unixtime, northing);
        _interpolator_easting.set_data_XY(unixtime, easting);
    }
    void set_data_position_system(const std::vector<double>&               unixtime,
                                  const std::vector<double>&               northing,
                                  const std::vector<double>&               easting,
                                  const datastructures::PositionalOffsets& sensor_offsets)
    {
        _sensor_configuration.set_offsets_position_system(sensor_offsets);
        _interpolator_northing.set_data_XY(unixtime, northing);
        _interpolator_easting.set_data_XY(unixtime, easting);
    }
    tools::vectorinterpolators::AkimaInterpolator& interpolator_northing()
    {
        return _interpolator_northing;
    }
    tools::vectorinterpolators::AkimaInterpolator& interpolator_easting()
    {
        return _interpolator_easting;
    }

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
        datastructures::SensorDataLocal sensor_data;
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

        sensor_data.gps_northing = _interpolator_northing(timestamp);
        sensor_data.gps_easting  = _interpolator_easting(timestamp);

        return _sensor_configuration.compute_target_position(target_id, sensor_data);
    }

  public:
    // __printer__ function is necessary to support print() info_string() etc (defined by
    // __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__ macro below)
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NavigationInterpolatorLocal", float_precision);

        printer.append(I_NavigationInterpolator::__printer__(float_precision));

        printer.register_section("Position system northing", '*');
        printer.append(_interpolator_northing.__printer__(float_precision), true);

        printer.register_section("Position system easting", '*');
        printer.append(_interpolator_easting.__printer__(float_precision), true);

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
        s.object(_interpolator_northing);
        s.object(_interpolator_easting);
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs the serialize function)
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NavigationInterpolatorLocal)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace navigation
} // namespace themachinethatgoesping
