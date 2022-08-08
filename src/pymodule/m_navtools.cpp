// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/navtools.hpp"
#include <themachinethatgoesping/tools/pybind11_helpers/enumhelpers.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::navtools;

void init_m_navtools(py::module& m)
{

    auto m_navtools =
        m.def_submodule("navtools", "Convenient functions for converting latlon and utm strings.");

    py::enum_<t_latlon_format>(
        m_navtools, "t_latlon_format", DOC(themachinethatgoesping, navigation, navtools, t_latlon_format))
        .value("degrees", t_latlon_format::degrees)
        .value("minutes", t_latlon_format::minutes)
        .value("seconds", t_latlon_format::seconds)
        .export_values()
        // pybind enum helpers
        __PYENUM_FROM_STRING__(t_latlon_format)
        //
        ;

    py::implicitly_convertible<std::string, t_latlon_format>();

    m_navtools.def("latitude_to_string",
                &latitude_to_string,
                DOC(themachinethatgoesping, navigation, navtools, latitude_to_string),
                py::arg("latitude"),
                py::arg("format")     = t_latlon_format::minutes,
                py::arg("precision") = 6);

    m_navtools.def("longitude_to_string",
                &longitude_to_string,
                DOC(themachinethatgoesping, navigation, navtools, longitude_to_string),
                py::arg("longitude"),
                py::arg("format")     = t_latlon_format::minutes,
                py::arg("precision") = 6);

    //----- utm conversion -----
    // m_navtools.det("utm_to_latlon", py::overload_cast<const std::vector<double>&, const std::vector<double>&, int, bool>(&utm_to_latlon),
    //             DOC(themachinethatgoesping, navigation, navtools, utm_to_latlon),
    //             py::arg("northing"),
    //             py::arg("easting") ,
    //             py::arg("zone") ,
    //             py::arg("northern_hemisphere"));
}
