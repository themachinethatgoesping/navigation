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

void init_c_sensordatalatlonvector(nb::module_& m)
{
    nb::class_<SensordataLatLonVector>(
        m,
        "SensordataLatLonVector",
        "A class to store a vector of SensordataLatLon elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<SensordataLatLon>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &SensordataLatLonVector::size)
        .def("size",
             &SensordataLatLonVector::size)
        .def("empty",
             &SensordataLatLonVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const SensordataLatLonVector& self) { return self.get_timestamps(); },
            [](SensordataLatLonVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const SensordataLatLonVector& self) { return self.get_data(); },
            [](SensordataLatLonVector& self, std::vector<SensordataLatLon> val)
            { self.data() = std::move(val); },
            "SensordataLatLon data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&SensordataLatLonVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&SensordataLatLonVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &SensordataLatLonVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &SensordataLatLonVector::reserve,
             nb::arg("n"))
        .def("clear",
             &SensordataLatLonVector::clear)
        .def("resize",
             &SensordataLatLonVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_latitudes",
             &SensordataLatLonVector::get_latitudes)
        .def("get_longitudes",
             &SensordataLatLonVector::get_longitudes)
        .def("get_depths",
             &SensordataLatLonVector::get_depths)
        .def("get_heaves",
             &SensordataLatLonVector::get_heaves)
        .def("get_headings",
             &SensordataLatLonVector::get_headings)
        .def("get_pitches",
             &SensordataLatLonVector::get_pitches)
        .def("get_rolls",
             &SensordataLatLonVector::get_rolls)
        // ----- operators -----
        .def("__eq__",
             &SensordataLatLonVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataLatLonVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataLatLonVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataLatLonVector)
        // end SensordataLatLonVector
        ;
}
