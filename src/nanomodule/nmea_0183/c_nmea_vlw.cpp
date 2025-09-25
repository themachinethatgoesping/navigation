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

void init_c_nmea_vlw(nb::module_& m)
{

    nb::class_<NMEA_VLW, NMEA_Base>(
        m, "NMEA_VLW", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VLW))
        .def(nb::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VLW, NMEA_VLW),
             nb::arg("nmea_base"),
             nb::arg("check") = true)

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
        // end GeolocationLatLon
        ;
}
