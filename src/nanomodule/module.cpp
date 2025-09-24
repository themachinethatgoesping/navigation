// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#define FORCE_IMPORT_ARRAY

#include <nanobind/nanobind.h>
//#include <themachinethatgoesping/tools_nanobind/xtensor-python/pytensor.hpp>



// #include "datastructures/module.hpp"
// #include "nmea_0183/module.hpp"

// declare modules
void init_m_navtools(nanobind::module_& m);                     // m_navtools.cpp
// void init_c_sensorconfiguration(nanobind::module_& m);          // c_sensorconfiguration.cpp
// void init_c_NavigationInterpolatorLocal(nanobind::module_& m);  // c_navigationinterpolatorlocal.cpp
// void init_c_NavigationInterpolatorLatLon(nanobind::module_& m); // c_navigationinterpolatorlatlon.cpp

NB_MODULE(MODULE_NAME, m)
{
    //xt::import_numpy();

    m.doc() = "Python module to store, interpolate and transform navigation data";
    m.attr("__version__") = MODULE_VERSION;

    // init_m_datastructures(m);
    // init_c_sensorconfiguration(m);
    // init_c_NavigationInterpolatorLocal(m);
    // init_c_NavigationInterpolatorLatLon(m);
    // init_m_nmea_0183(m);

    init_m_navtools(m);
}
