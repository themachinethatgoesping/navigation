// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#define FORCE_IMPORT_ARRAY

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <xtensor-python/pytensor.hpp>
#include <xtensor-python/pyarray.hpp> // Numpy bindings


#include "datastructures/module.hpp"
#include "nmea_0183/module.hpp"

// declare modules
void init_m_navtools(pybind11::module& m);                     // m_navtools.cpp
void init_c_sensorconfiguration(pybind11::module& m);          // c_sensorconfiguration.cpp
void init_c_NavigationInterpolatorLocal(pybind11::module& m);  // c_navigationinterpolatorlocal.cpp
void init_c_NavigationInterpolatorLatLon(pybind11::module& m); // c_navigationinterpolatorlatlon.cpp

PYBIND11_MODULE(MODULE_NAME, m)
{
    xt::import_numpy();
    
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.doc()               = "Python module to store, interpolate and transform navigation data";
    m.attr("__version__") = MODULE_VERSION;

    init_m_datastructures(m);
    init_c_sensorconfiguration(m);
    init_c_NavigationInterpolatorLocal(m);
    init_c_NavigationInterpolatorLatLon(m);
    init_m_nmea_0183(m);

    init_m_navtools(m);
}
