// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/sensorconfiguration.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;

void init_c_sensorconfiguration(py::module& m)
{
    py::class_<SensorConfiguration>(
        m, "SensorConfiguration", DOC(themachinethatgoesping, navigation, SensorConfiguration))
        .def(py::init<>(),
             DOC(themachinethatgoesping, navigation, SensorConfiguration, SensorConfiguration))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const datastructures::SensorDataLatLon&>(
                 &SensorConfiguration::compute_target_position, py::const_),
             DOC(themachinethatgoesping, navigation, SensorConfiguration, compute_target_position),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def(
            "compute_target_position",
            py::overload_cast<const std::string&, const datastructures::SensorDataUTM&>(
                &SensorConfiguration::compute_target_position, py::const_),
            DOC(themachinethatgoesping, navigation, SensorConfiguration, compute_target_position_2),
            py::arg("target_id"),
            py::arg("sensor_data"))
        .def(
            "compute_target_position",
            py::overload_cast<const std::string&, const datastructures::SensorDataLocal&>(
                &SensorConfiguration::compute_target_position, py::const_),
            DOC(themachinethatgoesping, navigation, SensorConfiguration, compute_target_position_3),
            py::arg("target_id"),
            py::arg("sensor_data"))
        .def(
            "compute_target_position",
            py::overload_cast<const std::string&, const datastructures::SensorData&>(
                &SensorConfiguration::compute_target_position, py::const_),
            DOC(themachinethatgoesping, navigation, SensorConfiguration, compute_target_position_4),
            py::arg("target_id"),
            py::arg("sensor_data"))
        .def("add_target",
             py::overload_cast<const std::string&, double, double, double, double, double, double>(
                 &SensorConfiguration::add_target),
             DOC(themachinethatgoesping, navigation, SensorConfiguration, add_target),
             py::arg("target_id"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("add_target",
             py::overload_cast<const std::string&, const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::add_target),
             DOC(themachinethatgoesping, navigation, SensorConfiguration, add_target_2),
             py::arg("target_id"),
             py::arg("target_offsets"))
        .def("get_target",
             &SensorConfiguration::get_target,
             DOC(themachinethatgoesping, navigation, SensorConfiguration, get_target),
             py::arg("target_id"))
        .def("get_target_ids",
             &SensorConfiguration::get_target_ids,
             DOC(themachinethatgoesping, navigation, SensorConfiguration, get_target_ids))
        .def("set_attitude_source",
             py::overload_cast<std::string_view, double, double, double>(
                 &SensorConfiguration::set_attitude_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_attitude_source),
             py::arg("name"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("set_attitude_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_attitude_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_attitude_source_2),
             py::arg("sensor_offsets"))
        .def("get_attitude_source",
             &SensorConfiguration::get_attitude_source,
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 get_attitude_source))
        .def("set_heading_source",
             py::overload_cast<std::string_view, double>(&SensorConfiguration::set_heading_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_heading_source),
             py::arg("name"),
             py::arg("yaw"))
        .def("set_heading_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_heading_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_heading_source_2),
             py::arg("sensor_offsets"))
        .def("get_heading_source",
             &SensorConfiguration::get_heading_source,
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 get_heading_source))
        .def("set_depth_source",
             py::overload_cast<std::string_view, double, double, double>(
                 &SensorConfiguration::set_depth_source),
             DOC(themachinethatgoesping, navigation, SensorConfiguration, set_depth_source),
             py::arg("name"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"))
        .def("set_depth_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_depth_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_depth_source_2),
             py::arg("sensor_offsets"))
        .def("get_depth_source",
             &SensorConfiguration::get_depth_source,
             DOC(themachinethatgoesping, navigation, SensorConfiguration, get_depth_source))
        .def("set_position_source",
             py::overload_cast<std::string_view, double, double, double>(
                 &SensorConfiguration::set_position_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_position_source),
             py::arg("name"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"))
        .def("set_position_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_position_source),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 set_position_source_2),
             py::arg("sensor_offsets"))
        .def("get_position_source",
             &SensorConfiguration::get_position_source,
             DOC(themachinethatgoesping,
                 navigation,
                 SensorConfiguration,
                 get_position_source))
        .def("__eq__",
             &SensorConfiguration::operator==,
             DOC(themachinethatgoesping, navigation, SensorConfiguration, operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorConfiguration)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorConfiguration)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorConfiguration)
        // end SensorConfiguration
        ;
}
