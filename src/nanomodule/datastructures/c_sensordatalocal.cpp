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

void init_c_sensordatalocal(nb::module_& m)
{

    nb::class_<SensordataLocal, Sensordata>(
        m,
        "SensordataLocal",
        DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal))
        .def(nb::init<const SensordataUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLocal,
                 SensordataLocal),
             nb::arg("sensordatautm"))
        .def(nb::init<const Sensordata&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLocal,
                 SensordataLocal_2),
             nb::arg("sensordata"),
             nb::arg("northing"),
             nb::arg("easting"))
    .def(nb::init<double, double, float, float, float, float, float>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLocal,
                 SensordataLocal_3),
             nb::arg("northing") = 0,
             nb::arg("easting")  = 0,
             nb::arg("depth")    = 0.0f,
             nb::arg("heave")    = 0.0f,
             nb::arg("heading")  = 0.0f,
             nb::arg("pitch")    = 0.0f,
             nb::arg("roll")     = 0.0f)
        .def("__eq__",
             &SensordataLocal::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal, operator_eq),
             nb::arg("other"))
        .def_rw(
            "northing",
            &SensordataLocal::northing,
            DOC(themachinethatgoesping, navigation, datastructures, SensordataLocal, northing))
        .def_rw(
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
