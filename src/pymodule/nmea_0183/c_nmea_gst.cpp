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

void init_c_nmea_gst(py::module& m)
{

    py::class_<NMEA_GST, NMEA_Base>(
        m, "NMEA_GST", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GST))
        .def(py::init<NMEA_Base, bool>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GST, NMEA_GST),
             py::arg("nmea_base"),
             py::arg("check") = true)

        // GST attributes
        .def("get_utc_time_string",
             &NMEA_GST::get_utc_time_string,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GST, get_utc_time_string))
        .def("get_psuedorange_rms",
             &NMEA_GST::get_psuedorange_rms,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GST, get_psuedorange_rms))
        .def("get_semimajor_error",
             &NMEA_GST::get_semimajor_error,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GST, get_semimajor_error))
        .def("get_semiminor_error",
             &NMEA_GST::get_semiminor_error,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_GST, get_semiminor_error))
        .def("get_semimajor_error_orientation",
             &NMEA_GST::get_semimajor_error_orientation,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GST,
                 get_semimajor_error_orientation))
        .def("get_latitude_error_deviation",
             &NMEA_GST::get_latitude_error_deviation,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GST,
                 get_latitude_error_deviation))
        .def("get_longitude_error_deviation",
             &NMEA_GST::get_longitude_error_deviation,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GST,
                 get_longitude_error_deviation))
        .def("get_altitude_error_deviation",
             &NMEA_GST::get_altitude_error_deviation,
             DOC(themachinethatgoesping,
                 navigation,
                 nmea_0183,
                 NMEA_GST,
                 get_altitude_error_deviation))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_GST)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_GST)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_GST)
        // end GeoLocationLatLon
        ;
}
