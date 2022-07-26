// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/navdata.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::navdata;

void init_c_sensordata(py::module& m)
{

    py::class_<SensorData>(m, "SensorData", DOC(themachinethatgoesping, navigation, navdata, SensorData))
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorData, SensorData_3),
             py::arg("gps_z")           = 0,
             py::arg("heave_heave")     = 0,
             py::arg("compass_heading") = 0,
             py::arg("imu_yaw")         = 0,
             py::arg("imu_pitch")       = 0,
             py::arg("imu_roll")        = 0)
        .def("__eq__",
             &SensorData::operator==,
             DOC(themachinethatgoesping, navigation, navdata, SensorData, operator_eq),
             py::arg("other"))
        .def_readwrite("gps_z", &SensorData::gps_z)
        .def_readwrite("heave_heave", &SensorData::heave_heave)
        .def_readwrite("compass_heading", &SensorData::compass_heading)
        .def_readwrite("imu_yaw", &SensorData::imu_yaw)
        .def_readwrite("imu_pitch", &SensorData::imu_pitch)
        .def_readwrite("imu_roll", &SensorData::imu_roll)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorData)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorData)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorData)
        // end SensorData
        ;
}
