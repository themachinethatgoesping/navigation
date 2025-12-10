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
        "A class to store a vector of GeolocationLatLon elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<GeolocationLatLon>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &GeolocationLatLonVector::size)
        .def("size",
             &GeolocationLatLonVector::size)
        .def("empty",
             &GeolocationLatLonVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const GeolocationLatLonVector& self) { return self.get_timestamps(); },
            [](GeolocationLatLonVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const GeolocationLatLonVector& self) { return self.get_data(); },
            [](GeolocationLatLonVector& self, std::vector<GeolocationLatLon> val)
            { self.data() = std::move(val); },
            "GeolocationLatLon data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&GeolocationLatLonVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&GeolocationLatLonVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &GeolocationLatLonVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &GeolocationLatLonVector::reserve,
             nb::arg("n"))
        .def("clear",
             &GeolocationLatLonVector::clear)
        .def("resize",
             &GeolocationLatLonVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_latitudes",
             &GeolocationLatLonVector::get_latitudes)
        .def("get_longitudes",
             &GeolocationLatLonVector::get_longitudes)
        .def("get_z",
             &GeolocationLatLonVector::get_z)
        .def("get_yaw",
             &GeolocationLatLonVector::get_yaw)
        .def("get_pitch",
             &GeolocationLatLonVector::get_pitch)
        .def("get_roll",
             &GeolocationLatLonVector::get_roll)
        // ----- operators -----
        .def("__eq__",
             &GeolocationLatLonVector::operator==,
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
