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

void init_c_geolocationutmvector(nb::module_& m)
{
    nb::class_<GeolocationUTMVector>(
        m,
        "GeolocationUTMVector",
        "A class to store a vector of GeolocationUTM elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<GeolocationUTM>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &GeolocationUTMVector::size)
        .def("size",
             &GeolocationUTMVector::size)
        .def("empty",
             &GeolocationUTMVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const GeolocationUTMVector& self) { return self.get_timestamps(); },
            [](GeolocationUTMVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const GeolocationUTMVector& self) { return self.get_data(); },
            [](GeolocationUTMVector& self, std::vector<GeolocationUTM> val)
            { self.data() = std::move(val); },
            "GeolocationUTM data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&GeolocationUTMVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&GeolocationUTMVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &GeolocationUTMVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &GeolocationUTMVector::reserve,
             nb::arg("n"))
        .def("clear",
             &GeolocationUTMVector::clear)
        .def("resize",
             &GeolocationUTMVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_northings",
             &GeolocationUTMVector::get_northings)
        .def("get_eastings",
             &GeolocationUTMVector::get_eastings)
        .def("get_utm_zones",
             &GeolocationUTMVector::get_utm_zones)
        .def("get_northern_hemispheres",
             &GeolocationUTMVector::get_northern_hemispheres)
        .def("get_z",
             &GeolocationUTMVector::get_z)
        .def("get_yaw",
             &GeolocationUTMVector::get_yaw)
        .def("get_pitch",
             &GeolocationUTMVector::get_pitch)
        .def("get_roll",
             &GeolocationUTMVector::get_roll)
        // ----- operators -----
        .def("__eq__",
             &GeolocationUTMVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(GeolocationUTMVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(GeolocationUTMVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(GeolocationUTMVector)
        // end GeolocationUTMVector
        ;
}
