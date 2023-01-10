// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_positionaloffsets(py::module& m)
{

    py::class_<PositionalOffsets>(
        m,
        "PositionalOffsets",
        DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets))
        .def(py::init<std::string, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 PositionalOffsets,
                 PositionalOffsets_2),
             py::arg("name")  = "",
             py::arg("x")     = 0,
             py::arg("y")     = 0,
             py::arg("z")     = 0,
             py::arg("yaw")   = 0,
             py::arg("pitch") = 0,
             py::arg("roll")  = 0)

        .def(
            "__eq__",
            &PositionalOffsets::operator==,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, operator_eq),
            py::arg("other"))
        .def_readwrite(
            "name",
            &PositionalOffsets::name,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, name))
        .def_readwrite(
            "x",
            &PositionalOffsets::x,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, x))
        .def_readwrite(
            "y",
            &PositionalOffsets::y,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, y))
        .def_readwrite(
            "z",
            &PositionalOffsets::z,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, z))
        .def_readwrite(
            "yaw",
            &PositionalOffsets::yaw,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, yaw))
        .def_readwrite(
            "pitch",
            &PositionalOffsets::pitch,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, pitch))
        .def_readwrite(
            "roll",
            &PositionalOffsets::roll,
            DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(PositionalOffsets)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(PositionalOffsets)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(PositionalOffsets)
        // end PositionalOffsets
        ;
}
