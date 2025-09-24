// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::nmea_0183;

void init_c_nmea_unknown(py::module& m)
{

    py::classh<NMEA_Unknown, NMEA_Base>(
        m, "NMEA_Unknown", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Unknown))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Unknown, NMEA_Unknown),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_Unknown)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_Unknown)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_Unknown)
        // end GeolocationLatLon
        ;
}
