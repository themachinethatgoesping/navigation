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

void init_c_sensordatalocalvector(nb::module_& m)
{
    nb::class_<SensordataLocalVector>(
        m,
        "SensordataLocalVector",
        "A class to store a vector of SensordataLocal elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<SensordataLocal>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &SensordataLocalVector::size)
        .def("size",
             &SensordataLocalVector::size)
        .def("empty",
             &SensordataLocalVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const SensordataLocalVector& self) { return self.get_timestamps(); },
            [](SensordataLocalVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const SensordataLocalVector& self) { return self.get_data(); },
            [](SensordataLocalVector& self, std::vector<SensordataLocal> val)
            { self.data() = std::move(val); },
            "SensordataLocal data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&SensordataLocalVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&SensordataLocalVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &SensordataLocalVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &SensordataLocalVector::reserve,
             nb::arg("n"))
        .def("clear",
             &SensordataLocalVector::clear)
        .def("resize",
             &SensordataLocalVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_northings",
             &SensordataLocalVector::get_northings)
        .def("get_eastings",
             &SensordataLocalVector::get_eastings)
        .def("get_depths",
             &SensordataLocalVector::get_depths)
        .def("get_heaves",
             &SensordataLocalVector::get_heaves)
        .def("get_headings",
             &SensordataLocalVector::get_headings)
        .def("get_pitches",
             &SensordataLocalVector::get_pitches)
        .def("get_rolls",
             &SensordataLocalVector::get_rolls)
        // ----- operators -----
        .def("__eq__",
             &SensordataLocalVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataLocalVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataLocalVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataLocalVector)
        // end SensordataLocalVector
        ;
}
