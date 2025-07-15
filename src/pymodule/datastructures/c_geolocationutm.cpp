// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

#define DOC_GeolocationUTM(ARG)                                                                    \
    DOC(themachinethatgoesping, navigation, datastructures, GeolocationUTM, ARG)

void init_c_geolocationutm(py::module& m)
{
    py::class_<GeolocationUTM, GeolocationLocal>(
        m,
        "GeolocationUTM",
        DOC(themachinethatgoesping, navigation, datastructures, GeolocationUTM))
        .def(py::init<const GeolocationLocal&, int, bool>(),
             DOC_GeolocationUTM(GeolocationUTM_2),
             py::arg("geolocationlocal"),
             py::arg("utm_zone"),
             py::arg("northern_hemisphere"))
        .def(py::init<const GeolocationLatLon&, int>(),
             DOC_GeolocationUTM(GeolocationUTM_3),
             py::arg("geolocationlatlon"),
             py::arg("setzone") = -1)
        .def(py::init<double, double, int, bool, double, double, double, double>(),
             DOC_GeolocationUTM(GeolocationUTM_4),
             py::arg("northing")                = 0,
             py::arg("easting")                 = 0,
             py::arg("utm_zone")                = 0,
             py::arg("northern_hemisphere") = true,
             py::arg("z")                       = 0,
             py::arg("yaw")                     = 0,
             py::arg("pitch")                   = 0,
             py::arg("roll")                    = 0)
        .def("__eq__",
             &GeolocationUTM::operator==,
             DOC_GeolocationUTM(operator_eq),
             py::arg("other"))
        .def_readwrite("utm_zone", &GeolocationUTM::utm_zone, DOC_GeolocationUTM(utm_zone))
        .def_readwrite("northern_hemisphere",
                       &GeolocationUTM::northern_hemisphere,
                       DOC_GeolocationUTM(northern_hemisphere))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationUTM)
        // end GeolocationUTM
        ;
}
