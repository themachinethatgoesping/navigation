// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation::nmea_0183;

void init_c_nmea_hdt(nb::module_& m)
{

    nb::class_<NMEA_HDT, NMEA_Base>(
        m, "NMEA_HDT", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_HDT))
        .def(nb::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_HDT, NMEA_HDT),
             nb::arg("nmea_base"),
             nb::arg("check") = true)

        // HDT attributes
        .def("get_heading_degrees_true",
             &NMEA_HDT::get_heading_degrees_true,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_HDT, get_heading_degrees_true))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_HDT)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_HDT)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_HDT)
        // end GeolocationLatLon
        ;
}
