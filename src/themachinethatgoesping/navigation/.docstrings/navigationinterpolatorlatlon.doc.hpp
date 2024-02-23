//sourcehash: 7f9346e2687567e7b00add6657be86bc2ee2fdc63aaab777e829943e01497367

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


static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon =
R"doc(The NavInterpolator class: Interpolate navigation (lat/lon) values and
attitude information and transform the values using the offsets
specified in the sensor configuration class)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_NavigationInterpolatorLatLon =
R"doc(Construct a new i navigationinterpolator interface

Parameter ``sensor_configuration``:
    sensor configuration used for this navigation interpolator

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_NavigationInterpolatorLatLon_2 =
R"doc(Construct a new Navigation Interpolator Lat Lon object from a base
Interpolator

Parameter ``base``:
    Base I_NavigationInterpolator object)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_class_name = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_compute_target_position =
R"doc(Compute the position of the target "target_id" based on the sensor
data for the given timestamp stamp

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``timestamp``:
    timestamp in seconds since epoch

Returns:
    data structure that contains the position of the target in the
    world coordinate system)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_get_sensor_data =
R"doc(Interpolate the saved sensor data for a specified timestamp stamp

Parameter ``timestamp``:
    timestamp in seconds since epoch

Returns:
    data structure that contains the sensor data interpolated for the
    given timestamp stamp)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_interpolator_latitude = R"doc(< interpolator for the latitude data)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_interpolator_latitude_2 =
R"doc(direct reference to the latitude interpolator object

Returns:
    interpolator_latitude&)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_interpolator_longitude = R"doc(< interpolator for the longitude data)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_interpolator_longitude_2 =
R"doc(direct reference to the longitude interpolator object

Returns:
    interpolator_longitude&)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_merge = R"doc(see documentation of I_NavigationInterpolator::merge)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_operator_call =
R"doc(Compute the position of the target "target_id" based on the sensor
data for the given timestamp stamp

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``timestamp``:
    timestamp in seconds since epoch

Returns:
    data structure that contains the position of the target in the
    world coordinate system)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_set_data_position =
R"doc(Set the data of the position system (latitude, longitude)

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``latitude``:
    latitude in °

Parameter ``longitude``:
    longitude in °)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_set_extrapolation_mode =
R"doc(Set the extrapolation mode for all interpolators

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


