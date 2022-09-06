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

void init_c_nmea_base(py::module& m)
{

    py::class_<NMEA_Base>(
        m, "NMEA_Base", DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base))
        .def(py::init<>(), DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, NMEA_Base))
        .def(py::init<std::string>(),
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, NMEA_Base_2),
             py::arg("sentence"))
        .def("__eq__",
             &NMEA_Base::operator==,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, operator_eq),
             py::arg("other"))
        .def("get_type",
             &NMEA_Base::get_type,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_type))
        .def("get_sender",
             &NMEA_Base::get_sender,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_sender))
        .def("get_name",
             &NMEA_Base::get_name,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_name))
        .def("get_sentence",
             &NMEA_Base::get_sentence,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_sentence))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_Base)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_Base)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_Base)
        // end GeoLocationLatLon
        ;
}
