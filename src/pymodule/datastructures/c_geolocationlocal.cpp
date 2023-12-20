// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
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

void init_c_geolocationlocal(py::module& m)
{

    py::class_<GeolocationLocal, Geolocation>(
        m,
        "GeolocationLocal",
        DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal))
        .def(py::init<const GeolocationUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLocal,
                 GeolocationLocal),
             py::arg("geolocationutm"))
        .def(py::init<const Geolocation&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLocal,
                 GeolocationLocal_2),
             py::arg("geolocation"),
             py::arg("northing"),
             py::arg("easting"))
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 GeolocationLocal,
                 GeolocationLocal_3),
             py::arg("northing") = 0,
             py::arg("easting")  = 0,
             py::arg("z")        = 0,
             py::arg("yaw")      = 0,
             py::arg("pitch")    = 0,
             py::arg("roll")     = 0)
        .def("__eq__",
             &GeolocationLocal::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal, operator_eq),
             py::arg("other"))
        .def_readwrite(
            "northing",
            &GeolocationLocal::northing,
            DOC(themachinethatgoesping, navigation, datastructures, GeolocationLocal, northing))
        .def_readwrite(
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
