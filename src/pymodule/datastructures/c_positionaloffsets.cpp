// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

#define DOC_PositionalOffsets(ARG)                                                                 \
    DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets, ARG)

void init_c_positionaloffsets(py::module& m)
{

    py::classh<PositionalOffsets>(
        m,
        "PositionalOffsets",
        DOC(themachinethatgoesping, navigation, datastructures, PositionalOffsets))
        .def(py::init<std::string, double, double, double, double, double, double, bool>(),
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
             py::arg("roll")  = 0,
             py::arg("ypr_offsets_applied") = false)
        .def_static("from_txrx",
                    &PositionalOffsets::from_txrx,
                    DOC_PositionalOffsets(from_txrx),
                    py::arg("tx"),
                    py::arg("rx"),
                    py::arg("name"))

        .def("__eq__",
             &PositionalOffsets::operator==,
             DOC_PositionalOffsets(operator_eq),
             py::arg("other"))
        .def_readwrite("name", &PositionalOffsets::name, DOC_PositionalOffsets(name))
        .def_readwrite("x", &PositionalOffsets::x, DOC_PositionalOffsets(x))
        .def_readwrite("y", &PositionalOffsets::y, DOC_PositionalOffsets(y))
        .def_readwrite("z", &PositionalOffsets::z, DOC_PositionalOffsets(z))
        .def_readwrite("yaw", &PositionalOffsets::yaw, DOC_PositionalOffsets(yaw))
        .def_readwrite("pitch", &PositionalOffsets::pitch, DOC_PositionalOffsets(pitch))
        .def_readwrite("roll", &PositionalOffsets::roll, DOC_PositionalOffsets(roll))
        .def_readwrite("ypr_offsets_applied",
                       &PositionalOffsets::ypr_offsets_applied,
                       "if true, the yaw/pitch/roll offsets are already applied to the associated "
                       "sensor data (e.g. Kongsberg .all logs the attitude/heading already "
                       "corrected for the sensor mounting offsets). If so, the SensorConfiguration "
                       "does not re-apply them.")
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(PositionalOffsets)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(PositionalOffsets)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(PositionalOffsets)
        // end PositionalOffsets
        ;
}
