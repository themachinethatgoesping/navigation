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

void init_c_nmea_gll(py::module& m)
{

    py::class_<NMEA_GLL, NMEABase>(
        m, "NMEA_GLL", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GLL))
        .def(py::init<NMEABase, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GLL,
                 NMEA_GLL),
             py::arg("nmeabase"),
             py::arg("check") = true)

        // GLL attributes
        .def_property_readonly("latitude",
                &NMEA_GLL::latitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    latitude))
        .def_property_readonly("longitude",
                &NMEA_GLL::longitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    longitude))
        .def_property_readonly("coordinated_universal_time",
             &NMEA_GLL::coordinated_universal_time,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GLL,
                 coordinated_universal_time))
        .def_property_readonly("status",
                &NMEA_GLL::status,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    status))
        .def_property_readonly("mode",
                &NMEA_GLL::mode,             DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    mode))  
        .def_property_readonly("mode_explained",
                &NMEA_GLL::mode,             DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    mode))  
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_GLL)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_GLL)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_GLL)
        // end GeoLocationLatLon
        ;
}
