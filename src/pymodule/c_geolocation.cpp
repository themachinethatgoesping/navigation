// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/geolocation.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py        = pybind11;
using namespace themachinethatgoesping::navigation;

void init_c_geolocation(py::module& m)
{

    py::class_<GeoLocation>(
        m, "GeoLocation", DOC(themachinethatgoesping, navigation, GeoLocation))
        .def(
            py::init<double, double, double, double, double, double>(),
            DOC(themachinethatgoesping, navigation, GeoLocation, GeoLocation_2),
            py::arg("latitude")     = 0,
            py::arg("longitude")     = 0,
            py::arg("z")     = 0,
            py::arg("yaw")   = 0,
            py::arg("pitch") = 0,
            py::arg("roll")  = 0)
        .def("__eq__",
             &GeoLocation::operator==,
             DOC(themachinethatgoesping, navigation, GeoLocation, operator_eq), py::arg("rhs"))
        .def_readwrite("latitude",&GeoLocation::latitude)
        .def_readwrite("longitude",&GeoLocation::longitude)
        .def_readwrite("z",&GeoLocation::z)
        .def_readwrite("yaw",&GeoLocation::yaw)
        .def_readwrite("pitch",&GeoLocation::pitch)
        .def_readwrite("roll",&GeoLocation::roll)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocation)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocation)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocation)
        // end GeoLocation
        ;
}
