//sourcehash: 9b3b3fa2b7efbb4b6c5092cffdd8ce77af69798e486a1c58fe9440a7aca64c49

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



static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) unlike the default Geolocation structure, this object stores
utm coordinates)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_GeolocationUTM = R"doc(Construct a new Sensor Position object)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_GeolocationUTM_2 =
R"doc(Construct an GeolocationUTM object from an existing GeolocationLocal
object (using a known zone and hemisphere)

Parameter ``location_local``:
    $Parameter ``utm_zone``:

UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_GeolocationUTM_3 =
R"doc(Construct an GeolocationUTM object from an existing GeolocationLatLon
object (this allows for explicit conversion from GeolocationLatLon
class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_GeolocationUTM_4 =
R"doc(Construct a new GeolocationUTM object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``utm_zone``:
    UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_from_geolocation_latlon =
R"doc(Construct convert a GeolocationLatLon Object to UTM

Parameter ``location``:
    valid GeolocationLatLon object

Parameter ``setzone``:
    set a preferred UTM zone negative means automatic, zero means UPS,
    positive means a particular UTM zone

Returns:
    GeolocationUTM)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_northern_hemisphere = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_to_geolocation_latlon =
R"doc(Convert a utm geolocationlatlon to an unprojected location

Parameter ``location_utm``:
    $Returns:

GeolocationLatLon)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeolocationUTM_utm_zone = R"doc(< UTM/UPS zone number)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


