// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/positionaloffsets.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py        = pybind11;
using namespace themachinethatgoesping::navigation;

void init_c_positionaloffsets(py::module& m)
{

    py::class_<PositionalOffsets>(
        m, "PositionalOffsets", DOC(themachinethatgoesping, navigation, PositionalOffsets))
        .def(
            py::init<double, double, double, double, double, double>(),
            DOC(themachinethatgoesping, navigation, PositionalOffsets, PositionalOffsets_2),
            py::arg("x")     = 0,
            py::arg("y")     = 0,
            py::arg("z")     = 0,
            py::arg("yaw")   = 0,
            py::arg("pitch") = 0,
            py::arg("roll")  = 0)
        .def("__eq__",
             &PositionalOffsets::operator==,
             DOC(themachinethatgoesping, navigation, PositionalOffsets, operator_eq), py::arg("rhs"))
        .def_readwrite("x",&PositionalOffsets::x)
        .def_readwrite("y",&PositionalOffsets::y)
        .def_readwrite("z",&PositionalOffsets::z)
        .def_readwrite("yaw",&PositionalOffsets::yaw)
        .def_readwrite("pitch",&PositionalOffsets::pitch)
        .def_readwrite("roll",&PositionalOffsets::roll)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(PositionalOffsets)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(PositionalOffsets)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(PositionalOffsets)
        // end PositionalOffsets
        ;
}
