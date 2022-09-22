// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_geolocationutm(py::module& m)
{

    py::class_<GeoLocationUTM, GeoLocationLocal>(
        m,
        "GeoLocationUTM",
        DOC(themachinethatgoesping, navigation, datastructures, GeoLocationUTM))
        .def(py::init<const GeoLocationLocal&, int, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeoLocationUTM,
                 GeoLocationUTM_2),
             py::arg("geolocationlatlon"),
             py::arg("zone"),
             py::arg("northern_hemisphere"))
        .def(py::init<const GeoLocationLatLon&, int>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeoLocationUTM,
                 GeoLocationUTM_3),
             py::arg("geolocationlatlon"),
             py::arg("setzone") = -1)
        .def(py::init<double, double, int, bool, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeoLocationUTM,
                 GeoLocationUTM_4),
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
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocationUTM, operator_eq),
             py::arg("rhs"))
        .def_readwrite(
            "zone",
            &GeoLocationUTM::zone,
            DOC(themachinethatgoesping, navigation, datastructures, GeoLocationUTM, zone))
        .def_readwrite("northern_hemisphere",
                       &GeoLocationUTM::northern_hemisphere,
                       DOC(themachinethatgoesping,
                           navigation,
                           datastructures,
                           GeoLocationUTM,
                           northern_hemisphere))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationUTM)
        // end GeoLocationUTM
        ;
}
