// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolatorlatlon.hpp"

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;
using themachinethatgoesping::tools::vectorinterpolators::t_extr_mode;

void init_c_NavigationInterpolatorLatLon(py::module& m)
{
    py::class_<NavigationInterpolatorLatLon>(
        m,
        "NavigationInterpolatorLatLon",
        DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon))
        .def(py::init<t_extr_mode>(),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 NavigationInterpolatorLatLon),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("set_extrapolation_mode",
             &NavigationInterpolatorLatLon::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLatLon::compute_target_position),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 compute_target_position),
             py::arg("target_id"),
             py::arg("timestamp"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLatLon::compute_target_position),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 compute_target_position),
             py::arg("target_id"),
             py::arg("timestamp"))
        .def("get_sensor_data",
             py::overload_cast<double>(&NavigationInterpolatorLatLon::get_sensor_data),
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon, get_sensor_data),
             py::arg("timestamp"))
        .def_property(
            "sensor_configuration",
            &NavigationInterpolatorLatLon::sensor_configuration,
            &NavigationInterpolatorLatLon::set_sensor_configuration,
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, sensor_configuration))
        .def("add_target",
             py::overload_cast<const std::string&, double, double, double, double, double, double>(
                 &NavigationInterpolatorLatLon::add_target),
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
                 &NavigationInterpolatorLatLon::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target_2),
             py::arg("target_id"),
             py::arg("target_offsets"))
        .def("set_data_position_system",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_position_system),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_data_position_system),
             py::arg("timestamp"),
             py::arg("latitude"),
             py::arg("longitude"))
        .def("set_data_position_system",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               double,
                               double,
                               double>(&NavigationInterpolatorLatLon::set_data_position_system),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_data_position_system_2),
             py::arg("timestamp"),
             py::arg("latitude"),
             py::arg("longitude"),
             py::arg("offset_x"),
             py::arg("offset_y"),
             py::arg("offset_z"))
        .def("set_data_position_system",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLatLon::set_data_position_system),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_data_position_system_3),
             py::arg("timestamp"),
             py::arg("latitude"),
             py::arg("longitude"),
             py::arg("sensor_offsets"))

        // set heave data
        .def("set_data_heave",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_heave),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heave),
             py::arg("timestamp"),
             py::arg("heave"))

        // set depth data
        .def("set_data_depth",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth),
             py::arg("timestamp"),
             py::arg("depth"))
        .def("set_data_depth",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               double,
                               double,
                               double>(&NavigationInterpolatorLatLon::set_data_depth),
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
                 &NavigationInterpolatorLatLon::set_data_depth),
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
                 &NavigationInterpolatorLatLon::set_data_attitude_sensor),
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
                               double>(&NavigationInterpolatorLatLon::set_data_attitude_sensor),
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
                 &NavigationInterpolatorLatLon::set_data_attitude_sensor),
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
                 &NavigationInterpolatorLatLon::set_data_attitude_sensor),
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
                               double>(&NavigationInterpolatorLatLon::set_data_attitude_sensor),
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
                 &NavigationInterpolatorLatLon::set_data_attitude_sensor),
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
                 &NavigationInterpolatorLatLon::set_data_compass),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_compass),
             py::arg("timestamp"),
             py::arg("heading"))
        .def("set_data_compass",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&, double>(
                 &NavigationInterpolatorLatLon::set_data_compass),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_compass_2),
             py::arg("timestamp"),
             py::arg("heading"),
             py::arg("offset_heading"))
        .def("set_data_compass",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLatLon::set_data_compass),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_compass_3),
             py::arg("timestamp"),
             py::arg("heading"),
             py::arg("sensor_offsets"))

        // access interpolators
        // latitude / longitude
        .def_property(
            "interpolator_latitude",
            &NavigationInterpolatorLatLon::interpolator_latitude,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_latitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLatLon,
                interpolator_latitude))
        .def_property(
            "interpolator_longitude",
            &NavigationInterpolatorLatLon::interpolator_longitude,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_longitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLatLon,
                interpolator_longitude))

        // heave, depth, attitude, compass
        .def_property(
            "interpolator_heave",
            &NavigationInterpolatorLatLon::interpolator_heave,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_heave() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heave))
        .def_property(
            "interpolator_depth",
            &NavigationInterpolatorLatLon::interpolator_depth,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator&
                   interpolator) { self.interpolator_depth() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_depth))
        .def_property(
            "interpolator_attitude",
            &NavigationInterpolatorLatLon::interpolator_attitude,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator&
                   interpolator) { self.interpolator_attitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                I_NavigationInterpolator,
                interpolator_attitude))
        .def_property(
            "interpolator_compass",
            &NavigationInterpolatorLatLon::interpolator_compass,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator&
                   interpolator) { self.interpolator_compass() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                I_NavigationInterpolator,
                interpolator_compass))

        .def("__eq__",
             &NavigationInterpolatorLatLon::operator==,
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon, operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NavigationInterpolatorLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NavigationInterpolatorLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NavigationInterpolatorLatLon)
        // end NavigationInterpolatorLatLon
        ;
}
