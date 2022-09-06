// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

// declare modules
void init_c_nmea_base(pybind11::module& m); // c_nmea_base.cpp
void init_c_nmea_zda(pybind11::module& m); // c_nmea_zda.cpp
void init_c_nmea_vlw(pybind11::module& m); // c_nmea_vlw.cpp
void init_c_nmea_vtg(pybind11::module& m); // c_nmea_vtg.cpp
void init_c_nmea_vhw(pybind11::module& m); // c_nmea_vhw.cpp
void init_c_nmea_rmc(pybind11::module& m); // c_nmea_rmc.cpp
void init_c_nmea_hdt(pybind11::module& m); // c_nmea_hdt.cpp
void init_c_nmea_gll(pybind11::module& m); // c_nmea_gll.cpp
void init_c_nmea_gga(pybind11::module& m); // c_nmea_gga.cpp
void init_c_nmea_unknown(pybind11::module& m); // c_nmea_unknown.cpp

void init_m_nmea_0183(pybind11::module& m)
{
    pybind11::module m_datastructures = m.def_submodule("nmea_0183");

    m_datastructures.doc() = "Submodule that contains nmea 0183 datastructures";

    init_c_nmea_base(m_datastructures);
    init_c_nmea_zda(m_datastructures);
    init_c_nmea_vlw(m_datastructures);
    init_c_nmea_vtg(m_datastructures);
    init_c_nmea_vhw(m_datastructures);
    init_c_nmea_rmc(m_datastructures);
    init_c_nmea_hdt(m_datastructures);
    init_c_nmea_gll(m_datastructures);
    init_c_nmea_gga(m_datastructures);
    init_c_nmea_unknown(m_datastructures);

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
