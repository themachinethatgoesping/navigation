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

    py::class_<NMEA_GLL, NMEA_Base>(
        m, "NMEA_GLL", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GLL))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GLL,
                 NMEA_GLL),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // GLL attributes
        .def("get_latitude",
                &NMEA_GLL::get_latitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    get_latitude))
        .def("get_longitude",
                &NMEA_GLL::get_longitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    get_longitude))
        .def("get_utc_time_string",
             &NMEA_GLL::get_utc_time_string,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GLL,
                 get_utc_time_string))
        .def("get_status",
                &NMEA_GLL::get_status,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    get_status))
        .def("get_mode",
                &NMEA_GLL::get_mode,             DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    get_mode))  
        .def("get_mode_explained",
                &NMEA_GLL::get_mode_explained,             DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GLL,
                    get_mode_explained))  
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_GLL)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_GLL)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_GLL)
        // end GeoLocationLatLon
        ;
}
