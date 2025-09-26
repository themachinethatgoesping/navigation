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
             nb::arg("z")     = 0.0f,
             nb::arg("yaw")   = 0.0f,
             nb::arg("pitch") = 0.0f,
             nb::arg("roll")  = 0.0f)
        .def("__eq__",
             &Geolocation::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, operator_eq),
             nb::arg("other"))
        .def_rw("z",
                       &Geolocation::z,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, z))
        .def_rw("yaw",
                       &Geolocation::yaw,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, yaw))
        .def_rw("pitch",
                       &Geolocation::pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, pitch))
        .def_rw("roll",
                       &Geolocation::roll,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, roll))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(Geolocation)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(Geolocation)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(Geolocation)
        // end Geolocation
        ;
}
