// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolatorlocal.hpp"

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;
using themachinethatgoesping::tools::vectorinterpolators::t_extr_mode;

void init_c_NavigationInterpolatorLocal(py::module& m)
{
    py::class_<NavigationInterpolatorLocal>(
        m,
        "NavigationInterpolatorLocal",
        DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal))
        .def(py::init<t_extr_mode>(),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 NavigationInterpolatorLocal),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("set_extrapolation_mode",
             &NavigationInterpolatorLocal::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLocal::compute_target_position),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 compute_target_position),
             py::arg("target_id"),
             py::arg("timestamp"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLocal::compute_target_position),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 compute_target_position),
             py::arg("target_id"),
             py::arg("timestamp"))
        .def("get_sensor_data",
             py::overload_cast<double>(&NavigationInterpolatorLocal::get_sensor_data),
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal, get_sensor_data),
             py::arg("timestamp"))
        .def_property(
            "sensor_configuration",
            &NavigationInterpolatorLocal::sensor_configuration,
            &NavigationInterpolatorLocal::set_sensor_configuration,
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, sensor_configuration))
        .def("add_target",
             py::overload_cast<const std::string&, double, double, double, double, double, double>(
                 &NavigationInterpolatorLocal::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target),
             py::arg("target_id"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("add_target",
             py::overload_cast<const std::string&, const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLocal::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target_2),
             py::arg("target_id"),
             py::arg("target_offsets"))
        .def("set_data_position_system",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_position_system),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 set_data_position_system),
             py::arg("timestamp"),
             py::arg("northing"),
             py::arg("easting"))
        .def("set_data_position_system",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               double,
                               double,
                               double>(&NavigationInterpolatorLocal::set_data_position_system),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 set_data_position_system_2),
             py::arg("timestamp"),
             py::arg("northing"),
             py::arg("easting"),
             py::arg("offset_x"),
             py::arg("offset_y"),
             py::arg("offset_z"))
        .def("set_data_position_system",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLocal::set_data_position_system),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 set_data_position_system_3),
             py::arg("timestamp"),
             py::arg("northing"),
             py::arg("easting"),
             py::arg("sensor_offsets"))

        // set heave data
        .def("set_data_heave",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_heave),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heave),
             py::arg("timestamp"),
             py::arg("heave"))

        // set depth data
        .def("set_data_depth",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth),
             py::arg("timestamp"),
             py::arg("depth"))
        .def("set_data_depth",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               double,
                               double,
                               double>(&NavigationInterpolatorLocal::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth_2),
             py::arg("timestamp"),
             py::arg("depth"),
             py::arg("offset_x"),
             py::arg("offset_y"),
             py::arg("offset_z"))
        .def("set_data_depth",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLocal::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth_3),
             py::arg("timestamp"),
             py::arg("depth"),
             py::arg("sensor_offsets"))

        // set attitude data
        .def("set_data_attitude_sensor",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_attitude_sensor),
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_data_attitude_sensor),
             py::arg("timestamp"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("set_data_attitude_sensor",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               double,
                               double,
                               double>(&NavigationInterpolatorLocal::set_data_attitude_sensor),
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_data_attitude_sensor_2),
             py::arg("timestamp"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"),
             py::arg("offset_yaw"),
             py::arg("offset_pitch"),
             py::arg("offset_roll"))
        .def("set_data_attitude_sensor",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLocal::set_data_attitude_sensor),
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_data_attitude_sensor_3),
             py::arg("timestamp"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"),
             py::arg("sensor_offsets"))

        // set attitude data (no yaw)
        .def("set_data_attitude_sensor",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_attitude_sensor),
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_data_attitude_sensor_4),
             py::arg("timestamp"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("set_data_attitude_sensor",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               double,
                               double,
                               double>(&NavigationInterpolatorLocal::set_data_attitude_sensor),
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_data_attitude_sensor_5),
             py::arg("timestamp"),
             py::arg("pitch"),
             py::arg("roll"),
             py::arg("offset_yaw"),
             py::arg("offset_pitch"),
             py::arg("offset_roll"))
        .def("set_data_attitude_sensor",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLocal::set_data_attitude_sensor),
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_data_attitude_sensor_6),
             py::arg("timestamp"),
             py::arg("pitch"),
             py::arg("roll"),
             py::arg("sensor_offsets"))

        // set data compass
        .def("set_data_compass",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_compass),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_compass),
             py::arg("timestamp"),
             py::arg("heading"))
        .def("set_data_compass",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&, double>(
                 &NavigationInterpolatorLocal::set_data_compass),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_compass_2),
             py::arg("timestamp"),
             py::arg("heading"),
             py::arg("offset_heading"))
        .def("set_data_compass",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLocal::set_data_compass),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_compass_3),
             py::arg("timestamp"),
             py::arg("heading"),
             py::arg("sensor_offsets"))

        // access interpolators
        // northing / easting
        .def_property(
            "interpolator_northing",
            &NavigationInterpolatorLocal::interpolator_northing,
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_northing() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLocal,
                interpolator_northing))
        .def_property(
            "interpolator_easting",
            &NavigationInterpolatorLocal::interpolator_easting,
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_easting() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLocal,
                interpolator_easting))

        // heave, depth, attitude, compass
        .def_property(
            "interpolator_heave",
            &NavigationInterpolatorLocal::interpolator_heave,
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_heave() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heave))
        .def_property(
            "interpolator_depth",
            &NavigationInterpolatorLocal::interpolator_depth,
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_depth() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_depth))
        .def_property(
            "interpolator_attitude",
            &NavigationInterpolatorLocal::interpolator_attitude,
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator&
                   interpolator) { self.interpolator_attitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                I_NavigationInterpolator,
                interpolator_attitude))
        .def_property(
            "interpolator_compass",
            &NavigationInterpolatorLocal::interpolator_compass,
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator&
                   interpolator) { self.interpolator_compass() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_compass))

        .def("__eq__",
             &NavigationInterpolatorLocal::operator==,
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal, operator_eq),
             py::arg("other"))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NavigationInterpolatorLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NavigationInterpolatorLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NavigationInterpolatorLocal)
        // end NavigationInterpolatorLocal
        ;
}
