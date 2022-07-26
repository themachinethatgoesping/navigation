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

void init_c_sensordatautm(py::module& m)
{

    py::class_<SensorDataUTM, SensorDataLocal>(
        m, "SensorDataUTM", DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM))
        .def(py::init<const SensorData&, double, double, int, bool>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, SensorDataUTM_2),
             py::arg("sensordatalatlon"),
             py::arg("gps_northing"),
          py::arg("gps_easting"),
             py::arg("gps_zone"),
             py::arg("gps_northern_hemisphere"))
        .def(py::init<const SensorDataLocal&, int, bool>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, SensorDataUTM_3),
             py::arg("sensordata_local"),
             py::arg("gps_zone"),
             py::arg("gps_northern_hemisphere"))
        .def(py::init<const SensorDataLatLon&, int>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, SensorDataUTM_4),
             py::arg("sensordatalatlon"),
             py::arg("setgps_zone") = -1)
        .def(py::init<double, double, int, bool, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, SensorDataUTM_5),
             py::arg("gps_northing")            = 0,
             py::arg("gps_easting")             = 0,
             py::arg("gps_zone")                = 0,
             py::arg("gps_northern_hemisphere") = true,
             py::arg("gps_z")                   = 0,
             py::arg("heave_heave")             = 0,
             py::arg("compass_heading")         = 0,
             py::arg("imu_yaw")                 = 0,
             py::arg("imu_pitch")               = 0,
             py::arg("imu_roll")                = 0)
        .def("__eq__",
             &SensorDataUTM::operator==,
             DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, operator_eq),
             py::arg("rhs"))
        .def_readwrite("gps_zone", &SensorDataUTM::gps_zone)
        .def_readwrite("gps_northern_hemisphere", &SensorDataUTM::gps_northern_hemisphere)
        // static functions
        .def_static("to_sensordata",
                    &SensorDataUTM::to_sensordata,
                    DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, to_sensordata),
                    py::arg("sensordata_utm"))
        .def_static("from_sensordata",
                    &SensorDataUTM::from_sensordata,
                    DOC(themachinethatgoesping, navigation, navdata, SensorDataUTM, from_sensordata),
                    py::arg("sensordatalatlon"),
                    py::arg("setgps_zone") = -1)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataUTM)
        // end SensorDataUTM
        ;
}
