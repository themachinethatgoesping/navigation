//sourcehash: 38a6792db8517fc6a6faaedcce91e72a55cb2fcf43018ae1081e340bd1194ef7

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



static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM =
R"doc(A structure to store a georeferenced data and attitude data from
different sensors (e.g. GPS, IMU, etc.) Unlike SensordataLatLon, this
structure stores UTM coordinates.)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_2 =
R"doc(Construct a new Sensor Data Local object using a base sensor data
object

Parameter ``data``:
    $Parameter ``northing``:

in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``utm_zone``:
    UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_3 =
R"doc(Construct an SensordataUTM object from an existing SensordataLocal
object (using a known zone and hemisphere)

Parameter ``data_local``:
    $Parameter ``utm_zone``:

UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_4 =
R"doc(Construct an SensordataUTM object from an existing SensordataLatLon
object (this allows for explicit conversion from SensordataLatLon
class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_5 =
R"doc(Construct a new SensordataUTM object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``utm_zone``:
    UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``depth``:
    in m, positive downwards

Parameter ``heave``:
    is added to depth in m, positive upwards

Parameter ``heading``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_from_sensordata =
R"doc(Construct convert a SensordataLatLon Object to UTM

Parameter ``data``:
    valid SensordataLatLon object

Parameter ``setzone``:
    set a preferred UTM zone negative means automatic, zero means UPS,
    positive means a particular UTM zone

Returns:
    SensordataUTM)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_northern_hemisphere = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_operator_eq =
R"doc(Check if two SensordataUTM objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_to_sensordata =
R"doc(Convert a utm sensordatalatlon to an unprojected data

Parameter ``data_utm``:
    $Returns:

SensordataLatLon)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_utm_zone = R"doc(< UTM/UPS zone number)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


