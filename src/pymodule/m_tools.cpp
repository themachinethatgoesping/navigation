// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/tools.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/enumhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::tools;

void init_m_tools(py::module& m)
{

    auto m_tools =
        m.def_submodule("tools", "Convinient functions for converting latlon and utm strings.");

    py::enum_<t_latlon_format>(
        m_tools, "t_latlon_format", DOC(themachinethatgoesping, navigation, tools, t_latlon_format))
        .value("degrees", t_latlon_format::degrees)
        .value("minutes", t_latlon_format::minutes)
        .value("seconds", t_latlon_format::seconds)
        .export_values()
        // pybind enum helpers
        __PYENUM_FROM_STRING__(t_latlon_format)
        //
        ;

    py::implicitly_convertible<std::string, t_latlon_format>();

    m_tools.def("latitude_to_string",
                &latitude_to_string,
                DOC(themachinethatgoesping, navigation, tools, latitude_to_string),
                py::arg("latitude"),
                py::arg("format")     = t_latlon_format::minutes,
                py::arg("precission") = 6);

    m_tools.def("longitude_to_string",
                &longitude_to_string,
                DOC(themachinethatgoesping, navigation, tools, longitude_to_string),
                py::arg("longitude"),
                py::arg("format")     = t_latlon_format::minutes,
                py::arg("precission") = 6);
}
