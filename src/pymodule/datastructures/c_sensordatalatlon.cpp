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

void init_c_sensordatalatlon(py::module& m)
{

    py::class_<SensorDataLatLon, SensorData>(
        m,
        "SensorDataLatLon",
        DOC(themachinethatgoesping, navigation, datastructures, SensorDataLatLon))
        .def(py::init<const SensorData&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorDataLatLon,
                 SensorDataLatLon_2),
             py::arg("sensordata"),
             py::arg("latitude"),
             py::arg("longitude"))
        .def(py::init<const SensorDataUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorDataLatLon,
                 SensorDataLatLon_3),
             py::arg("sensordata_utm"))
        .def(py::init<double, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorDataLatLon,
                 SensorDataLatLon_4),
             py::arg("latitude")  = 0,
             py::arg("longitude") = 0,
             py::arg("depth")     = 0,
             py::arg("heave")     = 0,
             py::arg("heading")   = 0,
             py::arg("pitch")     = 0,
             py::arg("roll")      = 0)
        .def("__eq__",
             &SensorDataLatLon::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataLatLon, operator_eq),
             py::arg("other"))
        .def_readwrite("latitude", &SensorDataLatLon::latitude)
        .def_readwrite("longitude", &SensorDataLatLon::longitude)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataLatLon)
        // end SensorDataLatLon
        ;
}
