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

void init_c_nmea_zda(nb::module_& m)
{

    nb::class_<NMEA_ZDA, NMEA_Base>(
        m, "NMEA_ZDA", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA))
        .def(nb::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, NMEA_ZDA),
             nb::arg("nmea_base"),
             nb::arg("check") = true)

        // ZDA attributes
        .def("get_utc_time_string",
             &NMEA_ZDA::get_utc_time_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, get_utc_time_string))
        .def("get_day",
             &NMEA_ZDA::get_day,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, get_day))
        .def("get_month",
             &NMEA_ZDA::get_month,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, get_month))
        .def("get_year",
             &NMEA_ZDA::get_year,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, get_year))
        .def("get_local_zone_hours",
             &NMEA_ZDA::get_local_zone_hours,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, get_local_zone_hours))
        .def("get_local_zone_minutes",
             &NMEA_ZDA::get_local_zone_minutes,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, get_local_zone_minutes))

        // Converted attributes
        .def("to_timestamp",
             &NMEA_ZDA::to_timestamp,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, to_timestamp))
        .def("to_date_string",
             &NMEA_ZDA::to_date_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_ZDA, to_date_string),
             nb::arg("format") = "%z__%d-%m-%Y__%H:%M:%S")

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_ZDA)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_ZDA)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_ZDA)
        // end GeolocationLatLon
        ;
}
