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

void init_c_sensordata(py::module& m)
{

    py::classh<Sensordata>(
        m, "Sensordata", DOC(themachinethatgoesping, navigation, datastructures, Sensordata))
        .def(py::init<SensordataLatLon>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata))
        .def(py::init<SensordataLocal>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata))
        .def(py::init<SensordataUTM>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata))
        .def(py::init<double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata_2),
             py::arg("depth")   = 0,
             py::arg("heave")   = 0,
             py::arg("heading") = 0,
             py::arg("pitch")   = 0,
             py::arg("roll")    = 0)
        .def("__eq__",
             &Sensordata::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, operator_eq),
             py::arg("other"))
        .def_readwrite("depth",
                       &Sensordata::depth,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, depth))
        .def_readwrite("heave",
                       &Sensordata::heave,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, heave))
        .def_readwrite("heading",
                       &Sensordata::heading,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, heading))
        .def_readwrite("pitch",
                       &Sensordata::pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, pitch))
        .def_readwrite("roll",
                       &Sensordata::roll,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(Sensordata)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(Sensordata)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(Sensordata)
        // end Sensordata
        ;
}
