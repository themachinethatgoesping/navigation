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

void init_c_geolocationlocal(py::module& m)
{

    py::class_<GeoLocationLocal>(
        m, "GeoLocationLocal", DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLocal))
        .def(py::init<const GeoLocationUTM&, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLocal, GeoLocationLocal_2),
             py::arg("geolocationutm"),
             py::arg("offset_northing") = 0,
             py::arg("offset_easting") = 0)
        .def(py::init<double, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLocal, GeoLocationLocal_3),
             py::arg("northing") = 0,
             py::arg("easting")  = 0,
             py::arg("z")        = 0,
             py::arg("yaw")      = 0,
             py::arg("pitch")    = 0,
             py::arg("roll")     = 0)
        .def("__eq__",
             &GeoLocationLocal::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLocal, operator_eq),
             py::arg("rhs"))
        .def_readwrite("northing", &GeoLocationLocal::northing)
        .def_readwrite("easting", &GeoLocationLocal::easting)
        .def_readwrite("z", &GeoLocationLocal::z)
        .def_readwrite("yaw", &GeoLocationLocal::yaw)
        .def_readwrite("pitch", &GeoLocationLocal::pitch)
        .def_readwrite("roll", &GeoLocationLocal::roll)
        // static functions
        .def_static("to_geolocationutm",
                    &GeoLocationLocal::to_geolocationutm,
                    DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLocal, to_geolocationutm),
                    py::arg("geolocation_local"),
                    py::arg("zone"),
                    py::arg("northern_hemisphere"),
                    py::arg("offset_northing") = 0,
                    py::arg("offset_easting")  = 0)
        .def_static("from_geolocationutm",
                    &GeoLocationLocal::from_geolocationutm,
                    DOC(themachinethatgoesping, navigation, datastructures, GeoLocationLocal, from_geolocationutm),
                    py::arg("geolocation_utm"),
                    py::arg("offset_northing") = 0,
                    py::arg("offset_easting")  = 0)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeoLocationLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeoLocationLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeoLocationLocal)
        // end GeoLocationLocal
        ;

    py::implicitly_convertible<GeoLocationUTM, GeoLocationLocal>();
    // py::implicitly_convertible<GeoLocationLocal, GeoLocationUTM>();
    // not possible because this conversion needs additional information about zone and hemisphere
}
