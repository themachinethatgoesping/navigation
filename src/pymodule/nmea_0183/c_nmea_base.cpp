// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

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
        .def("get_sentence_type",
             &NMEA_Base::get_sentence_type,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_sentence_type))
        .def("get_sender_id",
             &NMEA_Base::get_sender_id,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_sender_id))
        .def("get_sentence_id",
             &NMEA_Base::get_sentence_id,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_sentence_id))
        .def("get_sentence",
             &NMEA_Base::get_sentence,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_sentence))

        // access the parsed fields
        .def("get_field",
             &NMEA_Base::get_field,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_field),
             py::arg("index"))
        .def("get_field_as_int",
             &NMEA_Base::get_field_as_int,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_field_as_int),
             py::arg("index"))
        .def("get_field_as_floattype",
             &NMEA_Base::get_field_as_floattype<double>,
             DOC(themachinethatgoesping, navigation, nmea_0183, NMEA_Base, get_field_as_floattype),
             py::arg("index"))

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NMEA_Base)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NMEA_Base)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NMEA_Base)
        // end GeoLocationLatLon
        ;
}
