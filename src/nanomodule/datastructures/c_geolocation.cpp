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

void init_c_geolocation(nb::module_& m)
{

    nb::class_<Geolocation>(
        m, "Geolocation", DOC(themachinethatgoesping, navigation, datastructures, Geolocation))
        .def(nb::init<GeolocationLatLon>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation),
             nb::arg("geolocation_latlon"))
        .def(nb::init<GeolocationLocal>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation),
             nb::arg("geolocation_local"))
        .def(nb::init<GeolocationUTM>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation),
             nb::arg("geolocation_utm"))
        .def(nb::init<float, float, float, float>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation_2),
             nb::arg("z")     = 0,
             nb::arg("yaw")   = 0,
             nb::arg("pitch") = 0,
             nb::arg("roll")  = 0)
        .def(nb::init<float, themachinethatgoesping::tools::rotationfunctions::Rotation<float>>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation_3),
             nb::arg("z"),
             nb::arg("rotation"))
        .def("__eq__",
             &Geolocation::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, operator_eq),
             nb::arg("other"))
        .def_rw("z",
                       &Geolocation::z,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, z))
        .def_rw("rotation",
                       &Geolocation::rotation,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, rotation))
        .def_prop_rw("yaw",
                       &Geolocation::yaw,
                       &Geolocation::set_yaw,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, yaw))
        .def_prop_rw("pitch",
                       &Geolocation::pitch,
                       &Geolocation::set_pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, pitch))
        .def_prop_rw("roll",
                       &Geolocation::roll,
                       &Geolocation::set_roll,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, roll))
        .def("set_ypr",
                       &Geolocation::set_ypr,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, set_ypr),
                       nb::arg("yaw"),
                       nb::arg("pitch"),
                       nb::arg("roll"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(Geolocation)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(Geolocation)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(Geolocation)
        // end Geolocation
        ;
}
