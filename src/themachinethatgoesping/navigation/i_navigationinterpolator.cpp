// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "i_navigationinterpolator.hpp"

#include <stdexcept>
#include <fmt/format.h>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/linearinterpolator.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/slerpinterpolator.hpp>

namespace themachinethatgoesping {
namespace navigation {

// ----- constructor -----
I_NavigationInterpolator::I_NavigationInterpolator(SensorConfiguration sensor_configuration,
                                                   tools::vectorinterpolators::t_extr_mode extrapolation_mode)
    : _sensor_configuration(std::move(sensor_configuration))
{
    set_extrapolation_mode(extrapolation_mode);
}

// ----- merge data from another interpolator -----
void I_NavigationInterpolator::merge(const I_NavigationInterpolator& other)
{
    /* compare sensor operations, without targets */
    if (this->_sensor_configuration.without_targets() !=
        other._sensor_configuration.without_targets())
    {
        throw std::runtime_error(
            fmt::format("ERROR[{}]: Incompatible sensor configurations!", this->class_name()));
    }

    // check if sensor configuration can be merged
    if (!_sensor_configuration.can_merge_targets_with(other.get_sensor_configuration()))
    {
        throw std::runtime_error(
            fmt::format("ERROR[{}]: Incompatible target offsets!", this->class_name()));
    }

    // merge sensor configuration by adding targets
    _sensor_configuration.add_targets(other.get_sensor_configuration().get_targets());

    // merge data
    _interpolator_attitude.insert(other._interpolator_attitude.get_data_X(),
                                  other._interpolator_attitude.get_data_Y(),
                                  true);
    _interpolator_heading.insert(other._interpolator_heading.get_data_X(),
                                 other._interpolator_heading.get_data_Y(),
                                 true);
    _interpolator_heave.insert(
        other._interpolator_heave.get_data_X(), other._interpolator_heave.get_data_Y(), true);
    _interpolator_depth.insert(
        other._interpolator_depth.get_data_X(), other._interpolator_depth.get_data_Y(), true);
}

// ----- set extrapolation mode -----
void I_NavigationInterpolator::set_extrapolation_mode(tools::vectorinterpolators::t_extr_mode extrapolation_mode)
{
    _interpolator_attitude.set_extrapolation_mode(extrapolation_mode);
    _interpolator_heading.set_extrapolation_mode(extrapolation_mode);
    _interpolator_heave.set_extrapolation_mode(extrapolation_mode);
    _interpolator_depth.set_extrapolation_mode(extrapolation_mode);
}

// ----- operators -----
bool I_NavigationInterpolator::operator==(const I_NavigationInterpolator& other) const
{
    return _sensor_configuration == other._sensor_configuration &&
           _interpolator_attitude == other._interpolator_attitude &&
           _interpolator_heading == other._interpolator_heading &&
           _interpolator_heave == other._interpolator_heave &&
           _interpolator_depth == other._interpolator_depth;
}

bool I_NavigationInterpolator::operator!=(const I_NavigationInterpolator& other) const 
{ 
    return !(*this == other); 
}

// ----- set sensor data -----
void I_NavigationInterpolator::set_data_depth(const std::vector<double>& timestamp, const std::vector<float>& depth)
{
    _interpolator_depth.set_data_XY(timestamp, depth);
}

void I_NavigationInterpolator::set_data_heave(const std::vector<double>& timestamp, const std::vector<double>& heave)
{
    _interpolator_heave.set_data_XY(timestamp, heave);
}

void I_NavigationInterpolator::set_data_attitude(const std::vector<double>& timestamp,
                                                 const std::vector<float>& pitch,
                                                 const std::vector<float>& roll)
{
    std::vector<float> yaw(timestamp.size(), 0.0f);
    _interpolator_attitude.set_data_XYPR(timestamp, yaw, pitch, roll);
}

void I_NavigationInterpolator::set_data_heading(const std::vector<double>& timestamp, const std::vector<float>& heading)
{
    std::vector<float> pr(heading.size(), 0.0);
    _interpolator_heading.set_data_XYPR(timestamp, heading, pr, pr);
}

// ----- pass through functions -----
void I_NavigationInterpolator::add_target(const std::string& target_id,
                                          float             x,
                                          float             y,
                                          float             z,
                                          float             yaw,
                                          float             pitch,
                                          float             roll)
{
    _sensor_configuration.add_target(target_id, x, y, z, yaw, pitch, roll);
}

void I_NavigationInterpolator::add_target(const std::string&                       target_id,
                                          const datastructures::PositionalOffsets& target_offsets)
{
    _sensor_configuration.add_target(target_id, target_offsets);
}

void I_NavigationInterpolator::set_sensor_configuration(SensorConfiguration sensor_configuration)
{
    _sensor_configuration = std::move(sensor_configuration);
}

// ----- printer -----
tools::classhelper::ObjectPrinter I_NavigationInterpolator::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(this->class_name(), float_precision, superscript_exponents);

    printer.register_section("Sensor offset configuration", '*');
    printer.append(_sensor_configuration.__printer__(float_precision, superscript_exponents));

    printer.register_section("Attitude data", '*');
    printer.append(_interpolator_attitude.__printer__(float_precision, superscript_exponents), true);

    printer.register_section("Compass data", '*');
    printer.append(_interpolator_heading.__printer__(float_precision, superscript_exponents), true);

    printer.register_section("Heave data", '*');
    printer.append(_interpolator_heave.__printer__(float_precision, superscript_exponents), true);

    printer.register_section("Depth data", '*');
    printer.append(_interpolator_depth.__printer__(float_precision, superscript_exponents), true);

    return printer;
}

// ----- file I/O -----
I_NavigationInterpolator I_NavigationInterpolator::from_stream(std::istream& is)
{
    I_NavigationInterpolator interpolator(SensorConfiguration::from_stream(is));

    interpolator._interpolator_attitude = interpolator._interpolator_attitude.from_stream(is);
    interpolator._interpolator_heading  = interpolator._interpolator_heading.from_stream(is);
    interpolator._interpolator_heave    = interpolator._interpolator_heave.from_stream(is);
    interpolator._interpolator_depth    = interpolator._interpolator_depth.from_stream(is);

    return interpolator;
}

void I_NavigationInterpolator::to_stream(std::ostream& os) const
{
    _sensor_configuration.to_stream(os);
    _interpolator_attitude.to_stream(os);
    _interpolator_heading.to_stream(os);
    _interpolator_heave.to_stream(os);
    _interpolator_depth.to_stream(os);
}

bool I_NavigationInterpolator::valid() const
{
    // TODO: check which conditions are required for the interpolator to be valid
    return true;
}

} // namespace navigation
} // namespace themachinethatgoesping