//sourcehash: 083f3c786e6a4e6ca862ac78be42bcc6347408d9e25974f23b3e59fb6c109402

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


static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector = R"doc(A class to store a vector of GeolocationUTM elements with timestamps.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_eastings =
R"doc(Get all easting values as a vector
Returns:
    vector of easting values in meters)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_northern_hemispheres =
R"doc(Get all hemisphere flags as a vector
Returns:
    vector of booleans (true = northern hemisphere))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_northings =
R"doc(Get all northing values as a vector
Returns:
    vector of northing values in meters)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_pitch =
R"doc(Get all pitch values as a vector
Returns:
    vector of pitch values in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_roll =
R"doc(Get all roll values as a vector
Returns:
    vector of roll values in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_utm_zones =
R"doc(Get all UTM zone values as a vector
Returns:
    vector of UTM zone numbers)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_yaw =
R"doc(Get all yaw values as a vector
Returns:
    vector of yaw values in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_get_z =
R"doc(Get all z values (depth) as a vector
Returns:
    vector of z values in meters (positive downwards))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationUTMVector_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


