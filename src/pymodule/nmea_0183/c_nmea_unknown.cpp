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

void init_c_nmea_unknown(py::module& m)
{

    py::class_<NMEA_Unknown, NMEA_Base>(
        m, "NMEA_Unknown", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Unknown))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_Unknown,
                 NMEA_Unknown),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // access the parsed fields
        .def("get_field",
             &NMEA_Base::get_field,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_field),
             py::arg("index"))
        .def("get_field_as_int",
             &NMEA_Base::get_field_as_int,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_field_as_int),
             py::arg("index"))
        .def("get_field_as_double",
             &NMEA_Base::get_field_as_double,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_field_as_double),
             py::arg("index"))
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_Unknown)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_Unknown)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_Unknown)
        // end GeoLocationLatLon
        ;
}
