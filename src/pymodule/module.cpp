// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#include "datastructures/module.hpp"

// declare modules
void init_m_navtools(pybind11::module& m);                     // m_navtools.cpp
void init_c_sensorconfiguration(pybind11::module& m);          // c_sensorconfiguration.cpp
void init_c_NavigationInterpolatorLocal(pybind11::module& m);  // c_navigationinterpolatorlocal.cpp
void init_c_NavigationInterpolatorLatLon(pybind11::module& m); // c_navigationinterpolatorlatlon.cpp

PYBIND11_MODULE(PYTHON_LIB, m)
{
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.doc() = "Python module to store, interpolate and transform navigation data";

    init_m_navtools(m);
    init_m_datastructures(m);
    init_c_sensorconfiguration(m);
    init_c_NavigationInterpolatorLocal(m);
    init_c_NavigationInterpolatorLatLon(m);
}
