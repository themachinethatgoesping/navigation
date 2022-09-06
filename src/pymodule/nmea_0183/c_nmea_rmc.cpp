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

void init_c_nmea_rmc(py::module& m)
{

    py::class_<NMEA_RMC, NMEA_Base>(
        m, "NMEA_RMC", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_RMC))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_RMC,
                 NMEA_RMC),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // RMC attributes
        .def_property_readonly("coordinated_universal_time",
             &NMEA_RMC::coordinated_universal_time,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_RMC,
                 coordinated_universal_time))
        .def_property_readonly("status",
                &NMEA_RMC::status,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    status))
        .def_property_readonly("latitude",
                &NMEA_RMC::latitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    latitude))
        .def_property_readonly("longitude",
                &NMEA_RMC::longitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    longitude))
        .def_property_readonly("speed_over_ground_knots",
                &NMEA_RMC::speed_over_ground_knots,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    speed_over_ground_knots))
        .def_property_readonly("course_over_ground_degrees_true",
                &NMEA_RMC::course_over_ground_degrees_true,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    course_over_ground_degrees_true))
        .def_property_readonly("date",
                &NMEA_RMC::date,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    date))
        .def_property_readonly("magnetic_variation",
                &NMEA_RMC::magnetic_variation,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    magnetic_variation))
        .def_property_readonly("magnetic_variation",
                &NMEA_RMC::magnetic_variation,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    magnetic_variation))
        .def_property_readonly("mode",
                &NMEA_RMC::mode,             DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    mode))  
        .def_property_readonly("mode_explained",
                &NMEA_RMC::mode,             DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    mode))  
                 
        
        // Converted attributes
        .def("to_timestamp",
                &NMEA_RMC::to_timestamp,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    to_timestamp))
        .def("to_date_string",
                &NMEA_RMC::to_date_string,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_RMC,
                    to_date_string),
                    py::arg("format") ="%z__%d-%m-%Y__%H:%M:%S")
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_RMC)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_RMC)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_RMC)
        // end GeoLocationLatLon
        ;
}
