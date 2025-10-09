// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0



#include "../themachinethatgoesping/navigation/nmea_0183.hpp"
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/variant.h>

// declare modules
void init_c_nmea_base(nanobind::module_& m);    // c_nmea_base.cpp
void init_c_nmea_zda(nanobind::module_& m);     // c_nmea_zda.cpp
void init_c_nmea_vlw(nanobind::module_& m);     // c_nmea_vlw.cpp
void init_c_nmea_vtg(nanobind::module_& m);     // c_nmea_vtg.cpp
void init_c_nmea_vhw(nanobind::module_& m);     // c_nmea_vhw.cpp
void init_c_nmea_rmc(nanobind::module_& m);     // c_nmea_rmc.cpp
void init_c_nmea_hdt(nanobind::module_& m);     // c_nmea_hdt.cpp
void init_c_nmea_gll(nanobind::module_& m);     // c_nmea_gll.cpp
void init_c_nmea_gga(nanobind::module_& m);     // c_nmea_gga.cpp
void init_c_nmea_gst(nanobind::module_& m);     // c_nmea_gst.cpp
void init_c_nmea_unknown(nanobind::module_& m); // c_nmea_unknown.cpp

void init_m_nmea_0183(nanobind::module_& m)
{
    namespace nb = nanobind;

    nb::module_ m_nmea = m.def_submodule("nmea_0183");

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
    init_c_nmea_gst(m_nmea);
    init_c_nmea_unknown(m_nmea);

    m_nmea.def(
        "decode",
        nb::overload_cast<std::string>(themachinethatgoesping::navigation::nmea_0183::decode),
        DOC(themachinethatgoesping, navigation, nmea_0183, decode),
        nb::arg("nmea_sentence"));

    using namespace themachinethatgoesping::navigation::nmea_0183;

    // nanobind::implicitly_convertible<NMEA_Base, NMEA_ZDA>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_VLW>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_VTG>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_VHW>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_RMC>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_HDT>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_GLL>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_GGA>();
    // nanobind::implicitly_convertible<NMEA_Base, NMEA_Unknown>();
}
