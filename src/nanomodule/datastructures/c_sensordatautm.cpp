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

void init_c_sensordatautm(nb::module_& m)
{

    nb::class_<SensordataUTM, SensordataLocal>(
        m, "SensordataUTM", DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM))
        .def(
            nb::init<const Sensordata&, double, double, int, bool>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_2),
            nb::arg("sensordatalatlon"),
            nb::arg("northing"),
            nb::arg("easting"),
            nb::arg("utm_zone"),
            nb::arg("northern_hemisphere"))
        .def(
            nb::init<const SensordataLocal&, int, bool>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_3),
            nb::arg("sensordata_local"),
            nb::arg("utm_zone"),
            nb::arg("northern_hemisphere"))
        .def(
            nb::init<const SensordataLatLon&, int>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_4),
            nb::arg("sensordatalatlon"),
            nb::arg("setutm_zone") = -1)
        .def(
            nb::init<double, double, int, bool, float, float, float, float, float>(),
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, SensordataUTM_5),
            nb::arg("northing")                = 0,
            nb::arg("easting")                 = 0,
            nb::arg("utm_zone")                = 0,
            nb::arg("northern_hemisphere") = true,
            nb::arg("depth")                   = 0.0f,
            nb::arg("heave")                   = 0.0f,
            nb::arg("heading")                 = 0.0f,
            nb::arg("pitch")                   = 0.0f,
            nb::arg("roll")                    = 0.0f)
        .def("__eq__",
             &SensordataUTM::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, operator_eq),
             nb::arg("other"))
        .def_rw(
            "utm_zone",
            &SensordataUTM::utm_zone,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, utm_zone))
        .def_rw("northern_hemisphere",
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
            nb::arg("sensordata_utm"))
        .def_static(
            "from_sensordata",
            &SensordataUTM::from_sensordata,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataUTM, from_sensordata),
            nb::arg("sensordatalatlon"),
            nb::arg("setutm_zone") = -1)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataUTM)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataUTM)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataUTM)
        // end SensordataUTM
        ;
}
