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
             py::arg("depth")   = 0,
             py::arg("heave")   = 0,
             py::arg("heading") = 0,
             py::arg("imu_yaw") = 0,
             py::arg("pitch")   = 0,
             py::arg("roll")    = 0)
        .def("__eq__",
             &SensorData::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensorData, operator_eq),
             py::arg("other"))
        .def_readwrite("depth",
                       &SensorData::depth,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, depth))
        .def_readwrite("heave",
                       &SensorData::heave,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, heave))
        .def_readwrite("heading",
                       &SensorData::heading,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, heading))
        .def_readwrite("imu_yaw",
                       &SensorData::imu_yaw,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, imu_yaw))
        .def_readwrite("pitch",
                       &SensorData::pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, pitch))
        .def_readwrite("roll",
                       &SensorData::roll,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorData, roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorData)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorData)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorData)
        // end SensorData
        ;
}
