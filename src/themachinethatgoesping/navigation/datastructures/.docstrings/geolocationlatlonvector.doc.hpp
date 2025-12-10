//sourcehash: 134f3bc032ca8928e11a46df313548f4a117250ac4984e6ccffc41faa063e309

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


static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector =
R"doc(A structure to store a vector of georeferenced locations with
timestamps. Provides efficient access to individual components as
vectors for Python performance.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_GeolocationLatLonVector = R"doc(Construct an empty GeolocationLatLonVector)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_GeolocationLatLonVector_2 =
R"doc(Construct a GeolocationLatLonVector with pre-allocated capacity
Args:
    capacity: number of elements to reserve)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_GeolocationLatLonVector_3 =
R"doc(Construct a GeolocationLatLonVector from existing data
Args:
    timestamps: vector of timestamps
    geolocations: vector of geolocations (must be same size as
                  timestamps))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_at =
R"doc(Get geolocation at index
Args:
    index: position in the vector

Returns:
    const reference to geolocation)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_empty =
R"doc(Check if the vector is empty
Returns:
    true if no elements are stored)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_geolocations = R"doc(geolocation data)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_geolocations = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_latitudes =
R"doc(Get all latitudes as a vector
Returns:
    vector of latitudes in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_longitudes =
R"doc(Get all longitudes as a vector
Returns:
    vector of longitudes in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_pitch =
R"doc(Get all pitch values as a vector
Returns:
    vector of pitch values in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_roll =
R"doc(Get all roll values as a vector
Returns:
    vector of roll values in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_timestamps = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_yaw =
R"doc(Get all yaw values as a vector
Returns:
    vector of yaw values in degrees)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_get_z =
R"doc(Get all z values (depth) as a vector
Returns:
    vector of z values in meters (positive downwards))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_push_back =
R"doc(Add a geolocation with timestamp
Args:
    timestamp: time in seconds since epoch
    geolocation: the geolocation to add)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_push_back_2 =
R"doc(Add a geolocation with timestamp (move version)
Args:
    timestamp: time in seconds since epoch
    geolocation: the geolocation to add)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_reserve =
R"doc(Reserve capacity for n elements
Args:
    n: number of elements to reserve space for)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_size =
R"doc(Get the number of elements
Returns:
    size_t number of geolocations stored)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_timestamp_at =
R"doc(Get timestamp at index
Args:
    index: position in the vector

Returns:
    timestamp value)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_timestamps = R"doc(timestamps in seconds since epoch)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_GeolocationLatLonVector_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


