// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_geolocationlatlon(nb::module_& m)
{

    nb::class_<GeolocationLatLon, Geolocation>(
        m,
        "GeolocationLatLon",
        DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon))
        .def(nb::init<const Geolocation&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLatLon,
                 GeolocationLatLon_2),
             nb::arg("location"),
             nb::arg("latitude"),
             nb::arg("longitude"))
        .def(nb::init<const GeolocationUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLatLon,
                 GeolocationLatLon_3),
             nb::arg("geolocationlatlon_utm"))
    .def(nb::init<double, double, float, float, float, float>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLatLon,
                 GeolocationLatLon_4),
             nb::arg("latitude")  = 0,
             nb::arg("longitude") = 0,
             nb::arg("z")        = 0.0f,
             nb::arg("yaw")      = 0.0f,
             nb::arg("pitch")    = 0.0f,
             nb::arg("roll")     = 0.0f)
        .def(
            "__eq__",
            &GeolocationLatLon::operator==,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon, operator_eq),
            nb::arg("other"))
        .def_rw(
            "latitude",
            &GeolocationLatLon::latitude,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLatLon, latitude))
        .def_rw(
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
