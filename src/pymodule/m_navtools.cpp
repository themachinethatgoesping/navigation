// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/navigation/navtools.hpp"
#include <themachinethatgoesping/tools_pybind/enumhelper.hpp>

// -- include pybind11 headers
#include <pybind11/stl.h>
#include "xtensor-python/pyarray.hpp"
#include <xtensor-python/pytensor.hpp>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation::navtools;
using namespace themachinethatgoesping;

void init_m_navtools(py::module& m)
{

    auto m_navtools =
        m.def_submodule("navtools", "Convenient functions for converting latlon and utm strings.");

    auto pyenum_latlon = py::enum_<t_latlon_format>(
                             m_navtools,
                             "t_latlon_format",
                             DOC(themachinethatgoesping, navigation, navtools, t_latlon_format))
                             .value("degrees", t_latlon_format::degrees)
                             .value("minutes", t_latlon_format::minutes)
                             .value("seconds", t_latlon_format::seconds)
                             .export_values()
        //
        ;

    tools::pybind_helper::add_string_to_enum_conversion<t_latlon_format>(pyenum_latlon);

    //----- latitude_to_string -----
    m_navtools.def("latitude_to_string",
                   &latitude_to_string,
                   DOC(themachinethatgoesping, navigation, navtools, latitude_to_string),
                   py::arg("latitude"),
                   py::arg("format")    = t_latlon_format::minutes,
                   py::arg("precision") = 6);

    // vectorized call
    m_navtools.def(
        "latitude_to_string",
        [](const std::vector<double>& latitudes, t_latlon_format format, size_t precision) {
            std::vector<std::string> result;
            result.reserve(latitudes.size());
            for (auto& latitude : latitudes)
            {
                result.push_back(latitude_to_string(latitude, format, precision));
            }
            return result;
        },
        DOC(themachinethatgoesping, navigation, navtools, latitude_to_string),
        py::arg("latitude"),
        py::arg("format")    = t_latlon_format::minutes,
        py::arg("precision") = 6);

    //----- longitude_to_string -----
    m_navtools.def("longitude_to_string",
                   &longitude_to_string,
                   DOC(themachinethatgoesping, navigation, navtools, longitude_to_string),
                   py::arg("longitude"),
                   py::arg("format")    = t_latlon_format::minutes,
                   py::arg("precision") = 6);

    // vectorized call
    m_navtools.def(
        "longitude_to_string",
        [](const std::vector<double>& longitudes, t_latlon_format format, size_t precision) {
            std::vector<std::string> result;
            result.reserve(longitudes.size());
            for (auto& longitude : longitudes)
            {
                result.push_back(longitude_to_string(longitude, format, precision));
            }
            return result;
        },
        DOC(themachinethatgoesping, navigation, navtools, longitude_to_string),
        py::arg("longitude"),
        py::arg("format")    = t_latlon_format::minutes,
        py::arg("precision") = 6);

    //----- utm conversion -----
    // TODO: documentation is not updated to include these functions for some reason
    m_navtools.def(
        "utm_to_latlon",
        py::overload_cast<const std::vector<double>&, const std::vector<double>&, int, bool>(
            &utm_to_latlon),
        // DOC(themachinethatgoesping, navigation, navtools, utm_to_latlon),
        py::arg("northing"),
        py::arg("easting"),
        py::arg("zone"),
        py::arg("northern_hemisphere"));

    m_navtools.def("utm_to_latlon",
                   py::overload_cast<const std::vector<double>&,
                                     const std::vector<double>&,
                                     const std::vector<int>&,
                                     const std::vector<bool>&>(&utm_to_latlon),
                   // DOC(themachinethatgoesping, navigation, navtools, utm_to_latlon),
                   py::arg("northing"),
                   py::arg("easting"),
                   py::arg("zone"),
                   py::arg("northern_hemisphere"));

    m_navtools.def("latlon_to_utm",
                   &latlon_to_utm,
                   // DOC(themachinethatgoesping, navigation, navtools, utm_to_latlon),
                   py::arg("latitude"),
                   py::arg("longitude"),
                   py::arg("setzone"));

    m_navtools.def("compute_distance",
                   &compute_distance<double>,
                   DOC(themachinethatgoesping, navigation, navtools, compute_distance),
                   py::arg("lat1"),
                   py::arg("lon1"),
                   py::arg("lat2"),
                   py::arg("lon2"));

    m_navtools.def("compute_distances",
                   &compute_distances<xt::pytensor<double, 1>>,
                   DOC(themachinethatgoesping, navigation, navtools, compute_distances),
                   py::arg("latitudes"),
                   py::arg("longitudes"));

    m_navtools.def("cumulative_distances",
                   &cumulative_distances<xt::pytensor<double, 1>>,
                   DOC(themachinethatgoesping, navigation, navtools, cumulative_distances),
                   py::arg("latitudes"),
                   py::arg("longitudes"));
}
