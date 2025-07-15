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

void init_c_sensordatalocal(py::module& m)
{

    py::class_<SensordataLocal, Sensordata>(
        m,
        "SensordataLocal",
        DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal))
        .def(py::init<const SensordataUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLocal,
                 SensordataLocal),
             py::arg("sensordatautm"))
        .def(py::init<const Sensordata&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLocal,
                 SensordataLocal_2),
             py::arg("sensordata"),
             py::arg("northing"),
             py::arg("easting"))
        .def(py::init<double, double, double, double, double, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLocal,
                 SensordataLocal_3),
             py::arg("northing") = 0,
             py::arg("easting")  = 0,
             py::arg("depth")    = 0,
             py::arg("heave")    = 0,
             py::arg("heading")  = 0,
             py::arg("pitch")    = 0,
             py::arg("roll")     = 0)
        .def("__eq__",
             &SensordataLocal::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal, operator_eq),
             py::arg("other"))
        .def_readwrite(
            "northing",
            &SensordataLocal::northing,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal, northing))
        .def_readwrite(
            "easting",
            &SensordataLocal::easting,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal, easting))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataLocal)
        // end SensordataLocal
        ;
}
