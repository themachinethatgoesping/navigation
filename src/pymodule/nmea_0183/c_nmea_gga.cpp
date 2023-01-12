// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::nmea_0183;

void init_c_nmea_gga(py::module& m)
{

    py::class_<NMEA_GGA, NMEA_Base>(
        m, "NMEA_GGA", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, NMEA_GGA),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // GGA attributes
        .def("get_utc_time_string",
             &NMEA_GGA::get_utc_time_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_utc_time_string))
        .def("get_latitude",
             &NMEA_GGA::get_latitude,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_latitude))
        .def("get_longitude",
             &NMEA_GGA::get_longitude,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_longitude))
        .def("get_quality",
             &NMEA_GGA::get_quality,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_quality))
        .def("get_quality_explained",
             &NMEA_GGA::get_quality_explained,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_quality_explained))
        .def("get_number_of_satellites",
             &NMEA_GGA::get_number_of_satellites,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_number_of_satellites))
        .def("get_horizontal_dilution_of_precision",
             &NMEA_GGA::get_horizontal_dilution_of_precision,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GGA,
                 get_horizontal_dilution_of_precision))
        .def("get_altitude",
             &NMEA_GGA::get_altitude,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_altitude))
        .def("get_geoidal_separation",
             &NMEA_GGA::get_geoidal_separation,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GGA, get_geoidal_separation))
        .def("get_age_of_differential_gps_data",
             &NMEA_GGA::get_age_of_differential_gps_data,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GGA,
                 get_age_of_differential_gps_data))
        .def("get_differential_reference_station_id",
             &NMEA_GGA::get_differential_reference_station_id,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GGA,
                 get_differential_reference_station_id))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_GGA)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_GGA)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_GGA)
        // end GeoLocationLatLon
        ;
}
