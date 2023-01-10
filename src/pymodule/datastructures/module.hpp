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
    init_c_geolocationlatlon(m_datastructures);
    init_c_geolocationlocal(m_datastructures);
    init_c_geolocationutm(m_datastructures);
    init_c_sensordata(m_datastructures);
    init_c_sensordatalatlon(m_datastructures);
    init_c_sensordatalocal(m_datastructures);
    init_c_sensordatautm(m_datastructures);

    using namespace themachinethatgoesping::navigation::datastructures;

    pybind11::implicitly_convertible<GeoLocationUTM, GeoLocationLatLon>();
    pybind11::implicitly_convertible<GeoLocationLatLon, GeoLocationUTM>();
    pybind11::implicitly_convertible<GeoLocationUTM, GeoLocationLocal>();
    pybind11::implicitly_convertible<GeoLocationLatLon, GeoLocation>();
    pybind11::implicitly_convertible<GeoLocationLocal, GeoLocation>();
    pybind11::implicitly_convertible<GeoLocationUTM, GeoLocation>();

    pybind11::implicitly_convertible<SensorDataUTM, SensorDataLatLon>();
    pybind11::implicitly_convertible<SensorDataLatLon, SensorDataUTM>();
    pybind11::implicitly_convertible<SensorDataUTM,
                                     SensorDataLocal>(); // this does not work anymore since
                                                         // SensorData is derived from
                                                         // SensorDataLocal
    pybind11::implicitly_convertible<SensorDataUTM, SensorData>();
    pybind11::implicitly_convertible<SensorDataLatLon, SensorData>();
    pybind11::implicitly_convertible<SensorDataLocal, SensorData>();
}
