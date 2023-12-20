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

void init_c_sensordatautm(py::module& m)
{

    py::class_<SensordataUTM, SensordataLocal>(
        m, "SensordataUTM", DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM))
        .def(
            py::init<const Sensordata&, double, double, int, bool>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_2),
            py::arg("sensordatalatlon"),
            py::arg("northing"),
            py::arg("easting"),
            py::arg("utm_zone"),
            py::arg("northern_hemisphere"))
        .def(
            py::init<const SensordataLocal&, int, bool>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_3),
            py::arg("sensordata_local"),
            py::arg("utm_zone"),
            py::arg("northern_hemisphere"))
        .def(
            py::init<const SensordataLatLon&, int>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_4),
            py::arg("sensordatalatlon"),
            py::arg("setutm_zone") = -1)
        .def(
            py::init<double, double, int, bool, double, double, double, double, double>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_5),
            py::arg("northing")                = 0,
            py::arg("easting")                 = 0,
            py::arg("utm_zone")                = 0,
            py::arg("northern_hemisphere") = true,
            py::arg("depth")                   = 0,
            py::arg("heave")                   = 0,
            py::arg("heading")                 = 0,
            py::arg("pitch")                   = 0,
            py::arg("roll")                    = 0)
        .def("__eq__",
             &SensordataUTM::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, operator_eq),
             py::arg("other"))
        .def_readwrite(
            "utm_zone",
            &SensordataUTM::utm_zone,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, utm_zone))
        .def_readwrite("northern_hemisphere",
                       &SensordataUTM::northern_hemisphere,
                       DOC(themachinethatgoesping,
                           navigation,
                           datastructures,
                           SensordataUTM,
                           northern_hemisphere))
        // static functions
        .def_static(
            "to_sensordata",
            &SensordataUTM::to_sensordata,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, to_sensordata),
            py::arg("sensordata_utm"))
        .def_static(
            "from_sensordata",
            &SensordataUTM::from_sensordata,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, from_sensordata),
            py::arg("sensordatalatlon"),
            py::arg("setutm_zone") = -1)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataUTM)
        // end SensordataUTM
        ;
}
