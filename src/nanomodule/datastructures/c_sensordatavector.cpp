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

void init_c_sensordatavector(nb::module_& m)
{
    nb::class_<SensordataVector>(
        m,
        "SensordataVector",
        "A class to store a vector of Sensordata elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<Sensordata>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &SensordataVector::size)
        .def("size",
             &SensordataVector::size)
        .def("empty",
             &SensordataVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const SensordataVector& self) { return self.get_timestamps(); },
            [](SensordataVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const SensordataVector& self) { return self.get_data(); },
            [](SensordataVector& self, std::vector<Sensordata> val)
            { self.data() = std::move(val); },
            "Sensordata data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&SensordataVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&SensordataVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &SensordataVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &SensordataVector::reserve,
             nb::arg("n"))
        .def("clear",
             &SensordataVector::clear)
        .def("resize",
             &SensordataVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_depths",
             &SensordataVector::get_depths)
        .def("get_heaves",
             &SensordataVector::get_heaves)
        .def("get_headings",
             &SensordataVector::get_headings)
        .def("get_pitches",
             &SensordataVector::get_pitches)
        .def("get_rolls",
             &SensordataVector::get_rolls)
        // ----- operators -----
        .def("__eq__",
             &SensordataVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataVector)
        // end SensordataVector
        ;
}
