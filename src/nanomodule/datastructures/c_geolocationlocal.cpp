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

void init_c_geolocationlocal(nb::module_& m)
{

    nb::class_<GeolocationLocal, Geolocation>(
        m,
        "GeolocationLocal",
        DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal))
        .def(nb::init<const GeolocationUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLocal,
                 GeolocationLocal),
             nb::arg("geolocationutm"))
        .def(nb::init<const Geolocation&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLocal,
                 GeolocationLocal_2),
             nb::arg("geolocation"),
             nb::arg("northing"),
             nb::arg("easting"))
    .def(nb::init<double, double, float, float, float, float>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLocal,
                 GeolocationLocal_3),
             nb::arg("northing") = 0.0,
             nb::arg("easting")  = 0.0,
             nb::arg("z")        = 0.0f,
             nb::arg("yaw")      = 0.0f,
             nb::arg("pitch")    = 0.0f,
             nb::arg("roll")     = 0.0f)
        .def("__eq__",
             &GeolocationLocal::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal, operator_eq),
             nb::arg("other"))
        .def_rw(
            "northing",
            &GeolocationLocal::northing,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal, northing))
        .def_rw(
            "easting",
            &GeolocationLocal::easting,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal, easting))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationLocal)
        // end GeolocationLocal
        ;
}
