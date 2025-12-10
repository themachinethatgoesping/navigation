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

void init_c_sensordatautmvector(nb::module_& m)
{
    nb::class_<SensordataUTMVector>(
        m,
        "SensordataUTMVector",
        "A class to store a vector of SensordataUTM elements with timestamps.")
        .def(nb::init<>())
        .def(nb::init<std::vector<double>, std::vector<SensordataUTM>>(),
             nb::arg("timestamps"),
             nb::arg("data"))
        // ----- size/empty -----
        .def("__len__",
             &SensordataUTMVector::size)
        .def("size",
             &SensordataUTMVector::size)
        .def("empty",
             &SensordataUTMVector::empty)
        // ----- direct vector access via properties -----
        .def_prop_rw(
            "timestamps",
            [](const SensordataUTMVector& self) { return self.get_timestamps(); },
            [](SensordataUTMVector& self, std::vector<double> val)
            { self.timestamps() = std::move(val); },
            "Timestamps in seconds since epoch (read/write)")
        .def_prop_rw(
            "data",
            [](const SensordataUTMVector& self) { return self.get_data(); },
            [](SensordataUTMVector& self, std::vector<SensordataUTM> val)
            { self.data() = std::move(val); },
            "SensordataUTM data elements (read/write)")
        // ----- element access -----
        .def("__getitem__",
             nb::overload_cast<size_t>(&SensordataUTMVector::at, nb::const_),
             nb::arg("index"))
        .def("at",
             nb::overload_cast<size_t>(&SensordataUTMVector::at, nb::const_),
             nb::arg("index"))
        .def("timestamp_at",
             &SensordataUTMVector::timestamp_at,
             nb::arg("index"))
        // ----- modifiers -----
        .def("reserve",
             &SensordataUTMVector::reserve,
             nb::arg("n"))
        .def("clear",
             &SensordataUTMVector::clear)
        .def("resize",
             &SensordataUTMVector::resize,
             nb::arg("n"))
        // ----- component-wise access (for Python performance) -----
        .def("get_northings",
             &SensordataUTMVector::get_northings)
        .def("get_eastings",
             &SensordataUTMVector::get_eastings)
        .def("get_utm_zones",
             &SensordataUTMVector::get_utm_zones)
        .def("get_northern_hemispheres",
             &SensordataUTMVector::get_northern_hemispheres)
        .def("get_depths",
             &SensordataUTMVector::get_depths)
        .def("get_heaves",
             &SensordataUTMVector::get_heaves)
        .def("get_headings",
             &SensordataUTMVector::get_headings)
        .def("get_pitches",
             &SensordataUTMVector::get_pitches)
        .def("get_rolls",
             &SensordataUTMVector::get_rolls)
        // ----- operators -----
        .def("__eq__",
             &SensordataUTMVector::operator==,
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataUTMVector)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataUTMVector)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataUTMVector)
        // end SensordataUTMVector
        ;
}
