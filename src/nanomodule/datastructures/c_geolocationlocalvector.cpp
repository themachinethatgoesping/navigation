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

void init_c_geolocationlocalvector(nb::module_& m)
{
    nb::class_<GeolocationLocalVector>(
        m,
        "GeolocationLocalVector",
        "A class to store a vector of GeolocationLocal elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<GeolocationLocal>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &GeolocationLocalVector::size)
        .def("size",
             &GeolocationLocalVector::size)
        .def("empty",
             &GeolocationLocalVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const GeolocationLocalVector& self) { return self.get_timestamps(); },
            [](GeolocationLocalVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const GeolocationLocalVector& self) { return self.get_data(); },
            [](GeolocationLocalVector& self, std::vector<GeolocationLocal> val)
            { self.data() = std::move(val); },
            "GeolocationLocal data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&GeolocationLocalVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&GeolocationLocalVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &GeolocationLocalVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &GeolocationLocalVector::reserve,
             nb::arg("n"))
        .def("clear",
             &GeolocationLocalVector::clear)
        .def("resize",
             &GeolocationLocalVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_northings",
             &GeolocationLocalVector::get_northings)
        .def("get_eastings",
             &GeolocationLocalVector::get_eastings)
        .def("get_z",
             &GeolocationLocalVector::get_z)
        .def("get_yaw",
             &GeolocationLocalVector::get_yaw)
        .def("get_pitch",
             &GeolocationLocalVector::get_pitch)
        .def("get_roll",
             &GeolocationLocalVector::get_roll)
        // ----- operators -----
        .def("__eq__",
             &GeolocationLocalVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationLocalVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationLocalVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationLocalVector)
        // end GeolocationLocalVector
        ;
}
