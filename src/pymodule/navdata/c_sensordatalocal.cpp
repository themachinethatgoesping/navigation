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

    py::class_<SensorDataLocal>(
        m, "SensorDataLocal", DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal))
        .def(py::init<const SensorDataUTM&, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, SensorDataLocal_2),
             py::arg("sensordatautm"),
             py::arg("offset_northing") = 0,
             py::arg("offset_easting")  = 0)
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
        .def_readwrite("gps_northing", &SensorDataLocal::gps_northing)
        .def_readwrite("gps_easting", &SensorDataLocal::gps_easting)
        .def_readwrite("gps_z", &SensorDataLocal::gps_z)
        .def_readwrite("heave_heave", &SensorDataLocal::heave_heave)
        .def_readwrite("compass_heading", &SensorDataLocal::compass_heading)
        .def_readwrite("imu_yaw", &SensorDataLocal::imu_yaw)
        .def_readwrite("imu_pitch", &SensorDataLocal::imu_pitch)
        .def_readwrite("imu_roll", &SensorDataLocal::imu_roll)
        // static functions
        .def_static("to_sensordatautm",
                    &SensorDataLocal::to_sensordatautm,
                    DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, to_sensordatautm),
                    py::arg("sensordata_local"),
                    py::arg("gps_zone"),
                    py::arg("gps_northern_hemisphere"),
                    py::arg("offset_northing") = 0,
                    py::arg("offset_easting")  = 0)
        .def_static("from_sensordatautm",
                    &SensorDataLocal::from_sensordatautm,
                    DOC(themachinethatgoesping, navigation, navdata, SensorDataLocal, from_sensordatautm),
                    py::arg("sensordata_utm"),
                    py::arg("offset_northing") = 0,
                    py::arg("offset_easting")  = 0)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataLocal)
        // end SensorDataLocal
        ;

    py::implicitly_convertible<SensorDataUTM, SensorDataLocal>();
    // py::implicitly_convertible<SensorDataLocal, SensorDataUTM>();
    // not possible because this conversion needs additional information about zone and hemisphere
}
