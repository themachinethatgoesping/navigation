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

void init_c_sensordatalatlon(nb::module_& m)
{

    nb::class_<SensordataLatLon, Sensordata>(
        m,
        "SensordataLatLon",
        DOC(themachinethatgoesping, navigation, datastructures, SensordataLatLon))
        .def(nb::init<const Sensordata&, double, double>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLatLon,
                 SensordataLatLon_2),
             nb::arg("sensordata"),
             nb::arg("latitude"),
             nb::arg("longitude"))
        .def(nb::init<const SensordataUTM&>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLatLon,
                 SensordataLatLon_3),
             nb::arg("sensordata_utm"))
    .def(nb::init<double, double, float, float, float, float, float>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensordataLatLon,
                 SensordataLatLon_4),
             nb::arg("latitude")  = 0,
             nb::arg("longitude") = 0,
             nb::arg("depth")     = 0.0f,
             nb::arg("heave")     = 0.0f,
             nb::arg("heading")   = 0.0f,
             nb::arg("pitch")     = 0.0f,
             nb::arg("roll")      = 0.0f)
        .def("__eq__",
             &SensordataLatLon::operator==,
             DOC(themachinethatgoesping, navigation, datastructures, SensordataLatLon, operator_eq),
             nb::arg("other"))
        .def_rw("latitude", &SensordataLatLon::latitude)
        .def_rw("longitude", &SensordataLatLon::longitude)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensordataLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensordataLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensordataLatLon)
        // end SensordataLatLon
        ;
}
