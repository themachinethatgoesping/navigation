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

#define DOC_GeolocationUTM(ARG)                                                                    \
    DOC(themachinethatgoesping, navigation, datastructures, GeolocationUTM, ARG)

void init_c_geolocationutm(nb::module_& m)
{
    nb::class_<GeolocationUTM, GeolocationLocal>(
        m,
        "GeolocationUTM",
        DOC(themachinethatgoesping, navigation, datastructures, GeolocationUTM))
        .def(nb::init<const GeolocationLocal&, int, bool>(),
             DOC_GeolocationUTM(GeolocationUTM_2),
             nb::arg("geolocationlocal"),
             nb::arg("utm_zone"),
             nb::arg("northern_hemisphere"))
        .def(nb::init<const GeolocationLatLon&, int>(),
             DOC_GeolocationUTM(GeolocationUTM_3),
             nb::arg("geolocationlatlon"),
             nb::arg("setzone") = -1)
            .def(nb::init<double, double, int, bool, float, float, float, float>(),
             DOC_GeolocationUTM(GeolocationUTM_4),
             nb::arg("northing")                = 0,
             nb::arg("easting")                 = 0,
             nb::arg("utm_zone")                = 0,
             nb::arg("northern_hemisphere") = true,
                nb::arg("z")                       = 0.0f,
                nb::arg("yaw")                     = 0.0f,
                nb::arg("pitch")                   = 0.0f,
                nb::arg("roll")                    = 0.0f)
        .def("__eq__",
             &GeolocationUTM::operator==,
             DOC_GeolocationUTM(operator_eq),
             nb::arg("other"))
        .def_rw("utm_zone", &GeolocationUTM::utm_zone, DOC_GeolocationUTM(utm_zone))
        .def_rw("northern_hemisphere",
                       &GeolocationUTM::northern_hemisphere,
                       DOC_GeolocationUTM(northern_hemisphere))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationUTM)
        // end GeolocationUTM
        ;
}
