// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::nmea_0183;

void init_c_nmeabase(py::module& m)
{

    py::class_<NMEABase>(
        m, "NMEABase", DOC(themachinethatgoesping, navigation, nmea_0183, NMEABase))
        .def(py::init<>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEABase,
                 NMEABase))
        .def(py::init<std::string>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEABase,
                 NMEABase_2),
             py::arg("sentence"))
        .def("__eq__",
             &NMEABase::operator==,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEABase, operator_eq),
             py::arg("other"))
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEABase)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEABase)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEABase)
        // end GeoLocationLatLon
        ;
}
