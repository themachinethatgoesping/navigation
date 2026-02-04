// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#define FORCE_IMPORT_ARRAY

#include <nanobind/nanobind.h>
// #include <themachinethatgoesping/tools_nanobind/xtensor-python/nanobind/pytensor.hpp>

#include "datastructures/module.hpp"
#include "nmea_0183/module.hpp"

#include <themachinethatgoesping/navigation/navtools.hpp>
#include <themachinethatgoesping/tools_nanobind/enumhelper.hpp>

// declare modules
void init_m_navtools(nanobind::module_& m);                    // m_navtools.cpp
void init_c_sensorconfiguration(nanobind::module_& m);         // c_sensorconfiguration.cpp
void init_c_NavigationInterpolatorLocal(nanobind::module_& m); // c_navigationinterpolatorlocal.cpp
void init_c_NavigationInterpolatorLatLon(
    nanobind::module_& m); // c_navigationinterpolatorlatlon.cpp

NB_MODULE(MODULE_NAME, m)
{
    using themachinethatgoesping::navigation::navtools::o_latlon_format;
    using themachinethatgoesping::navigation::navtools::t_latlon_format;
    // xt::import_numpy();

    // this module needs some imports from tools_nanopy to work properly
    nb::module_ a = nb::module_::import_("themachinethatgoesping.tools_nanopy");

    m.doc()               = "Python module to store, interpolate and transform navigation data";
    m.attr("__version__") = MODULE_VERSION;

    auto pyenum_latlon =
        nb::enum_<t_latlon_format>(
            m,
            "t_latlon_format",
            DOC(themachinethatgoesping, navigation, navtools, t_latlon_format))
            .value("degrees",
                   t_latlon_format::degrees,
                   DOC(themachinethatgoesping, navigation, navtools, t_latlon_format, degrees))
            .value("minutes",
                   t_latlon_format::minutes,
                   DOC(themachinethatgoesping, navigation, navtools, t_latlon_format, minutes))
            .value("seconds",
                   t_latlon_format::seconds,
                   DOC(themachinethatgoesping, navigation, navtools, t_latlon_format, seconds))
        //
        ;

    themachinethatgoesping::tools::nanobind_helper::make_option_class<o_latlon_format>(
        m, "o_latlon_format");

    init_m_datastructures(m);
    init_c_sensorconfiguration(m);
    init_c_NavigationInterpolatorLocal(m);
    init_c_NavigationInterpolatorLatLon(m);
    init_m_nmea_0183(m);

    init_m_navtools(m);
}
