// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#include "navdata/module.hpp"

// declare modules
void init_m_navtools(pybind11::module& m);          // m_navtools.cpp

PYBIND11_MODULE(PYTHON_LIB, m)
{
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.doc() = "Python module to store, interpolate and transform navigation data";

    init_m_navtools(m);
    init_m_navdata(m);
}
