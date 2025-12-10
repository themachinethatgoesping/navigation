//sourcehash: a115cc517662cc226350d87ecf7219566cf172564de453fd6e643367ddade0d3

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


static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator =
R"doc(The NavInterpolator class: Interpolate attitude information and
transform the values using the offsets specified in the sensor
configuration class This is an interface class that specifies attitude
information but not the position)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_I_NavigationInterpolator =
R"doc(Construct a new i navigationinterpolator interface

Args:
    extrapolation_mode: extrapolate, fail or nearest)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_add_target =
R"doc(add a target sensor with positional offsets

Args:
    target_id: name of the target sensor
    x: x position of the sensor in m, positive forward
    y: y position of the sensor in m, positive starboard
    z: z position of the sensor in m, positive down
    yaw: yaw angle of the sensor in °, positive clockwise
    pitch: pitch angle of the sensor in °, positive is bow up
    roll: roll angle of the sensor in °, positive is port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_add_target_2 =
R"doc(add a target sensor with positional offsets

Args:
    target_id: name of the target sensor
    sensor_offsets: structure that contains the sensor position)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_class_name = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_get_sensor_configuration =
R"doc(direct reference to the sensor configuration

Returns:
    SensorConfiguration&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude = R"doc(interpolator that stores attitude data (pitch and roll))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude_2 =
R"doc(direct reference to the attitude data interpolator

Returns:
    interpolator_attitude&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude_3 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth = R"doc(interpolator that stores depth data (depth, positive downwards) [m])doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth_2 =
R"doc(direct reference to the depth data interpolator

Returns:
    interpolator_depth&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth_3 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading = R"doc(interpolator that stores compass data (yaw/heading) [°])doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading_2 =
R"doc(direct reference to the compass data interpolator

Returns:
    interpolator_heading&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading_3 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave =
R"doc(interpolator that stores heave data (relative change in depth,
positive upwards) [m])doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave_2 =
R"doc(direct reference to the heave data interpolator

Returns:
    interpolator_heave&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave_3 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_merge =
R"doc(Merge data from another interpolator. Only works of the
SensorConfiguration is compatible.

Args:
    other:)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_sensor_configuration = R"doc(sensor configuration that stores the offsets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_attitude =
R"doc(Set the attitude data (no yaw, this is set in set_data_heading)

Args:
    timestamp: in seconds since epoch
    pitch: in °, positive is bow up
    roll: in °, positive is port up)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_depth =
R"doc(Set the depth data

Args:
    timestamp: in seconds since epoch
    depth: in meters, positive downwards)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_heading =
R"doc(Set the compass data

Args:
    timestamp: in seconds since epoch
    heading: in °, positive clockwise (north is 0°))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_heave =
R"doc(Set the heave data

Args:
    timestamp: in seconds since epoch
    heave: in meters, positive upwards)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode for the attitude, compass, heave and depth
interpolators

Args:
    extrapolation_mode: extrapolate, fail or nearest)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_sensor_configuration = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_to_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_I_NavigationInterpolator_valid = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


