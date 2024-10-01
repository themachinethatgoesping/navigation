//sourcehash: e67bcbb972606f96dd0a8c79a67ff978d5cd5dae9920342c734757168e8f5f74

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


static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator =
R"doc(The NavInterpolator class: Interpolate attitude information and
transform the values using the offsets specified in the sensor
configuration class This is an interface class that specifies attitude
information but not the position)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_I_NavigationInterpolator =
R"doc(Construct a new i navigationinterpolator interface

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_add_target =
R"doc(add a target sensor with positional offsets

Parameter ``target_id``:
    name of the target sensor

Parameter ``x``:
    x position of the sensor in m, positive forward

Parameter ``y``:
    y position of the sensor in m, positive starboard

Parameter ``z``:
    z position of the sensor in m, positive down

Parameter ``yaw``:
    yaw angle of the sensor in °, positive clockwise

Parameter ``pitch``:
    pitch angle of the sensor in °, positive is bow up

Parameter ``roll``:
    roll angle of the sensor in °, positive is port up)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_add_target_2 =
R"doc(add a target sensor with positional offsets

Parameter ``target_id``:
    name of the target sensor

Parameter ``sensor_offsets``:
    structure that contains the sensor position)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_class_name = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_get_sensor_configuration =
R"doc(direct reference to the sensor configuration

Returns:
    SensorConfiguration&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude = R"doc(< interpolator that stores attitude data (pitch and roll))doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude_2 =
R"doc(direct reference to the attitude data interpolator

Returns:
    interpolator_attitude&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth =
R"doc(< interpolator that stores depth data (depth, positive downwards) <
[m])doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth_2 =
R"doc(direct reference to the depth data interpolator

Returns:
    interpolator_depth&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading = R"doc(< interpolator that stores compass data (yaw/heading) [°])doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading_2 =
R"doc(direct reference to the compass data interpolator

Returns:
    interpolator_heading&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave =
R"doc(< interpolator that stores heave data (relative change in depth, <
positive upwards) [m])doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave_2 =
R"doc(direct reference to the depth data interpolator

Returns:
    interpolator_depth&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_merge =
R"doc(Merge data from another interpolator. Only works of the
SensorConfiguration is compatible.

Parameter ``other``:)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_sensor_configuration = R"doc(< sensor configuration that stores the offsets)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_attitude =
R"doc(Set the attitude data (no yaw, this is set in set_data_heading)

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``pitch``:
    in °, positive is bow up

Parameter ``roll``:
    in °, positive is port up)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_depth =
R"doc(Set the depth data

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``depth``:
    in meters, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_heading =
R"doc(Set the compass data

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``heading``:
    in °, positive clockwise (north is 0°))doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_heave =
R"doc(Set the heave data

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``heave``:
    in meters, positive upwards)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode for the attitude, compass, heave and depth
interpolators

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_sensor_configuration = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_valid = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


