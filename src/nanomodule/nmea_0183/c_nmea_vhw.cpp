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

void init_c_nmea_vhw(nb::module_& m)
{

    nb::class_<NMEA_VHW, NMEA_Base>(
        m, "NMEA_VHW", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VHW))
        .def(nb::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VHW, NMEA_VHW),
             nb::arg("nmea_base"),
             nb::arg("check") = true)

        // VHW attributes
        .def("get_vessel_heading_true",
             &NMEA_VHW::get_vessel_heading_true,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VHW, get_vessel_heading_true))
        .def("get_vessel_heading_magnetic",
             &NMEA_VHW::get_vessel_heading_magnetic,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VHW,
                 get_vessel_heading_magnetic))
        .def("get_speed_over_water_knots",
             &NMEA_VHW::get_speed_over_water_knots,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VHW,
                 get_speed_over_water_knots))
        .def("get_speed_over_water_kmh",
             &NMEA_VHW::get_speed_over_water_kmh,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VHW, get_speed_over_water_kmh))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_VHW)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_VHW)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_VHW)
        // end GeolocationLatLon
        ;
}
