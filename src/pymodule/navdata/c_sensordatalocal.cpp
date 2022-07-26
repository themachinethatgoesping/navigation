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

void init_c_sensordatalocal(py::module& m)
{

    py::class_<SensorDataLocal, SensorData>(
        m, "SensorDataLocal", DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal))
        .def(py::init<const SensorDataUTM&>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, SensorDataLocal),
             py::arg("sensordatautm"))
        .def(py::init<const SensorData&, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, SensorDataLocal_2),
             py::arg("sensordata"),
             py::arg("gps_northing"),
             py::arg("gps_easting"))
        .def(py::init<double, double, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, SensorDataLocal_3),
             py::arg("gps_northing")    = 0,
             py::arg("gps_easting")     = 0,
             py::arg("gps_z")           = 0,
             py::arg("heave_heave")     = 0,
             py::arg("compass_heading") = 0,
             py::arg("imu_yaw")         = 0,
             py::arg("imu_pitch")       = 0,
             py::arg("imu_roll")        = 0)
        .def("__eq__",
             &SensorDataLocal::operator==,
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, operator_eq),
             py::arg("rhs"))
        .def_readwrite("gps_northing", &SensorDataLocal::gps_northing, DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, gps_northing))
        .def_readwrite("gps_easting", &SensorDataLocal::gps_easting, DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, gps_easting))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataLocal)
        // end SensorDataLocal
        ;

}
