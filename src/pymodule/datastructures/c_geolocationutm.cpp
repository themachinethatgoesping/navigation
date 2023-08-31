// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
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

#define DOC_GeoLocationUTM(ARG)                                                                    \
    DOC(themachinethatgoesping, navigation, datastructures, GeoLocationUTM, ARG)

void init_c_geolocationutm(py::module& m)
{
    py::class_<GeoLocationUTM, GeoLocationLocal>(
        m,
        "GeoLocationUTM",
        DOC(themachinethatgoesping, navigation, datastructures, GeoLocationUTM))
        .def(py::init<const GeoLocationLocal&, int, bool>(),
             DOC_GeoLocationUTM(GeoLocationUTM_2),
             py::arg("geolocationlatlon"),
             py::arg("utm_zone"),
             py::arg("utm_northern_hemisphere"))
        .def(py::init<const GeoLocationLatLon&, int>(),
             DOC_GeoLocationUTM(GeoLocationUTM_3),
             py::arg("geolocationlatlon"),
             py::arg("setzone") = -1)
        .def(py::init<double, double, int, bool, double, double, double, double>(),
             DOC_GeoLocationUTM(GeoLocationUTM_4),
             py::arg("northing")                = 0,
             py::arg("easting")                 = 0,
             py::arg("utm_zone")                = 0,
             py::arg("utm_northern_hemisphere") = true,
             py::arg("z")                       = 0,
             py::arg("yaw")                     = 0,
             py::arg("pitch")                   = 0,
             py::arg("roll")                    = 0)
        .def("__eq__",
             &GeoLocationUTM::operator==,
             DOC_GeoLocationUTM(operator_eq),
             py::arg("other"))
        .def_readwrite("utm_zone", &GeoLocationUTM::utm_zone, DOC_GeoLocationUTM(utm_zone))
        .def_readwrite("utm_northern_hemisphere",
                       &GeoLocationUTM::utm_northern_hemisphere,
                       DOC_GeoLocationUTM(utm_northern_hemisphere))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationUTM)
        // end GeoLocationUTM
        ;
}
