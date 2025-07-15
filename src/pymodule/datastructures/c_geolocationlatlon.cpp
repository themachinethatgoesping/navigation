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

void init_c_geolocationlatlon(py::module& m)
{

    py::class_<GeolocationLatLon, Geolocation>(
        m,
        "GeolocationLatLon",
        DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon))
        .def(py::init<const Geolocation&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLatLon,
                 GeolocationLatLon_2),
             py::arg("location"),
             py::arg("latitude"),
             py::arg("longitude"))
        .def(py::init<const GeolocationUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLatLon,
                 GeolocationLatLon_3),
             py::arg("geolocationlatlon_utm"))
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLatLon,
                 GeolocationLatLon_4),
             py::arg("latitude")  = 0,
             py::arg("longitude") = 0,
             py::arg("z")         = 0,
             py::arg("yaw")       = 0,
             py::arg("pitch")     = 0,
             py::arg("roll")      = 0)
        .def(
            "__eq__",
            &GeolocationLatLon::operator==,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon, operator_eq),
            py::arg("other"))
        .def_readwrite(
            "latitude",
            &GeolocationLatLon::latitude,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon, latitude))
        .def_readwrite(
            "longitude",
            &GeolocationLatLon::longitude,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon, longitude))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationLatLon)
        // end GeolocationLatLon
        ;
}
