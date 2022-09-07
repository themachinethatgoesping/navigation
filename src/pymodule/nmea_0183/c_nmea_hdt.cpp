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

void init_c_nmea_hdt(py::module& m)
{

    py::class_<NMEA_HDT, NMEA_Base>(
        m, "NMEA_HDT", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_HDT))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_HDT,
                 NMEA_HDT),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // HDT attributes
        .def("get_heading_degrees_true",
                &NMEA_HDT::get_heading_degrees_true,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_HDT,
                    get_heading_degrees_true))
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_HDT)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_HDT)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_HDT)
        // end GeoLocationLatLon
        ;
}
