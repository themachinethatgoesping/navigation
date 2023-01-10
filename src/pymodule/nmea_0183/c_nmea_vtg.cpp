// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::nmea_0183;

void init_c_nmea_vtg(py::module& m)
{

    py::class_<NMEA_VTG, NMEA_Base>(
        m, "NMEA_VTG", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VTG))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VTG, NMEA_VTG),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // VTG attributes
        .def("get_course_over_ground_degrees_true",
             &NMEA_VTG::get_course_over_ground_degrees_true,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VTG,
                 get_course_over_ground_degrees_true))
        .def("get_course_over_ground_degrees_magnetic",
             &NMEA_VTG::get_course_over_ground_degrees_magnetic,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VTG,
                 get_course_over_ground_degrees_magnetic))
        .def("get_speed_over_ground_knots",
             &NMEA_VTG::get_speed_over_ground_knots,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VTG,
                 get_speed_over_ground_knots))
        .def(
            "get_speed_over_ground_kmh",
            &NMEA_VTG::get_speed_over_ground_kmh,
            DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VTG, get_speed_over_ground_kmh))
        .def("get_mode",
             &NMEA_VTG::get_mode,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VTG, get_mode))
        .def("get_mode_explained",
             &NMEA_VTG::get_mode_explained,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VTG, get_mode_explained))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_VTG)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_VTG)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_VTG)
        // end GeoLocationLatLon
        ;
}
