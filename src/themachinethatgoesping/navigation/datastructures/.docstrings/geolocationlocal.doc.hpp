//sourcehash: e087736bcdc40ad387d4ef0417c901c91e94edf3d638ec0b4fa42a1339dac551

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


static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) unlike the default GeoLocation structure, this object stores
local northing and easting coordinates. These coordinates can be
converted to UTM coordinates if the zone and hemisphere are known.)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_GeoLocationLocal = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_GeoLocationLocal_2 =
R"doc(Construct a new GeoLocationLocal object

Parameter ``location``:
    $Parameter ``northing``:

in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_GeoLocationLocal_3 =
R"doc(Construct a new GeoLocationLocal object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_easting = R"doc(< in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_northing = R"doc(< in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


