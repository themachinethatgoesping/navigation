// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::datastructures;

void init_c_sensordatautm(py::module& m)
{

    py::class_<SensorDataUTM, SensorDataLocal>(
        m, "SensorDataUTM", DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM))
        .def(py::init<const SensorData&, double, double, int, bool>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, SensorDataUTM_2),
             py::arg("sensordatalatlon"),
             py::arg("northing"),
             py::arg("easting"),
             py::arg("utm_zone"),
             py::arg("utm_northern_hemisphere"))
        .def(py::init<const SensorDataLocal&, int, bool>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, SensorDataUTM_3),
             py::arg("sensordata_local"),
             py::arg("utm_zone"),
             py::arg("utm_northern_hemisphere"))
        .def(py::init<const SensorDataLatLon&, int>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, SensorDataUTM_4),
             py::arg("sensordatalatlon"),
             py::arg("setutm_zone") = -1)
        .def(py::init<double, double, int, bool, double, double, double, double, double>(),
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, SensorDataUTM_5),
             py::arg("northing")            = 0,
             py::arg("easting")             = 0,
             py::arg("utm_zone")                = 0,
             py::arg("utm_northern_hemisphere") = true,
             py::arg("depth")                   = 0,
             py::arg("heave")             = 0,
             py::arg("heading")         = 0,
             py::arg("pitch")               = 0,
             py::arg("roll")                = 0)
        .def("__eq__",
             &SensorDataUTM::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, operator_eq),
             py::arg("rhs"))
        .def_readwrite("utm_zone",
                       &SensorDataUTM::utm_zone,
                       DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, utm_zone))
        .def_readwrite("utm_northern_hemisphere",
                       &SensorDataUTM::utm_northern_hemisphere,
                       DOC(themachinethatgoesping,
                           navigation,
                           datastructures,
                           SensorDataUTM,
                           utm_northern_hemisphere))
        // static functions
        .def_static("to_sensordata",
                    &SensorDataUTM::to_sensordata,
                    DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, to_sensordata),
                    py::arg("sensordata_utm"))
        .def_static(
            "from_sensordata",
            &SensorDataUTM::from_sensordata,
            DOC(themachinethatgoesping, navigation, datastructures, SensorDataUTM, from_sensordata),
            py::arg("sensordatalatlon"),
            py::arg("setutm_zone") = -1)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataUTM)
        // end SensorDataUTM
        ;
}
