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

void init_c_nmea_rmc(py::module& m)
{

    py::classh<NMEA_RMC, NMEA_Base>(
        m, "NMEA_RMC", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, NMEA_RMC),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // RMC attributes
        .def("get_utc_time_string",
             &NMEA_RMC::get_utc_time_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_utc_time_string))
        .def("get_status",
             &NMEA_RMC::get_status,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_status))
        .def("get_latitude",
             &NMEA_RMC::get_latitude,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_latitude))
        .def("get_longitude",
             &NMEA_RMC::get_longitude,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_longitude))
        .def("get_speed_over_ground_knots",
             &NMEA_RMC::get_speed_over_ground_knots,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_RMC,
                 get_speed_over_ground_knots))
        .def("get_course_over_ground_degrees_true",
             &NMEA_RMC::get_course_over_ground_degrees_true,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_RMC,
                 get_course_over_ground_degrees_true))
        .def("get_utc_date_string",
             &NMEA_RMC::get_utc_date_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_utc_date_string))
        .def("get_magnetic_variation",
             &NMEA_RMC::get_magnetic_variation,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_magnetic_variation))
        .def("get_mode",
             &NMEA_RMC::get_mode,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_mode))
        .def("get_mode_explained",
             &NMEA_RMC::get_mode_explained,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, get_mode_explained))

        // Converted attributes
        .def("to_timestamp",
             &NMEA_RMC::to_timestamp,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, to_timestamp))
        .def("to_date_string",
             &NMEA_RMC::to_date_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC, to_date_string),
             py::arg("format") = "%z__%d-%m-%Y__%H:%M:%S")

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_RMC)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_RMC)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_RMC)
        // end GeolocationLatLon
        ;
}
