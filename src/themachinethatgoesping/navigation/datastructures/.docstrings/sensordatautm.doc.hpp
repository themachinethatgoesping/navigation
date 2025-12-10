//sourcehash: 5284ffcd6758ba1ef8c5f264a779ffc75b2c3a65b4a8e912eff5ed42dbb23778

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



static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM =
R"doc(A structure to store a georeferenced data and attitude data from
different sensors (e.g. GPS, IMU, etc.) Unlike SensordataLatLon, this
structure stores UTM coordinates.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_2 =
R"doc(Construct a new Sensor Data Local object using a base sensor data
object

Args:
    data: 
    northing: in m, positive northwards
    easting: in m, positive eastwards
    utm_zone: UTM/UPS zone number
    northern_hemisphere: if true: northern hemisphere, else: southern
                         hemisphere)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_3 =
R"doc(Construct an SensordataUTM object from an existing SensordataLocal
object (using a known zone and hemisphere)

Args:
    data_local: 
    utm_zone: UTM/UPS zone number
    northern_hemisphere: if true: northern hemisphere, else: southern
                         hemisphere)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_4 =
R"doc(Construct an SensordataUTM object from an existing SensordataLatLon
object (this allows for explicit conversion from SensordataLatLon
class))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_SensordataUTM_5 =
R"doc(Construct a new SensordataUTM object

Args:
    northing: in m, positive northwards
    easting: in m, positive eastwards
    utm_zone: UTM/UPS zone number
    northern_hemisphere: if true: northern hemisphere, else: southern
                         hemisphere
    depth: in m, positive downwards
    heave: is added to depth in m, positive upwards
    heading: in °, 0° is north, 90° is east
    pitch: in °, positive means bow up
    roll: in °, positive means port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_from_sensordata =
R"doc(Construct convert a SensordataLatLon Object to UTM

Args:
    data: valid SensordataLatLon object
    setzone: set a preferred UTM zone negative means automatic, zero
             means UPS, positive means a particular UTM zone

Returns:
    SensordataUTM)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_northern_hemisphere = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_operator_eq =
R"doc(Check if two SensordataUTM objects are equal

Args:
    rhs: 

Returns:
    true if equal false if not equal)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_to_sensordata =
R"doc(Convert a utm sensordatalatlon to an unprojected data

Args:
    data_utm: 

Returns:
    SensordataLatLon)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_to_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensordataUTM_utm_zone = R"doc(UTM/UPS zone number)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


