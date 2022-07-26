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

void init_c_sensordatalatlon(py::module& m)
{

    py::class_<SensorDataLatLon>(m, "SensorDataLatLon", DOC(themachinethatgoesping, navigation, navdata, SensorDataLatLon))
        .def(py::init<const SensorDataUTM&>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLatLon, SensorDataLatLon_2),
             py::arg("sensordatalatlon_utm"))
        .def(py::init<double, double, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLatLon, SensorDataLatLon_3),
             py::arg("gps_latitude")    = 0,
             py::arg("gps_longitude")   = 0,
             py::arg("gps_z")           = 0,
             py::arg("heave_heave")     = 0,
             py::arg("compass_heading") = 0,
             py::arg("imu_yaw")         = 0,
             py::arg("imu_pitch")       = 0,
             py::arg("imu_roll")        = 0)
        .def("__eq__",
             &SensorDataLatLon::operator==,
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLatLon, operator_eq),
             py::arg("other"))
        .def_readwrite("gps_latitude", &SensorDataLatLon::gps_latitude)
        .def_readwrite("gps_longitude", &SensorDataLatLon::gps_longitude)
        .def_readwrite("gps_z", &SensorDataLatLon::gps_z)
        .def_readwrite("heave_heave", &SensorDataLatLon::heave_heave)
        .def_readwrite("compass_heading", &SensorDataLatLon::compass_heading)
        .def_readwrite("imu_yaw", &SensorDataLatLon::imu_yaw)
        .def_readwrite("imu_pitch", &SensorDataLatLon::imu_pitch)
        .def_readwrite("imu_roll", &SensorDataLatLon::imu_roll)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataLatLon)
        // end SensorDataLatLon
        ;
}
