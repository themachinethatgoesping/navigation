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

namespace py        = pybind11;
using namespace themachinethatgoesping::navigation::navdata;

void init_c_geolocationlatlon(py::module& m)
{

    py::class_<GeoLocationLatLon>(
        m, "GeoLocationLatLon", DOC(themachinethatgoesping, navigation, navdata, GeoLocationLatLon))
        .def(py::init<const GeoLocationUTM&>(),
             DOC(themachinethatgoesping, navigation, navdata, GeoLocationLatLon, GeoLocationLatLon_2),
             py::arg("geolocationlatlon_utm")       )   
        .def(
            py::init<double, double, double, double, double, double>(),
            DOC(themachinethatgoesping, navigation, navdata, GeoLocationLatLon, GeoLocationLatLon_3),
            py::arg("latitude")     = 0,
            py::arg("longitude")     = 0,
            py::arg("z")     = 0,
            py::arg("yaw")   = 0,
            py::arg("pitch") = 0,
            py::arg("roll")  = 0)
        .def("__eq__",
             &GeoLocationLatLon::operator==,
             DOC(themachinethatgoesping, navigation, navdata, GeoLocationLatLon, operator_eq), py::arg("rhs"))
        .def_readwrite("latitude",&GeoLocationLatLon::latitude)
        .def_readwrite("longitude",&GeoLocationLatLon::longitude)
        .def_readwrite("z",&GeoLocationLatLon::z)
        .def_readwrite("yaw",&GeoLocationLatLon::yaw)
        .def_readwrite("pitch",&GeoLocationLatLon::pitch)
        .def_readwrite("roll",&GeoLocationLatLon::roll)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationLatLon)
        // end GeoLocationLatLon
        ;

}
