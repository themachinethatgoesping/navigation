// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "../docstrings.hpp"
#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// declare modules
void init_c_nmea_base(pybind11::module& m);    // c_nmea_base.cpp
void init_c_nmea_zda(pybind11::module& m);     // c_nmea_zda.cpp
void init_c_nmea_vlw(pybind11::module& m);     // c_nmea_vlw.cpp
void init_c_nmea_vtg(pybind11::module& m);     // c_nmea_vtg.cpp
void init_c_nmea_vhw(pybind11::module& m);     // c_nmea_vhw.cpp
void init_c_nmea_rmc(pybind11::module& m);     // c_nmea_rmc.cpp
void init_c_nmea_hdt(pybind11::module& m);     // c_nmea_hdt.cpp
void init_c_nmea_gll(pybind11::module& m);     // c_nmea_gll.cpp
void init_c_nmea_gga(pybind11::module& m);     // c_nmea_gga.cpp
void init_c_nmea_unknown(pybind11::module& m); // c_nmea_unknown.cpp

void init_m_nmea_0183(pybind11::module& m)
{
    namespace py = pybind11;

    py::module m_nmea = m.def_submodule("nmea_0183");

    m_nmea.doc() = "Submodule that contains nmea 0183 datastructures";

    init_c_nmea_base(m_nmea);
    init_c_nmea_zda(m_nmea);
    init_c_nmea_vlw(m_nmea);
    init_c_nmea_vtg(m_nmea);
    init_c_nmea_vhw(m_nmea);
    init_c_nmea_rmc(m_nmea);
    init_c_nmea_hdt(m_nmea);
    init_c_nmea_gll(m_nmea);
    init_c_nmea_gga(m_nmea);
    init_c_nmea_unknown(m_nmea);

    m_nmea.def(
        "decode",
        py::overload_cast<std::string>(themachinethatgoesping::navigation::nmea_0183::decode),
        DOC(themachinethatgoesping, navigation, nmea_0183, decode),
        py::arg("nmea_sentence"));

    using namespace themachinethatgoesping::navigation::nmea_0183;

    // pybind11::implicitly_convertible<NMEA_Base, NMEA_ZDA>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_VLW>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_VTG>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_VHW>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_RMC>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_HDT>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_GLL>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_GGA>();
    // pybind11::implicitly_convertible<NMEA_Base, NMEA_Unknown>();
}
