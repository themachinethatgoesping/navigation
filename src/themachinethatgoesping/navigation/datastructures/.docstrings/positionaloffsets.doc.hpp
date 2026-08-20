//sourcehash: 35d3d5b30be59a7fec09cbd72c13070422c18d52e96c8996ac8fa441b0c605c0

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


static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose =
R"doc(A structure to store positional offsets (e.g. of a sensor) relative to
the vessel coordinate system)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_SensorPose = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_SensorPose_2 =
R"doc(Construct a new SensorPose object

Args:
    name: The name of the sensor
    x: in m, positive forward
    y: in m, positive starboard
    z: in m, positive downwards
    yaw: positive means clockwise rotation
    pitch: in °, positive means bow up
    roll: in °, positive means port up
    ypr_offsets_applied: if true, the yaw/pitch/roll offsets are
                         already applied to the associated sensor data
                         (default: false))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_SensorPose_3 =
R"doc(Construct a new SensorPose object from a Rotation

Args:
    name: The name of the sensor
    x: in m, positive forward
    y: in m, positive starboard
    z: in m, positive downwards
    rotation: yaw/pitch/roll offset orientation
    ypr_offsets_applied: if true, the offsets are already applied
                         (default: false))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_from_txrx =
R"doc(Construct a new SensorPose object from a transmitter and receiver unit

Args:
    tx: Multibeam transmitter offsets
    rx: Multibeam receiver offsets
    name: Name of the newly constructed transceiver offsets

Returns:
    Transceiver SensorPose)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_name = R"doc(The name of the sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_pitch = R"doc(pitch in °, positive means bow up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_roll = R"doc(roll in °, positive means port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_rotation = R"doc(yaw/pitch/roll offsets (°); exposed via yaw()/pitch()/roll())doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_set_pitch = R"doc(set pitch (°), keeping yaw and roll)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_set_roll = R"doc(set roll (°), keeping yaw and pitch)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_set_yaw = R"doc(set yaw (°), keeping pitch and roll)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_set_ypr = R"doc(set yaw, pitch and roll (°) at once)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_to_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_x = R"doc(in m, positive forward)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_y = R"doc(in m, positive starboard)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_yaw = R"doc(yaw in °, positive means clockwise rotation)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_ypr_offsets_applied =
R"doc(if true, the yaw/pitch/roll offsets are already applied to the
associated sensor data stream (e.g. Kongsberg .all logs the
attitude/heading already corrected for the sensor mounting offsets).
In that case the SensorConfiguration must not re-apply them when
computing the vessel rotation. If false (default), the offsets still
have to be applied.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_SensorPose_z = R"doc(in m, positive downwards)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


