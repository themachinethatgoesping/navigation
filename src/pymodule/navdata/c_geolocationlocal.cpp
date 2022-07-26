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

void init_c_geolocationlocal(py::module& m)
{

    py::class_<GeoLocationLocal, GeoLocation>(
        m, "GeoLocationLocal", DOC(themachinethatgoesping, navigation, navdata, GeoLocationLocal))
        .def(py::init<const GeoLocationUTM&>(),
             DOC(themachinethatgoesping, navigation, navdata, GeoLocationLocal, GeoLocationLocal),
             py::arg("geolocationutm"))
        .def(py::init<const GeoLocation&, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, GeoLocationLocal, GeoLocationLocal_2),
             py::arg("geolocation"),
             py::arg("northing"),
             py::arg("easting"))
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, navdata, GeoLocationLocal, GeoLocationLocal_3),
             py::arg("northing") = 0,
             py::arg("easting")  = 0,
             py::arg("z")        = 0,
             py::arg("yaw")      = 0,
             py::arg("pitch")    = 0,
             py::arg("roll")     = 0)
        .def("__eq__",
             &GeoLocationLocal::operator==,
             DOC(themachinethatgoesping, navigation, navdata, GeoLocationLocal, operator_eq),
             py::arg("rhs"))
        .def_readwrite("northing", &GeoLocationLocal::northing)
        .def_readwrite("easting", &GeoLocationLocal::easting)
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationLocal)
        // end GeoLocationLocal
        ;

}
