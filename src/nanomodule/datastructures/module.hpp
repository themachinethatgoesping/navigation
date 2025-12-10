// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <nanobind/nanobind.h>

// declare modules
void init_c_positionaloffsets(nanobind::module_& m); // c_positionaloffsets.cpp
void init_c_geolocation(nanobind::module_& m);       // c_geolocation.cpp
void init_c_geolocationlatlon(nanobind::module_& m);       // c_geolocationlatlon.cpp
void init_c_geolocationlatlonvector(nanobind::module_& m); // c_geolocationlatlonvector.cpp
void init_c_geolocationutm(nanobind::module_& m);          // c_geolocationutm.cpp
void init_c_geolocationlocal(nanobind::module_& m);  // c_geolocationlocal.cpp
void init_c_geolocationvector(nanobind::module_& m);      // c_geolocationvector.cpp
void init_c_geolocationlocalvector(nanobind::module_& m); // c_geolocationlocalvector.cpp
void init_c_geolocationutmvector(nanobind::module_& m);   // c_geolocationutmvector.cpp
void init_c_sensordata(nanobind::module_& m);        // c_sensordata.cpp
void init_c_sensordatalatlon(nanobind::module_& m);  // c_sensordatalatlon.cpp
void init_c_sensordatautm(nanobind::module_& m);     // c_sensordatautm.cpp
void init_c_sensordatalocal(nanobind::module_& m);   // c_sensordatalocal.cpp
void init_c_sensordatavector(nanobind::module_& m);       // c_sensordatavector.cpp
void init_c_sensordatalatlonvector(nanobind::module_& m); // c_sensordatalatlonvector.cpp
void init_c_sensordatalocalvector(nanobind::module_& m);  // c_sensordatalocalvector.cpp
void init_c_sensordatautmvector(nanobind::module_& m);    // c_sensordatautmvector.cpp

void init_m_datastructures(nanobind::module_& m)
{
    nanobind::module_ m_datastructures = m.def_submodule("datastructures");

    m_datastructures.doc() = "Submodule that contains datastructures that store navigation "
                             "data or navigation sensor input";

    init_c_positionaloffsets(m_datastructures);
    init_c_geolocation(m_datastructures);
    init_c_geolocationlocal(m_datastructures);
    init_c_geolocationlatlon(m_datastructures);
    init_c_geolocationlatlonvector(m_datastructures);
    init_c_geolocationutm(m_datastructures);
    init_c_geolocationvector(m_datastructures);
    init_c_geolocationlocalvector(m_datastructures);
    init_c_geolocationutmvector(m_datastructures);
    init_c_sensordata(m_datastructures);
    init_c_sensordatalatlon(m_datastructures);
    init_c_sensordatalocal(m_datastructures);
    init_c_sensordatautm(m_datastructures);
    init_c_sensordatavector(m_datastructures);
    init_c_sensordatalatlonvector(m_datastructures);
    init_c_sensordatalocalvector(m_datastructures);
    init_c_sensordatautmvector(m_datastructures);

    using namespace themachinethatgoesping::navigation::datastructures;

    // nanobind::implicitly_convertible<GeolocationUTM, GeolocationLatLon>();
    // nanobind::implicitly_convertible<GeolocationLatLon, GeolocationUTM>();
    nanobind::implicitly_convertible<GeolocationUTM, GeolocationLocal>();
    nanobind::implicitly_convertible<GeolocationLatLon, Geolocation>();
    nanobind::implicitly_convertible<GeolocationLocal, Geolocation>();
    nanobind::implicitly_convertible<GeolocationUTM, Geolocation>();

    // nanobind::implicitly_convertible<SensordataUTM, SensordataLatLon>();
    // nanobind::implicitly_convertible<SensordataLatLon, SensordataUTM>();
    nanobind::implicitly_convertible<SensordataUTM,
                                     SensordataLocal>(); // this does not work anymore since
                                                         // Sensordata is derived from
                                                         // SensordataLocal
    nanobind::implicitly_convertible<SensordataUTM, Sensordata>();
    nanobind::implicitly_convertible<SensordataLatLon, Sensordata>();
    nanobind::implicitly_convertible<SensordataLocal, Sensordata>();
}
