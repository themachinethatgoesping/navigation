// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/sensorpositionoffsets.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py        = pybind11;
using namespace themachinethatgoesping::navigation;

void init_c_sensorpositionoffsets(py::module& m)
{

    py::class_<SensorPositionOffsets>(
        m, "SensorPositionOffsets", DOC(themachinethatgoesping, navigation, SensorPositionOffsets))
        .def(
            py::init<double, double, double, double, double, double>(),
            DOC(themachinethatgoesping, navigation, SensorPositionOffsets, SensorPositionOffsets_2),
            py::arg("x")     = 0,
            py::arg("y")     = 0,
            py::arg("z")     = 0,
            py::arg("yaw")   = 0,
            py::arg("pitch") = 0,
            py::arg("roll")  = 0)
        .def("__eq__",
             &SensorPositionOffsets::operator==,
             DOC(themachinethatgoesping, navigation, SensorPositionOffsets, operator_eq), py::arg("rhs"))
        .def_readwrite("x",&SensorPositionOffsets::x)
        .def_readwrite("y",&SensorPositionOffsets::y)
        .def_readwrite("z",&SensorPositionOffsets::z)
        .def_readwrite("yaw",&SensorPositionOffsets::yaw)
        .def_readwrite("pitch",&SensorPositionOffsets::pitch)
        .def_readwrite("roll",&SensorPositionOffsets::roll)
        // .def("__call__",
        //      py::overload_cast<const std::vector<double>&>(&AkimaInterpolator::operator()),
        //      DOC(themachinethatgoesping,
        //          tools,
        //          vectorinterpolators,
        //          I_Interpolator,
        //          operator_call_2),
        //      py::arg("targets_x"))
        // .def("set_extrapolation_mode",
        //      &AkimaInterpolator::set_extrapolation_mode,
        //      DOC(themachinethatgoesping,
        //          tools,
        //          vectorinterpolators,
        //          I_Interpolator,
        //          set_extrapolation_mode),
        //      py::arg("extrapolation_mode"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorPositionOffsets)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorPositionOffsets)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorPositionOffsets)
        // end SensorPositionOffsets
        ;
}
