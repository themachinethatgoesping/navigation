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

void init_c_sensordata(nb::module_& m)
{

    nb::class_<Sensordata>(
        m, "Sensordata", DOC(themachinethatgoesping, navigation, datastructures, Sensordata))
        .def(nb::init<SensordataLatLon>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata))
        .def(nb::init<SensordataLocal>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata))
        .def(nb::init<SensordataUTM>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata))
        .def(nb::init<double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata_2),
             nb::arg("depth")   = 0,
             nb::arg("heave")   = 0,
             nb::arg("heading") = 0,
             nb::arg("pitch")   = 0,
             nb::arg("roll")    = 0)
        .def("__eq__",
             &Sensordata::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, operator_eq),
             nb::arg("other"))
        .def_rw("depth",
                       &Sensordata::depth,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, depth))
        .def_rw("heave",
                       &Sensordata::heave,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, heave))
        .def_rw("heading",
                       &Sensordata::heading,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, heading))
        .def_rw("pitch",
                       &Sensordata::pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, pitch))
        .def_rw("roll",
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
