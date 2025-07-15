// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/sensorconfiguration.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;

#define DOC_SensorConfiguration(ARG)                                                               \
    DOC(themachinethatgoesping, navigation, SensorConfiguration, ARG)

void init_c_sensorconfiguration(py::module& m)
{
    py::class_<SensorConfiguration>(
        m, "SensorConfiguration", DOC(themachinethatgoesping, navigation, SensorConfiguration))
        .def(py::init<std::string_view>(),
             DOC_SensorConfiguration(SensorConfiguration),
             py::arg("default_sensor_name") = "zero-referenced")
        .def("without_targets",
             &SensorConfiguration::without_targets,
             DOC_SensorConfiguration(without_targets))
        .def("can_merge_targets_with",
             &SensorConfiguration::can_merge_targets_with,
             DOC_SensorConfiguration(can_merge_targets_with),
             py::arg("other"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const datastructures::SensordataLatLon&>(
                 &SensorConfiguration::compute_target_position, py::const_),
             DOC_SensorConfiguration(compute_target_position),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const datastructures::SensordataUTM&>(
                 &SensorConfiguration::compute_target_position, py::const_),
             DOC_SensorConfiguration(compute_target_position_2),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const datastructures::SensordataLocal&>(
                 &SensorConfiguration::compute_target_position, py::const_),
             DOC_SensorConfiguration(compute_target_position_3),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const datastructures::Sensordata&>(
                 &SensorConfiguration::compute_target_position, py::const_),
             DOC_SensorConfiguration(compute_target_position_4),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("has_target",
             &SensorConfiguration::has_target,
             DOC_SensorConfiguration(has_target),
             py::arg("target_id"))
        .def("add_target",
             py::overload_cast<const std::string&, float, float, float, float, float, float>(
                 &SensorConfiguration::add_target),
             DOC_SensorConfiguration(add_target),
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
             DOC_SensorConfiguration(add_target_2),
             py::arg("target_id"),
             py::arg("target_offsets"))
        .def("add_targets",
             &SensorConfiguration::add_targets,
             DOC_SensorConfiguration(add_targets),
             py::arg("targets"))
        .def("get_target",
             &SensorConfiguration::get_target,
             DOC_SensorConfiguration(get_target),
             py::arg("target_id"))
        .def("get_targets", &SensorConfiguration::get_targets, DOC_SensorConfiguration(get_targets))
        .def("remove_target",
             &SensorConfiguration::remove_target,
             DOC_SensorConfiguration(remove_target),
             py::arg("target_id"))
        .def("remove_targets",
             &SensorConfiguration::remove_targets,
             DOC_SensorConfiguration(remove_targets))
        .def("get_target_ids",
             &SensorConfiguration::get_target_ids,
             DOC_SensorConfiguration(get_target_ids))
        .def("set_attitude_source",
             py::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_attitude_source),
             DOC_SensorConfiguration(set_attitude_source),
             py::arg("name"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("set_attitude_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_attitude_source),
             DOC_SensorConfiguration(set_attitude_source_2),
             py::arg("sensor_offsets"))
        .def("get_attitude_source",
             &SensorConfiguration::get_attitude_source,
             DOC_SensorConfiguration(get_attitude_source))
        .def("set_heading_source",
             py::overload_cast<std::string_view, float>(&SensorConfiguration::set_heading_source),
             DOC_SensorConfiguration(set_heading_source),
             py::arg("name"),
             py::arg("yaw"))
        .def("set_heading_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_heading_source),
             DOC_SensorConfiguration(set_heading_source_2),
             py::arg("sensor_offsets"))
        .def("get_heading_source",
             &SensorConfiguration::get_heading_source,
             DOC_SensorConfiguration(get_heading_source))
        .def("set_waterline_offset",
             py::overload_cast<float>(&SensorConfiguration::set_waterline_offset),
             DOC_SensorConfiguration(set_waterline_offset),
             py::arg("z"))
        .def("get_waterline_offset",
             &SensorConfiguration::get_waterline_offset,
             DOC_SensorConfiguration(get_waterline_offset))
        .def("set_depth_source",
             py::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_depth_source),
             DOC_SensorConfiguration(set_depth_source),
             py::arg("name"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"))
        .def("set_depth_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_depth_source),
             DOC_SensorConfiguration(set_depth_source_2),
             py::arg("sensor_offsets"))
        .def("get_depth_source",
             &SensorConfiguration::get_depth_source,
             DOC_SensorConfiguration(get_depth_source))
        .def("set_position_source",
             py::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_position_source),
             DOC_SensorConfiguration(set_position_source),
             py::arg("name"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"))
        .def("set_position_source",
             py::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_position_source),
             DOC_SensorConfiguration(set_position_source_2),
             py::arg("sensor_offsets"))
        .def("get_position_source",
             &SensorConfiguration::get_position_source,
             DOC_SensorConfiguration(get_position_source))
        .def("__eq__",
             &SensorConfiguration::operator==,
             DOC_SensorConfiguration(operator_eq),
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
