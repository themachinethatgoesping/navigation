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

void init_c_sensordatalatlon(py::module& m)
{

    py::classh<SensordataLatLon, Sensordata>(
        m,
        "SensordataLatLon",
        DOC(themachinethatgoesping, navigation, datastructures, SensordataLatLon))
        .def(py::init<const Sensordata&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLatLon,
                 SensordataLatLon_2),
             py::arg("sensordata"),
             py::arg("latitude"),
             py::arg("longitude"))
        .def(py::init<const SensordataUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLatLon,
                 SensordataLatLon_3),
             py::arg("sensordata_utm"))
        .def(py::init<double, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLatLon,
                 SensordataLatLon_4),
             py::arg("latitude")  = 0,
             py::arg("longitude") = 0,
             py::arg("depth")     = 0,
             py::arg("heave")     = 0,
             py::arg("heading")   = 0,
             py::arg("pitch")     = 0,
             py::arg("roll")      = 0)
        .def("__eq__",
             &SensordataLatLon::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensordataLatLon, operator_eq),
             py::arg("other"))
        .def_readwrite("latitude", &SensordataLatLon::latitude)
        .def_readwrite("longitude", &SensordataLatLon::longitude)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataLatLon)
        // end SensordataLatLon
        ;
}
