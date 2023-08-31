// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
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

void init_c_sensordatalocal(py::module& m)
{

    py::class_<SensorDataLocal, SensorData>(
        m,
        "SensorDataLocal",
        DOC(themachinethatgoesping, navigation, datastructures, SensorDataLocal))
        .def(py::init<const SensorDataUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorDataLocal,
                 SensorDataLocal),
             py::arg("sensordatautm"))
        .def(py::init<const SensorData&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorDataLocal,
                 SensorDataLocal_2),
             py::arg("sensordata"),
             py::arg("northing"),
             py::arg("easting"))
        .def(py::init<double, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorDataLocal,
                 SensorDataLocal_3),
             py::arg("northing") = 0,
             py::arg("easting")  = 0,
             py::arg("depth")    = 0,
             py::arg("heave")    = 0,
             py::arg("heading")  = 0,
             py::arg("pitch")    = 0,
             py::arg("roll")     = 0)
        .def("__eq__",
             &SensorDataLocal::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensorDataLocal, operator_eq),
             py::arg("other"))
        .def_readwrite(
            "northing",
            &SensorDataLocal::northing,
            DOC(themachinethatgoesping, navigation, datastructures, SensorDataLocal, northing))
        .def_readwrite(
            "easting",
            &SensorDataLocal::easting,
            DOC(themachinethatgoesping, navigation, datastructures, SensorDataLocal, easting))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorDataLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorDataLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorDataLocal)
        // end SensorDataLocal
        ;
}
