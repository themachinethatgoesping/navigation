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

void init_c_nmea_vlw(py::module& m)
{

    py::class_<NMEA_VLW, NMEA_Base>(
        m, "NMEA_VLW", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VLW))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VLW, NMEA_VLW),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // VLW attributes
        .def("get_total_water_distance_nautical_miles",
             &NMEA_VLW::get_total_water_distance_nautical_miles,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VLW,
                 get_total_water_distance_nautical_miles))
        .def("get_trip_water_distance_nautical_miles",
             &NMEA_VLW::get_trip_water_distance_nautical_miles,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VLW,
                 get_trip_water_distance_nautical_miles))
        .def("get_total_ground_distance_nautical_miles",
             &NMEA_VLW::get_total_ground_distance_nautical_miles,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VLW,
                 get_total_ground_distance_nautical_miles))
        .def("get_trip_ground_distance_nautical_miles",
             &NMEA_VLW::get_trip_ground_distance_nautical_miles,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VLW,
                 get_trip_ground_distance_nautical_miles))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_VLW)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_VLW)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_VLW)
        // end GeoLocationLatLon
        ;
}
