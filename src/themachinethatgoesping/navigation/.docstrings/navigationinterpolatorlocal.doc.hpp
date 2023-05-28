//sourcehash: ad0d5c75d3ce6a8aab1cae270cf40aef029b72deb98c16c442bd09047fe1d114

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


static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal =
R"doc(The NavInterpolator class: Interpolate navigation (northing/easting no
zone specified) values and attitude information and transform the
values using the offsets specified in the sensor configuration class)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_NavigationInterpolatorLocal =
R"doc(Construct a new i navigationinterpolator interface

Parameter ``sensor_configuration``:
    sensor configuration used for this navigation interpolator

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_NavigationInterpolatorLocal_2 =
R"doc(Construct a new Navigation Interpolator Lat Lon object from a base
Interpolator

Parameter ``base``:
    Base I_NavigationInterpolator object)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_compute_target_position =
R"doc(Compute the position of the target "target_id" based on the sensor
data for the given timestamp stamp

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``timestamp``:
    timestamp in seconds since epoch

Returns:
    data structure that contains the position of the target in the
    world coordinate system)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_get_sensor_data =
R"doc(Interpolate the saved sensor data for a specified timestamp stamp

Parameter ``timestamp``:
    timestamp in seconds since epoch

Returns:
    data structure that contains the sensor data interpolated for the
    given timestamp stamp)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_interpolator_easting = R"doc(< interpolator for the easting data)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_interpolator_easting_2 =
R"doc(direct reference to the easting interpolator object

Returns:
    interpolator_easting&)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_interpolator_northing = R"doc(< interpolator for the northing data)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_interpolator_northing_2 =
R"doc(direct reference to the northing interpolator object

Returns:
    interpolator_northing&)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_merge = R"doc(see documentation of I_NavigationInterpolator::merge)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_set_data_position =
R"doc(Set the data of the position system (northing, easting)

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``northing``:
    northing in meters

Parameter ``easting``:
    easting in meters)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_set_data_position_2 =
R"doc(Set the data of the position system (northing, easting) and the
offsets of the position system

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``northing``:
    in meters

Parameter ``easting``:
    in meters

Parameter ``name``:
    of the position system

Parameter ``offset_x``:
    in m, positive forward

Parameter ``offset_y``:
    in m, positive starboard

Parameter ``offset_z``:
    in m, positive down)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_set_data_position_3 =
R"doc(Set the data of the position system (northing, easting) and the
offsets of the position system

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``northing``:
    in meters

Parameter ``easting``:
    in meters

Parameter ``sensor_offsets``:
    structure containing the offsets of the position system)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_set_extrapolation_mode =
R"doc(Set the extrapolation mode for all interpolators

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


