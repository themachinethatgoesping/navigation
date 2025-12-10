//sourcehash: 8e0ecb544457fb414e7ee7da1926179369731b8c706da5adc7a75cc06febaa47

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_HPP__
#define __DOCSTRINGS_HPP__

#define MKD_EXPAND(x)                                      x
#define MKD_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, COUNT, ...)  COUNT
#define MKD_VA_SIZE(...)                                   MKD_EXPAND(MKD_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define MKD_CAT1(a, b)                                     a ## b
#define MKD_CAT2(a, b)                                     MKD_CAT1(a, b)
#define MKD_DOC1(n1)                                       mkd_doc_##n1
#define MKD_DOC2(n1, n2)                                   mkd_doc_##n1##_##n2
#define MKD_DOC3(n1, n2, n3)                               mkd_doc_##n1##_##n2##_##n3
#define MKD_DOC4(n1, n2, n3, n4)                           mkd_doc_##n1##_##n2##_##n3##_##n4
#define MKD_DOC5(n1, n2, n3, n4, n5)                       mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5
#define MKD_DOC6(n1, n2, n3, n4, n5, n6)                   mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define MKD_DOC7(n1, n2, n3, n4, n5, n6, n7)               mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define MKD_DOC8(n1, n2, n3, n4, n5, n6, n7, n8)           mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8
#define MKD_DOC9(n1, n2, n3, n4, n5, n6, n7, n8, n9)       mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9
#define MKD_DOC10(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10) mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9##_##n10
#define DOC(...)                                           MKD_EXPAND(MKD_EXPAND(MKD_CAT2(MKD_DOC, MKD_VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#endif // __DOCSTRINGS_HPP__
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) Unlike the base Geolocation object, this also stores latitude
and longitude coordinates)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_GeolocationLatLon = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_GeolocationLatLon_2 =
R"doc(Construct a new Sensor Data Lat Lon object using a base sensor data
object

Args:
    location: 
    latitude: in °, positive northwards
    longitude: in °, positive eastwards)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_GeolocationLatLon_3 =
R"doc(Construct an GeolocationLatLon object from an existing GeolocationUTM
object (this allows for explicit conversion from GeolocationUTM class))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_GeolocationLatLon_4 =
R"doc(Construct a new GeolocationLatLon object

Args:
    latitude: in °, positive northwards
    longitude: in °, positive eastwards
    z: in m, positive downwards
    yaw: in °, 0° is north, 90° is east
    pitch: in °, positive means bow up
    roll: in °, positive means port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_latitude = R"doc(in °, positive northwards)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_longitude = R"doc(in °, positive eastwards)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_operator_eq =
R"doc(Check if two GeolocationLatLon objects are equal

Args:
    rhs: 

Returns:
    true if equal false if not equal)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_operator_ne =
R"doc(Construct a new GeolocationLatLon object from a string

Args:
    str: string containing the location in the format
         "latitude,longitude,z,yaw,pitch,roll")doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLon_to_stream = R"doc()doc";


#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


