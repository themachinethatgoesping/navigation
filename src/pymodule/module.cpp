// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

// declare modules
void init_c_positionaloffsets(pybind11::module& m); // c_positionaloffsets.cpp
void init_c_geolocation(pybind11::module& m);       // c_geolocation.cpp
void init_c_geolocationutm(pybind11::module& m);    // c_geolocationutm.cpp
void init_m_navtools(pybind11::module& m);             // m_navtools.cpp

PYBIND11_MODULE(PYTHON_LIB, m)
{
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.doc() = "Python module to store, interpolate and transform navigation data";

    init_m_navtools(m);
    init_c_positionaloffsets(m);
    init_c_geolocation(m);
    init_c_geolocationutm(m);
}
