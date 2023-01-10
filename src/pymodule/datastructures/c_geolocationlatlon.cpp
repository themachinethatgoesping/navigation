// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_geolocationlatlon(py::module& m)
{

    py::class_<GeoLocationLatLon, GeoLocation>(
        m,
        "GeoLocationLatLon",
        DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLatLon))
        .def(py::init<const GeoLocation&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeoLocationLatLon,
                 GeoLocationLatLon_2),
             py::arg("location"),
             py::arg("latitude"),
             py::arg("longitude"))
        .def(py::init<const GeoLocationUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeoLocationLatLon,
                 GeoLocationLatLon_3),
             py::arg("geolocationlatlon_utm"))
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeoLocationLatLon,
                 GeoLocationLatLon_4),
             py::arg("latitude")  = 0,
             py::arg("longitude") = 0,
             py::arg("z")         = 0,
             py::arg("yaw")       = 0,
             py::arg("pitch")     = 0,
             py::arg("roll")      = 0)
        .def(
            "__eq__",
            &GeoLocationLatLon::operator==,
            DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLatLon, operator_eq),
            py::arg("other"))
        .def_readwrite(
            "latitude",
            &GeoLocationLatLon::latitude,
            DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLatLon, latitude))
        .def_readwrite(
            "longitude",
            &GeoLocationLatLon::longitude,
            DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLatLon, longitude))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationLatLon)
        // end GeoLocationLatLon
        ;
}
