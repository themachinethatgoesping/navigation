// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation::datastructures;

#define DOC_PositionalOffsets(ARG)                                                                 \
    DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, ARG)

void init_c_positionaloffsets(nb::module_& m)
{

    nb::class_<PositionalOffsets>(
        m,
        "PositionalOffsets",
        DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets))
        .def(nb::init<std::string, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 PositionalOffsets,
                 PositionalOffsets_2),
             nb::arg("name")  = "",
             nb::arg("x")     = 0,
             nb::arg("y")     = 0,
             nb::arg("z")     = 0,
             nb::arg("yaw")   = 0,
             nb::arg("pitch") = 0,
             nb::arg("roll")  = 0)
        .def_static("from_txrx",
                    &PositionalOffsets::from_txrx,
                    DOC_PositionalOffsets(from_txrx),
                    nb::arg("tx"),
                    nb::arg("rx"),
                    nb::arg("name"))

        .def("__eq__",
             &PositionalOffsets::operator==,
             DOC_PositionalOffsets(operator_eq),
             nb::arg("other"))
        .def_rw("name", &PositionalOffsets::name, DOC_PositionalOffsets(name))
        .def_rw("x", &PositionalOffsets::x, DOC_PositionalOffsets(x))
        .def_rw("y", &PositionalOffsets::y, DOC_PositionalOffsets(y))
        .def_rw("z", &PositionalOffsets::z, DOC_PositionalOffsets(z))
        .def_rw("yaw", &PositionalOffsets::yaw, DOC_PositionalOffsets(yaw))
        .def_rw("pitch", &PositionalOffsets::pitch, DOC_PositionalOffsets(pitch))
        .def_rw("roll", &PositionalOffsets::roll, DOC_PositionalOffsets(roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(PositionalOffsets)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(PositionalOffsets)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(PositionalOffsets)
        // end PositionalOffsets
        ;
}
