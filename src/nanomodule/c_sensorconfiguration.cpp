// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/sensorconfiguration.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/optional.h>
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
        .def("compute_target_pose",
             &SensorConfiguration::compute_target_pose,
             DOC_SensorConfiguration(compute_target_pose),
             nb::arg("target_id"),
             nb::arg("sensor_data"),
             nb::arg("reference_heading_in_degrees"),
             nb::arg("subarray_id")   = "",
             nb::arg("subarray_pose") = std::optional<datastructures::SensorPose>())
        .def("compute_position_system_offset",
             &SensorConfiguration::compute_position_system_offset,
             DOC_SensorConfiguration(compute_position_system_offset),
             nb::arg("sensor_data"),
             nb::arg("reference_heading_in_degrees") = 0.f,
             nb::arg("at_waterline")                 = false)
        .def("get_vessel_rotation",
             &SensorConfiguration::get_vessel_rotation,
             DOC_SensorConfiguration(get_vessel_rotation),
             nb::arg("sensor_data"),
             nb::arg("reference_heading_in_degrees") = 0.f)
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
             nb::overload_cast<const std::string&, const datastructures::SensorPose&>(
                 &SensorConfiguration::add_target),
             DOC_SensorConfiguration(add_target_2),
             nb::arg("target_id"),
             nb::arg("target_offsets"))
        .def("add_targets",
             &SensorConfiguration::add_targets,
             DOC_SensorConfiguration(add_targets),
             nb::arg("targets"))
        .def("get_target",
             nb::overload_cast<const std::string&>(&SensorConfiguration::get_target, nb::const_),
             DOC_SensorConfiguration(get_target),
             nb::arg("target_id"))
        .def("get_target",
             nb::overload_cast<const std::string&,
                               const std::string&,
                               const std::optional<datastructures::SensorPose>&>(
                 &SensorConfiguration::get_target, nb::const_),
             "Get a target's static pose, optionally combined with a subarray phase center "
             "(vessel-static frame).",
             nb::arg("target_id"),
             nb::arg("subarray_id"),
             nb::arg("subarray_pose") = std::optional<datastructures::SensorPose>())
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
        .def("add_target_subarray",
             &SensorConfiguration::add_target_subarray,
             DOC_SensorConfiguration(add_target_subarray),
             nb::arg("target_id"),
             nb::arg("subarray_id"),
             nb::arg("subarray_offsets"))
        .def("set_target_subarrays",
             &SensorConfiguration::set_target_subarrays,
             DOC_SensorConfiguration(set_target_subarrays),
             nb::arg("target_id"),
             nb::arg("subarrays"))
        .def("set_target_subarrays_from_model",
             &SensorConfiguration::set_target_subarrays_from_model,
             DOC_SensorConfiguration(set_target_subarrays_from_model),
             nb::arg("target_id"),
             nb::arg("model_name"))
        .def("has_target_subarrays",
             &SensorConfiguration::has_target_subarrays,
             DOC_SensorConfiguration(has_target_subarrays),
             nb::arg("target_id"))
        .def("has_target_subarray",
             &SensorConfiguration::has_target_subarray,
             DOC_SensorConfiguration(has_target_subarray),
             nb::arg("target_id"),
             nb::arg("subarray_id"))
        .def("get_target_subarray",
             &SensorConfiguration::get_target_subarray,
             DOC_SensorConfiguration(get_target_subarray),
             nb::arg("target_id"),
             nb::arg("subarray_id"))
        .def("get_target_subarrays",
             &SensorConfiguration::get_target_subarrays,
             DOC_SensorConfiguration(get_target_subarrays),
             nb::arg("target_id"))
        .def("get_target_subarray_ids",
             &SensorConfiguration::get_target_subarray_ids,
             DOC_SensorConfiguration(get_target_subarray_ids),
             nb::arg("target_id"))
        .def("remove_target_subarrays",
             &SensorConfiguration::remove_target_subarrays,
             DOC_SensorConfiguration(remove_target_subarrays),
             nb::arg("target_id"))
        .def_static("get_model_subarray_offsets",
                    &SensorConfiguration::get_model_subarray_offsets,
                    DOC_SensorConfiguration(get_model_subarray_offsets),
                    nb::arg("model_name"))
        .def_static("get_model_subarray_offset",
                    &SensorConfiguration::get_model_subarray_offset,
                    DOC_SensorConfiguration(get_model_subarray_offset),
                    nb::arg("model_name"),
                    nb::arg("subarray_id"))
        .def("set_model_name",
             &SensorConfiguration::set_model_name,
             DOC_SensorConfiguration(set_model_name),
             nb::arg("name"))
        .def("get_model_name",
             &SensorConfiguration::get_model_name,
             DOC_SensorConfiguration(get_model_name))
        .def("set_transducer_configuration",
             &SensorConfiguration::set_transducer_configuration,
             DOC_SensorConfiguration(set_transducer_configuration),
             nb::arg("cfg"))
        .def("get_transducer_configuration",
             &SensorConfiguration::get_transducer_configuration,
             DOC_SensorConfiguration(get_transducer_configuration))
        .def("set_attitude_source",
             nb::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_attitude_source),
             DOC_SensorConfiguration(set_attitude_source),
             nb::arg("name"),
             nb::arg("yaw"),
             nb::arg("pitch"),
             nb::arg("roll"))
        .def("set_attitude_source",
             nb::overload_cast<const datastructures::SensorPose&>(
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
             nb::overload_cast<const datastructures::SensorPose&>(
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
        .def("set_position_source_motion_compensated",
             &SensorConfiguration::set_position_source_motion_compensated,
             DOC_SensorConfiguration(set_position_source_motion_compensated),
             nb::arg("motion_compensated"))
        .def("get_position_source_motion_compensated",
             &SensorConfiguration::get_position_source_motion_compensated,
             DOC_SensorConfiguration(get_position_source_motion_compensated))
        .def("set_depth_source",
             nb::overload_cast<std::string_view, float, float, float>(
                 &SensorConfiguration::set_depth_source),
             DOC_SensorConfiguration(set_depth_source),
             nb::arg("name"),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"))
        .def("set_depth_source",
             nb::overload_cast<const datastructures::SensorPose&>(
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
             nb::overload_cast<const datastructures::SensorPose&>(
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
        // printing functions with a style selector (optionA True = one row per target,
        // False = transposed table keeping an explanation column)
        .def("set_printer_style",
             &SensorConfiguration::set_printer_style,
             "Select the print()/info_string() table layout: True = one row per target (default), "
             "False = transposed (fields x/y/z/... as rows, records as columns, explanation column).",
             nb::arg("row_per_target"))
        .def(
            "__repr__",
            [](SensorConfiguration& self) { return self.__printer__(3, true).class_name(); },
            "Return object information as string")
        .def(
            "__str__",
            [](SensorConfiguration& self) { return self.__printer__(3, true).create_str(); },
            "Return object information as string")
        .def(
            "info_string",
            [](SensorConfiguration& self,
               unsigned int         float_precision,
               bool                 superscript_exponents,
               std::optional<bool>  optionA) {
                if (optionA.has_value())
                    self.set_printer_style(*optionA);
                return self.__printer__(float_precision, superscript_exponents).create_str();
            },
            "Return object information as string",
            nb::arg("float_precision")       = 3,
            nb::arg("superscript_exponents") = true,
            nb::arg("optionA")               = std::nullopt)
        .def(
            "print",
            [](SensorConfiguration& self,
               unsigned int         float_precision,
               bool                 superscript_exponents,
               std::optional<bool>  optionA) {
                if (optionA.has_value())
                    self.set_printer_style(*optionA);
                nb::print(
                    self.__printer__(float_precision, superscript_exponents).create_str().c_str());
            },
            "Print object information (optionA: True = one row per target, False = transposed table)",
            nb::arg("float_precision")       = 3,
            nb::arg("superscript_exponents") = true,
            nb::arg("optionA")               = std::nullopt)
        // end SensorConfiguration
        ;
}
