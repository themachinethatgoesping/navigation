// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/geolocationutm.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;

void init_c_geolocationutm(py::module& m)
{

    py::class_<GeoLocationUTM>(
        m, "GeoLocationUTM", DOC(themachinethatgoesping, navigation, GeoLocationUTM))
        .def(py::init<const GeoLocation&, int>(),
             DOC(themachinethatgoesping, navigation, GeoLocationUTM, GeoLocationUTM_2),
             py::arg("geolocation"),
             py::arg("setzone") = -1)
        .def(py::init<double, double, int, bool, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, GeoLocationUTM, GeoLocationUTM_3),
             py::arg("northing")            = 0,
             py::arg("easting")             = 0,
             py::arg("zone")                = 0,
             py::arg("northern_hemisphere") = true,
             py::arg("z")                   = 0,
             py::arg("yaw")                 = 0,
             py::arg("pitch")               = 0,
             py::arg("roll")                = 0)
        .def("__eq__",
             &GeoLocationUTM::operator==,
             DOC(themachinethatgoesping, navigation, GeoLocationUTM, operator_eq),
             py::arg("rhs"))
        .def_readwrite("northing", &GeoLocationUTM::northing)
        .def_readwrite("easting", &GeoLocationUTM::easting)
        .def_readwrite("zone", &GeoLocationUTM::zone)
        .def_readwrite("northern_hemisphere", &GeoLocationUTM::northern_hemisphere)
        .def_readwrite("z", &GeoLocationUTM::z)
        .def_readwrite("yaw", &GeoLocationUTM::yaw)
        .def_readwrite("pitch", &GeoLocationUTM::pitch)
        .def_readwrite("roll", &GeoLocationUTM::roll)
        // static functions
        .def_static("to_geolocation",
                    &GeoLocationUTM::to_geolocation,
                    DOC(themachinethatgoesping, navigation, GeoLocationUTM, to_geolocation),
                    py::arg("geolocation_utm"))
        .def_static("from_geolocation",
                    &GeoLocationUTM::from_geolocation,
                    DOC(themachinethatgoesping, navigation, GeoLocationUTM, from_geolocation),
                    py::arg("geolocation"),
                    py::arg("setzone") = -1)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationUTM)
        // end GeoLocationUTM
        ;

    py::implicitly_convertible<GeoLocation, GeoLocationUTM>();
    py::implicitly_convertible<GeoLocationUTM, GeoLocation>();
}
