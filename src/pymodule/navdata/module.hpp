// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

// declare modules
void init_c_positionaloffsets(pybind11::module& m); // c_positionaloffsets.cpp
void init_c_geolocation(pybind11::module& m);       // c_geolocation.cpp
void init_c_geolocationutm(pybind11::module& m);    // c_geolocationutm.cpp
void init_c_geolocationlocal(pybind11::module& m);  // c_geolocationlocal.cpp
void init_c_sensordata(pybind11::module& m);        // c_sensordata.cpp
void init_c_sensordatautm(pybind11::module& m);     // c_sensordatautm.cpp
void init_c_sensordatalocal(pybind11::module& m);   // c_sensordatalocal.cpp

void init_m_navdata(pybind11::module& m)
{
    pybind11::module m_navdata = m.def_submodule("navdata");

    m_navdata.doc() = "Submodule that contains navdata that store navigation "
                             "data or navigation sensor input";

    init_c_positionaloffsets(m_navdata);
    init_c_geolocation(m_navdata);
    init_c_geolocationutm(m_navdata);
    init_c_geolocationlocal(m_navdata);
    init_c_sensordata(m_navdata);
    init_c_sensordatautm(m_navdata);
    init_c_sensordatalocal(m_navdata);
}
