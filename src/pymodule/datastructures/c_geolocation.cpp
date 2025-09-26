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

void init_c_geolocation(py::module& m)
{

    py::classh<Geolocation>(
        m, "Geolocation", DOC(themachinethatgoesping, navigation, datastructures, Geolocation))
        .def(py::init<GeolocationLatLon>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation),
             py::arg("geolocation_latlon"))
        .def(py::init<GeolocationLocal>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation),
             py::arg("geolocation_local"))
        .def(py::init<GeolocationUTM>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation),
             py::arg("geolocation_utm"))
        .def(py::init<float, float, float, float>(),
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, Geolocation_2),
             py::arg("z")     = 0,
             py::arg("yaw")   = 0,
             py::arg("pitch") = 0,
             py::arg("roll")  = 0)
        .def("__eq__",
             &Geolocation::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, Geolocation, operator_eq),
             py::arg("other"))
        .def_readwrite("z",
                       &Geolocation::z,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, z))
        .def_readwrite("yaw",
                       &Geolocation::yaw,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, yaw))
        .def_readwrite("pitch",
                       &Geolocation::pitch,
                       DOC(themachinethatgoesping, navigation, datastructures, Geolocation, pitch))
        .def_readwrite("roll",
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
