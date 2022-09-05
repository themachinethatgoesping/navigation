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

void init_c_nmea_vlw(py::module& m)
{

    py::class_<NMEA_VLW, NMEABase>(
        m, "NMEA_VLW", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_VLW))
        .def(py::init<NMEABase, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VLW,
                 NMEA_VLW),
             py::arg("nmeabase"),
             py::arg("check") = true)

        // VLW attributes
        .def_property_readonly("total_water_distance_nautical_miles",
             &NMEA_VLW::total_water_distance_nautical_miles,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_VLW,
                 total_water_distance_nautical_miles))
        .def_property_readonly("trip_water_distance_nautical_miles",
                &NMEA_VLW::trip_water_distance_nautical_miles,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_VLW,
                    trip_water_distance_nautical_miles))
        .def_property_readonly("total_ground_distance_nautical_miles",
                &NMEA_VLW::total_ground_distance_nautical_miles,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_VLW,
                    total_ground_distance_nautical_miles))
        .def_property_readonly("trip_ground_distance_nautical_miles",
                &NMEA_VLW::trip_ground_distance_nautical_miles,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_VLW,
                    trip_ground_distance_nautical_miles))

        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_VLW)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_VLW)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_VLW)
        // end GeoLocationLatLon
        ;
}
