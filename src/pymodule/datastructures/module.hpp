// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

// declare modules
void init_c_positionaloffsets(pybind11::module& m); // c_positionaloffsets.cpp
void init_c_geolocation(pybind11::module& m);       // c_geolocation.cpp
void init_c_geolocationlatlon(pybind11::module& m); // c_geolocationlatlon.cpp
void init_c_geolocationutm(pybind11::module& m);    // c_geolocationutm.cpp
void init_c_geolocationlocal(pybind11::module& m);  // c_geolocationlocal.cpp
void init_c_sensordata(pybind11::module& m);        // c_sensordata.cpp
void init_c_sensordatalatlon(pybind11::module& m);  // c_sensordatalatlon.cpp
void init_c_sensordatautm(pybind11::module& m);     // c_sensordatautm.cpp
void init_c_sensordatalocal(pybind11::module& m);   // c_sensordatalocal.cpp

void init_m_datastructures(pybind11::module& m)
{
    pybind11::module m_datastructures = m.def_submodule("datastructures");

    m_datastructures.doc() = "Submodule that contains datastructures that store navigation "
                             "data or navigation sensor input";

    init_c_positionaloffsets(m_datastructures);
    init_c_geolocation(m_datastructures);
    init_c_geolocationlocal(m_datastructures);
    init_c_geolocationlatlon(m_datastructures);
    init_c_geolocationutm(m_datastructures);
    init_c_sensordata(m_datastructures);
    init_c_sensordatalatlon(m_datastructures);
    init_c_sensordatalocal(m_datastructures);
    init_c_sensordatautm(m_datastructures);

    using namespace themachinethatgoesping::navigation::datastructures;

    // pybind11::implicitly_convertible<GeolocationUTM, GeolocationLatLon>();
    // pybind11::implicitly_convertible<GeolocationLatLon, GeolocationUTM>();
    pybind11::implicitly_convertible<GeolocationUTM, GeolocationLocal>();
    pybind11::implicitly_convertible<GeolocationLatLon, Geolocation>();
    pybind11::implicitly_convertible<GeolocationLocal, Geolocation>();
    pybind11::implicitly_convertible<GeolocationUTM, Geolocation>();

    // pybind11::implicitly_convertible<SensordataUTM, SensordataLatLon>();
    // pybind11::implicitly_convertible<SensordataLatLon, SensordataUTM>();
    pybind11::implicitly_convertible<SensordataUTM,
                                     SensordataLocal>(); // this does not work anymore since
                                                         // Sensordata is derived from
                                                         // SensordataLocal
    pybind11::implicitly_convertible<SensordataUTM, Sensordata>();
    pybind11::implicitly_convertible<SensordataLatLon, Sensordata>();
    pybind11::implicitly_convertible<SensordataLocal, Sensordata>();
}
