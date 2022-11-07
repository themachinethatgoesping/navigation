// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_pybind/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_geolocation(py::module& m)
{

    py::class_<GeoLocation>(
        m, "GeoLocation", DOC(themachinethatgoesping, navigation, datastructures, GeoLocation))
        .def(py::init<GeoLocationLatLon>(),
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, GeoLocation),
             py::arg("geolocation_latlon"))
        .def(py::init<GeoLocationLocal>(),
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, GeoLocation),
             py::arg("geolocation_local"))
        .def(py::init<GeoLocationUTM>(),
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, GeoLocation),
             py::arg("geolocation_utm"))
        .def(py::init<double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, GeoLocation_2),
             py::arg("z")     = 0,
             py::arg("yaw")   = 0,
             py::arg("pitch") = 0,
             py::arg("roll")  = 0)
        .def("__eq__",
             &GeoLocation::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, operator_eq),
             py::arg("other"))
        .def_readwrite("z",
                       &GeoLocation::z,
                       DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, z))
        .def_readwrite("yaw",
                       &GeoLocation::yaw,
                       DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, yaw))
        .def_readwrite("pitch",
                       &GeoLocation::pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, pitch))
        .def_readwrite("roll",
                       &GeoLocation::roll,
                       DOC(themachinethatgoesping, navigation, datastructures, GeoLocation, roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocation)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocation)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocation)
        // end GeoLocation
        ;
}
