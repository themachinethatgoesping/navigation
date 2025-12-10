//sourcehash: 0f9e66daaf56de84d1fd6d414c442d4135ea5d55bc8b18e714e1a456eb61e017

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


static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets =
R"doc(A structure to store positional offsets (e.g. of a sensor) relative to
the vessel coordinate system)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_PositionalOffsets = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_PositionalOffsets_2 =
R"doc(Construct a new PositionalOffsets object

Args:
    name: The name of the sensor
    x: in m, positive forward
    y: in m, positive starboard
    z: in m, positive downwards
    yaw: positive means clockwise rotation
    pitch: in °, positive means bow up
    roll: in °, positive means port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_from_txrx =
R"doc(Construct a new PositionalOffsets object from a transmitter and
receiver unit

Args:
    tx: Multibeam transmitter offsets
    rx: Multibeam receiver offsets
    name: Name of the newly constructed transceiver offsets

Returns:
    Transceiver PositionalOffsets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_name = R"doc(The name of the sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_pitch = R"doc(in °, positive means bow up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_roll = R"doc(in °, positive means port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_to_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_x = R"doc(in m, positive forward)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_y = R"doc(in m, positive starboard)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_yaw = R"doc(in °, positive means clockwise rotation)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_z = R"doc(in m, positive downwards)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


