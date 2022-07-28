// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/navdata.hpp"
#include "../themachinethatgoesping/navigation/sensorcoordinatesystem.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;

void init_c_sensorcoordinatesystem(py::module& m)
{
    py::class_<SensorCoordinateSystem>(
        m,
        "SensorCoordinateSystem",
        DOC(themachinethatgoesping, navigation, SensorCoordinateSystem))
        .def(py::init<>(),
            DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, SensorCoordinateSystem))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const navdata::SensorDataLatLon&>(
                 &SensorCoordinateSystem::compute_target_position, py::const_),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, compute_target_position),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const navdata::SensorDataUTM&>(
                 &SensorCoordinateSystem::compute_target_position, py::const_),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, compute_target_position_2),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const navdata::SensorDataLocal&>(
                 &SensorCoordinateSystem::compute_target_position, py::const_),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, compute_target_position_3),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, const navdata::SensorData&>(
                 &SensorCoordinateSystem::compute_target_position, py::const_),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, compute_target_position_4),
             py::arg("target_id"),
             py::arg("sensor_data"))
        .def("add_target",
             py::overload_cast<const std::string&, double, double, double, double, double, double>(
                 &SensorCoordinateSystem::add_target),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, add_target),
             py::arg("target_id"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("add_target",
             py::overload_cast<const std::string&, const navdata::PositionalOffsets&>(
                 &SensorCoordinateSystem::add_target),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, add_target_2),
             py::arg("target_id"),
             py::arg("target_offsets"))
        .def("get_target_offsets",
             &SensorCoordinateSystem::get_target_offsets,
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, get_target_offsets),
             py::arg("target_id"))
        .def("set_motion_sensor_offsets",
             py::overload_cast<double, double, double>(
                 &SensorCoordinateSystem::set_motion_sensor_offsets),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 set_motion_sensor_offsets),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("set_motion_sensor_offsets",
             py::overload_cast<const navdata::PositionalOffsets&>(
                 &SensorCoordinateSystem::set_motion_sensor_offsets),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 set_motion_sensor_offsets_2),
             py::arg("sensor_offsets"))
        .def("get_motion_sensor_offsets",
             &SensorCoordinateSystem::get_motion_sensor_offsets,
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 get_motion_sensor_offsets))
        .def("set_compass_offsets",
             py::overload_cast<double>(&SensorCoordinateSystem::set_compass_offsets),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, set_compass_offsets),
             py::arg("yaw"))
        .def("set_compass_offsets",
             py::overload_cast<const navdata::PositionalOffsets&>(
                 &SensorCoordinateSystem::set_compass_offsets),
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, set_compass_offsets_2),
             py::arg("sensor_offsets"))
        .def("get_compass_offsets",
             &SensorCoordinateSystem::get_compass_offsets,
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, get_compass_offsets))
        .def("set_depth_sensor_offsets",
             py::overload_cast<double, double, double>(
                 &SensorCoordinateSystem::set_depth_sensor_offsets),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 set_depth_sensor_offsets),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"))
        .def("set_depth_sensor_offsets",
             py::overload_cast<const navdata::PositionalOffsets&>(
                 &SensorCoordinateSystem::set_depth_sensor_offsets),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 set_depth_sensor_offsets_2),
             py::arg("sensor_offsets"))
        .def("get_depth_sensor_offsets",
             &SensorCoordinateSystem::get_depth_sensor_offsets,
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 get_depth_sensor_offsets))
        .def("set_position_system_offsets",
             py::overload_cast<double, double, double>(
                 &SensorCoordinateSystem::set_position_system_offsets),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 set_position_system_offsets),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"))
        .def("set_position_system_offsets",
             py::overload_cast<const navdata::PositionalOffsets&>(
                 &SensorCoordinateSystem::set_position_system_offsets),
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 set_position_system_offsets_2),
             py::arg("sensor_offsets"))
        .def("get_position_system_offsets",
             &SensorCoordinateSystem::get_position_system_offsets,
             DOC(themachinethatgoesping,
                 navigation,
                 SensorCoordinateSystem,
                 get_position_system_offsets))
        .def("__eq__",
             &SensorCoordinateSystem::operator==,
             DOC(themachinethatgoesping, navigation, SensorCoordinateSystem, operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorCoordinateSystem)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorCoordinateSystem)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorCoordinateSystem)
        // end SensorCoordinateSystem
        ;
}
