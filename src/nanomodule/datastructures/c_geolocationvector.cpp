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

void init_c_geolocationvector(nb::module_& m)
{
    nb::class_<GeolocationVector>(
        m,
        "GeolocationVector",
        "A class to store a vector of Geolocation elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<Geolocation>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &GeolocationVector::size)
        .def("size",
             &GeolocationVector::size)
        .def("empty",
             &GeolocationVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const GeolocationVector& self) { return self.get_timestamps(); },
            [](GeolocationVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const GeolocationVector& self) { return self.get_data(); },
            [](GeolocationVector& self, std::vector<Geolocation> val)
            { self.data() = std::move(val); },
            "Geolocation data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&GeolocationVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&GeolocationVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &GeolocationVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &GeolocationVector::reserve,
             nb::arg("n"))
        .def("clear",
             &GeolocationVector::clear)
        .def("resize",
             &GeolocationVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_z",
             &GeolocationVector::get_z)
        .def("get_yaw",
             &GeolocationVector::get_yaw)
        .def("get_pitch",
             &GeolocationVector::get_pitch)
        .def("get_roll",
             &GeolocationVector::get_roll)
        // ----- operators -----
        .def("__eq__",
             &GeolocationVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationVector)
        // end GeolocationVector
        ;
}
