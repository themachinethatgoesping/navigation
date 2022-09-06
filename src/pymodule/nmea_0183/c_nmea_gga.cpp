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

void init_c_nmea_gga(py::module& m)
{

    py::class_<NMEA_GGA, NMEA_Base>(
        m, "NMEA_GGA", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GGA,
                 NMEA_GGA),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // GGA attributes
        .def_property_readonly("coordinated_universal_time",
             &NMEA_GGA::coordinated_universal_time,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GGA,
                 coordinated_universal_time))
        .def_property_readonly("latitude",
                &NMEA_GGA::latitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    latitude))
        .def_property_readonly("longitude",
                &NMEA_GGA::longitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    longitude))
        .def_property_readonly("quality",
                &NMEA_GGA::quality,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    quality))
        .def_property_readonly("quality_explained",
                &NMEA_GGA::quality_explained,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    quality_explained))
        .def_property_readonly("number_of_satellites",
                &NMEA_GGA::number_of_satellites,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    number_of_satellites))
        .def_property_readonly("horizontal_dilution_of_precision",
                &NMEA_GGA::horizontal_dilution_of_precision,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    horizontal_dilution_of_precision))
        .def_property_readonly("altitude",
                &NMEA_GGA::altitude,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    altitude))
        .def_property_readonly("geoidal_separation",
                &NMEA_GGA::geoidal_separation,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    geoidal_separation))
        .def_property_readonly("age_of_differential_gps_data",
                &NMEA_GGA::age_of_differential_gps_data,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    age_of_differential_gps_data))
        .def_property_readonly("differential_reference_station_id",
                &NMEA_GGA::differential_reference_station_id,
                DOC(themachinethatgoesping,
                    navigation,
                    nmea_0183,
                    NMEA_GGA,
                    differential_reference_station_id))                    

        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_GGA)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_GGA)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_GGA)
        // end GeoLocationLatLon
        ;
}
