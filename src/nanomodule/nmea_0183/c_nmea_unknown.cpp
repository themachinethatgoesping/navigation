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

void init_c_nmea_unknown(nb::module_& m)
{

    nb::class_<NMEA_Unknown, NMEA_Base>(
        m, "NMEA_Unknown", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Unknown))
        .def(nb::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Unknown, NMEA_Unknown),
             nb::arg("nmea_base"),
             nb::arg("check") = true)

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_Unknown)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_Unknown)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_Unknown)
        // end GeolocationLatLon
        ;
}
