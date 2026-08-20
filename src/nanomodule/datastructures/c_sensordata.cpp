// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


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
        .def(nb::init<float, float, float, float, float>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata_2),
             nb::arg("depth")   = 0.0f,
             nb::arg("heave")   = 0.0f,
             nb::arg("heading") = 0.0f,
             nb::arg("pitch")   = 0.0f,
             nb::arg("roll")    = 0.0f)
        .def(nb::init<float, float, themachinethatgoesping::tools::rotationfunctions::Rotation<float>>(),
             DOC(themachinethatgoesping, navigation, datastructures, Sensordata, Sensordata_3),
             nb::arg("depth"),
             nb::arg("heave"),
             nb::arg("rotation"))
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
        .def_rw("rotation",
                       &Sensordata::rotation,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, rotation))
        .def_prop_rw("heading",
                       &Sensordata::heading,
                       &Sensordata::set_heading,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, heading))
        .def_prop_rw("pitch",
                       &Sensordata::pitch,
                       &Sensordata::set_pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, pitch))
        .def_prop_rw("roll",
                       &Sensordata::roll,
                       &Sensordata::set_roll,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, roll))
        .def("set_ypr",
                       &Sensordata::set_ypr,
                       DOC(themachinethatgoesping, navigation, datastructures, Sensordata, set_ypr),
                       nb::arg("heading"),
                       nb::arg("pitch"),
                       nb::arg("roll"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(Sensordata)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(Sensordata)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(Sensordata)
        // end Sensordata
        ;
}
