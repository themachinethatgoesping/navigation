//sourcehash: 7bf9bb4314e3bed20af62eed25e74a84a2aa8d2c7a89ac73eda1a0615bda9f97

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_HPP__

#define __EXPAND(x)                                                  x
#define __COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, COUNT, ...) COUNT
#define __VA_SIZE(...)                                               __EXPAND(__COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
#define __CAT1(a, b)                                                 a##b
#define __CAT2(a, b)                                                 __CAT1(a, b)
#define __DOC1(n1)                                                   __doc_##n1
#define __DOC2(n1, n2)                                               __doc_##n1##_##n2
#define __DOC3(n1, n2, n3)                                           __doc_##n1##_##n2##_##n3
#define __DOC4(n1, n2, n3, n4)                                       __doc_##n1##_##n2##_##n3##_##n4
#define __DOC5(n1, n2, n3, n4, n5)                                   __doc_##n1##_##n2##_##n3##_##n4##_##n5
#define __DOC6(n1, n2, n3, n4, n5, n6)                               __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define __DOC7(n1, n2, n3, n4, n5, n6, n7)                           __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define __DOC8(n1, n2, n3, n4, n5, n6, n7, n8)                                                     \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8
#define __DOC9(n1, n2, n3, n4, n5, n6, n7, n8, n9)                                                 \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9
#define __DOC10(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10)                                           \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9##_##n10
#define DOC(...) __EXPAND(__EXPAND(__CAT2(__DOC, __VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#endif // NEW_DOC_HEADER_HPP
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) This structure does not store any coordinates except the depth
(z))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_Geolocation = R"doc(Construct a new Position object)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_Geolocation_2 =
R"doc(Construct a new Geolocation object

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_operator_eq =
R"doc(Check if two Geolocation objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_operator_ne =
R"doc(Construct a new Geolocation object from a string

Parameter ``str``:
    string containing the location in the format
    "latitude,longitude,z,yaw,pitch,roll")doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_Geolocation_z = R"doc(< in m, positive downwards)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


