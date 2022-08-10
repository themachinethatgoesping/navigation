// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_sensordata(py::module& m)
{

    py::class_<SensorData>(
        m, "SensorData", DOC(themachinethatgoesping, navigation, datastructures, SensorData))
        .def(py::init<SensorDataLatLon>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorData, SensorData))
        .def(py::init<SensorDataLocal>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorData, SensorData))
        .def(py::init<SensorDataUTM>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorData, SensorData))
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorData, SensorData_2),
             py::arg("gps_z")           = 0,
             py::arg("heave_heave")     = 0,
             py::arg("heading_source") = 0,
             py::arg("imu_yaw")         = 0,
             py::arg("imu_pitch")       = 0,
             py::arg("imu_roll")        = 0)
        .def("__eq__",
             &SensorData::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensorData, operator_eq),
             py::arg("other"))
        .def_readwrite("gps_z",
                       &SensorData::gps_z,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, gps_z))
        .def_readwrite("heave_heave",
                       &SensorData::heave_heave,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, heave_heave))
        .def_readwrite(
            "heading_source",
            &SensorData::heading_source,
            DOC(themachinethatgoesping, navigation, datastructures, SensorData, heading_source))
        .def_readwrite("imu_yaw",
                       &SensorData::imu_yaw,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, imu_yaw))
        .def_readwrite("imu_pitch",
                       &SensorData::imu_pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, imu_pitch))
        .def_readwrite("imu_roll",
                       &SensorData::imu_roll,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, imu_roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorData)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorData)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorData)
        // end SensorData
        ;
}
