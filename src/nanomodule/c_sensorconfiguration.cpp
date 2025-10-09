// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/sensorconfiguration.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation;

#define DOC_SensorConfiguration(ARG)                                                               \
    DOC(themachinethatgoesping, navigation, SensorConfiguration, ARG)

void init_c_sensorconfiguration(nb::module_& m)
{
    nb::class_<SensorConfiguration>(
        m, "SensorConfiguration", DOC(themachinethatgoesping, navigation, SensorConfiguration))
        .def(nb::init<std::string_view>(),
             DOC_SensorConfiguration(SensorConfiguration),
             nb::arg("default_sensor_name") = "zero-referenced")
        .def("without_targets",
             &SensorConfiguration::without_targets,
             DOC_SensorConfiguration(without_targets))
        .def("can_merge_targets_with",
             &SensorConfiguration::can_merge_targets_with,
             DOC_SensorConfiguration(can_merge_targets_with),
             nb::arg("other"))
        .def("compute_target_position",
             nb::overload_cast<const std::string&, const datastructures::SensordataLatLon&>(
                 &SensorConfiguration::compute_target_position, nb::const_),
             DOC_SensorConfiguration(compute_target_position),
             nb::arg("target_id"),
             nb::arg("sensor_data"))
        .def("compute_target_position",
             nb::overload_cast<const std::string&, const datastructures::SensordataUTM&>(
                 &SensorConfiguration::compute_target_position, nb::const_),
             DOC_SensorConfiguration(compute_target_position_2),
             nb::arg("target_id"),
             nb::arg("sensor_data"))
        .def("compute_target_position",
             nb::overload_cast<const std::string&, const datastructures::SensordataLocal&>(
                 &SensorConfiguration::compute_target_position, nb::const_),
             DOC_SensorConfiguration(compute_target_position_3),
             nb::arg("target_id"),
             nb::arg("sensor_data"))
        .def("compute_target_position",
             nb::overload_cast<const std::string&, const datastructures::Sensordata&>(
                 &SensorConfiguration::compute_target_position, nb::const_),
             DOC_SensorConfiguration(compute_target_position_4),
             nb::arg("target_id"),
             nb::arg("sensor_data"))
        .def("has_target",
             &SensorConfiguration::has_target,
             DOC_SensorConfiguration(has_target),
             nb::arg("target_id"))
        .def("add_target",
             nb::overload_cast<const std::string&, float, float, float, float, float, float>(
                 &SensorConfiguration::add_target),
             DOC_SensorConfiguration(add_target),
             nb::arg("target_id"),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"),
             nb::arg("yaw"),
             nb::arg("pitch"),
             nb::arg("roll"))
        .def("add_target",
             nb::overload_cast<const std::string&, const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::add_target),
             DOC_SensorConfiguration(add_target_2),
             nb::arg("target_id"),
             nb::arg("target_offsets"))
        .def("add_targets",
             &SensorConfiguration::add_targets,
             DOC_SensorConfiguration(add_targets),
             nb::arg("targets"))
        .def("get_target",
             &SensorConfiguration::get_target,
             DOC_SensorConfiguration(get_target),
             nb::arg("target_id"))
        .def("get_targets", &SensorConfiguration::get_targets, DOC_SensorConfiguration(get_targets))
        .def("remove_target",
             &SensorConfiguration::remove_target,
             DOC_SensorConfiguration(remove_target),
             nb::arg("target_id"))
        .def("remove_targets",
             &SensorConfiguration::remove_targets,
             DOC_SensorConfiguration(remove_targets))
        .def("get_target_ids",
             &SensorConfiguration::get_target_ids,
             DOC_SensorConfiguration(get_target_ids))
        .def("set_attitude_source",
             nb::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_attitude_source),
             DOC_SensorConfiguration(set_attitude_source),
             nb::arg("name"),
             nb::arg("yaw"),
             nb::arg("pitch"),
             nb::arg("roll"))
        .def("set_attitude_source",
             nb::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_attitude_source),
             DOC_SensorConfiguration(set_attitude_source_2),
             nb::arg("sensor_offsets"))
        .def("get_attitude_source",
             &SensorConfiguration::get_attitude_source,
             DOC_SensorConfiguration(get_attitude_source))
        .def("set_heading_source",
             nb::overload_cast<std::string_view, float>(&SensorConfiguration::set_heading_source),
             DOC_SensorConfiguration(set_heading_source),
             nb::arg("name"),
             nb::arg("yaw"))
        .def("set_heading_source",
             nb::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_heading_source),
             DOC_SensorConfiguration(set_heading_source_2),
             nb::arg("sensor_offsets"))
        .def("get_heading_source",
             &SensorConfiguration::get_heading_source,
             DOC_SensorConfiguration(get_heading_source))
        .def("set_waterline_offset",
             nb::overload_cast<float>(&SensorConfiguration::set_waterline_offset),
             DOC_SensorConfiguration(set_waterline_offset),
             nb::arg("z"))
        .def("get_waterline_offset",
             &SensorConfiguration::get_waterline_offset,
             DOC_SensorConfiguration(get_waterline_offset))
        .def("set_depth_source",
             nb::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_depth_source),
             DOC_SensorConfiguration(set_depth_source),
             nb::arg("name"),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"))
        .def("set_depth_source",
             nb::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_depth_source),
             DOC_SensorConfiguration(set_depth_source_2),
             nb::arg("sensor_offsets"))
        .def("get_depth_source",
             &SensorConfiguration::get_depth_source,
             DOC_SensorConfiguration(get_depth_source))
        .def("set_position_source",
             nb::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_position_source),
             DOC_SensorConfiguration(set_position_source),
             nb::arg("name"),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"))
        .def("set_position_source",
             nb::overload_cast<const datastructures::PositionalOffsets&>(
                 &SensorConfiguration::set_position_source),
             DOC_SensorConfiguration(set_position_source_2),
             nb::arg("sensor_offsets"))
        .def("get_position_source",
             &SensorConfiguration::get_position_source,
             DOC_SensorConfiguration(get_position_source))
        .def("__eq__",
             &SensorConfiguration::operator==,
             DOC_SensorConfiguration(operator_eq),
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorConfiguration)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorConfiguration)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorConfiguration)
        // end SensorConfiguration
        ;
}
