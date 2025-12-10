// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_geolocationlatlonvector(nb::module_& m)
{
    nb::class_<GeolocationLatLonVector>(
        m,
        "GeolocationLatLonVector",
        mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector)
        .def(nb::init<>(),
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_GeolocationLatLonVector)
        .def(nb::init<size_t>(),
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_GeolocationLatLonVector_2,
             nb::arg("capacity"))
        .def(nb::init<std::vector<double>, std::vector<GeolocationLatLon>>(),
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_GeolocationLatLonVector_3,
             nb::arg("timestamps"),
             nb::arg("geolocations"))
        // ----- size/empty -----
        .def("__len__",
             &GeolocationLatLonVector::size,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_size)
        .def("size",
             &GeolocationLatLonVector::size,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_size)
        .def("empty",
             &GeolocationLatLonVector::empty,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_empty)
        // ----- element access -----
        .def("__getitem__",
             &GeolocationLatLonVector::at,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_at,
             nb::arg("index"))
        .def("at",
             &GeolocationLatLonVector::at,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_at,
             nb::arg("index"))
        .def("timestamp_at",
             &GeolocationLatLonVector::timestamp_at,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_timestamp_at,
             nb::arg("index"))
        // ----- direct vector access -----
        .def("get_timestamps",
             &GeolocationLatLonVector::get_timestamps,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_timestamps)
        .def("get_geolocations",
             &GeolocationLatLonVector::get_geolocations,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_geolocations)
        // ----- component-wise access (for Python performance) -----
        .def("get_latitudes",
             &GeolocationLatLonVector::get_latitudes,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_latitudes)
        .def("get_longitudes",
             &GeolocationLatLonVector::get_longitudes,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_longitudes)
        .def("get_z",
             &GeolocationLatLonVector::get_z,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_z)
        .def("get_yaw",
             &GeolocationLatLonVector::get_yaw,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_yaw)
        .def("get_pitch",
             &GeolocationLatLonVector::get_pitch,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_pitch)
        .def("get_roll",
             &GeolocationLatLonVector::get_roll,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_roll)
        // ----- modifiers -----
        .def("reserve",
             &GeolocationLatLonVector::reserve,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_reserve,
             nb::arg("n"))
        .def("push_back",
             nb::overload_cast<double, const GeolocationLatLon&>(
                 &GeolocationLatLonVector::push_back),
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_push_back,
             nb::arg("timestamp"),
             nb::arg("geolocation"))
        // ----- operators -----
        .def("__eq__",
             &GeolocationLatLonVector::operator==,
             mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_operator_eq,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationLatLonVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationLatLonVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationLatLonVector)
        // end GeolocationLatLonVector
        ;
}
