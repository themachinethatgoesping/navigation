//sourcehash: 5946d704ea84bfb1c54747fe06913f1adb8d20a9af9aa12ea751a125d9bd3881

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


static const char *__doc__unnamed_class_at_themachinethatgoesping_navigation_navtools_hpp_594_67 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_compute_latlon_distance_m =
R"doc(Compute the distance in meters between two latitude-longitude
coordinates using the WGS84 ellipsoid.

Template parameter ``T_float``:
    Floating-point type for latitude and longitude values.

Parameter ``lat1``:
    Latitude of the first coordinate.

Parameter ``lon1``:
    Longitude of the first coordinate.

Parameter ``lat2``:
    Latitude of the second coordinate.

Parameter ``lon2``:
    Longitude of the second coordinate.

Returns:
    Distance between the two coordinates in meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_compute_latlon_distance_m_2 =
R"doc(Compute the distance in meters between two latitude-longitude
coordinates using the WGS84 ellipsoid.

Template parameter ``T_latlon_holder``:
    Type that holds latitude and longitude values.

Parameter ``geolocation_latlon_1``:
    First latitude-longitude coordinate.

Parameter ``geolocation_latlon_2``:
    Second latitude-longitude coordinate.

Returns:
    Distance between the two coordinates in meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_compute_latlon_distance_m_3 =
R"doc(Compute the distance in meters between two latitude-longitude
coordinates using the WGS84 ellipsoid.

Template parameter ``T_latlon_holder``:
    Type that holds latitude and longitude values as a pair of floats.

Parameter ``geolocation_latlon_1``:
    First latitude-longitude coordinate.

Parameter ``geolocation_latlon_2``:
    Second latitude-longitude coordinate.

Returns:
    Distance between the two coordinates in meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_compute_latlon_distances_m =
R"doc(Compute the distances in meters between consecutive latitude-longitude
coordinates using the WGS84 ellipsoid.

Template parameter ``T_return_container``:
    Type of container to store the distances.

Template parameter ``T_float_container``:
    Type of container that holds latitude and longitude values as
    floats.

Parameter ``latitudes``:
    Vector of latitude values.

Parameter ``longitudes``:
    Vector of longitude values.

Returns:
    Vector of distances between consecutive coordinates in meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_compute_latlon_distances_m_2 =
R"doc(Compute the distances in meters between consecutive latitude-longitude
coordinates using the WGS84 ellipsoid.

Template parameter ``T_return_container``:
    Type of container to store the distances.

Template parameter ``T_container``:
    Type of container that holds latitude and longitude values as a
    latlon holder type.

Parameter ``geo_locations_latlon``:
    Vector of latitude-longitude coordinates.

Returns:
    Vector of distances between consecutive coordinates in meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_cumulative_latlon_distances_m =
R"doc(Compute the cumulative distances in meters between consecutive
latitude-longitude coordinates using the WGS84 ellipsoid.

Template parameter ``T_return_container``:
    Type of container to store the distances.

Template parameter ``T_float_container``:
    Type of container that holds latitude and longitude values as
    floats.

Parameter ``latitudes``:
    Vector of latitude values.

Parameter ``longitudes``:
    Vector of longitude values.

Returns:
    Vector of cumulative distances between consecutive coordinates in
    meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_cumulative_latlon_distances_m_2 =
R"doc(Compute the cumulative distances in meters between consecutive
latitude-longitude coordinates using the WGS84 ellipsoid.

Template parameter ``T_return_container``:
    Type of container to store the distances.

Template parameter ``T_container``:
    Type of container that holds latitude and longitude values as a
    latlon holder type.

Parameter ``geo_locations_latlon``:
    Vector of latitude-longitude coordinates.

Returns:
    Vector of cumulative distances between consecutive coordinates in
    meters.)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_dms_to_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_latitude_to_string =
R"doc(convert a latitude value to a string

Parameter ``latitude``:
    value to be converted

Parameter ``precision``:
    number of digits behind the .

Parameter ``format``:
    latlon format (degrees°N/S, degrees°minutes'N/S or
    degrees°minutes'seconds''N/S)

Returns:
    converted latitude string)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_latlon_to_utm =
R"doc(Convert latitudes and longitudes to utm coordinates using
GeographicLib

Parameter ``lat``:
    list of latitudes

Parameter ``lon``:
    list of longitudes

Parameter ``setzone``:
    utm output zone number (1-60), default (-1) determines zone using
    mean latitude and longitude

Returns:
    std::tuple<std::vector<double>, std::vector<double>, int, bool>)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_longitude_to_string =
R"doc(convert a latitude value to a string

Parameter ``latitude``:
    value to be converted

Parameter ``precision``:
    number of digits behind the .

Parameter ``format``:
    latlon format (degrees°N/S, degrees°minutes'N/S or
    degrees°minutes'seconds''N/S)

Returns:
    converted latitude string)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format = R"doc(lat/lon format specifications)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_degrees = R"doc(< lat/lon will be converted to degrees.degrees°N/S E/W)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_minutes = R"doc(< lat/lon will be converted to degrees°minutes.minutes'E/S E/W)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_seconds =
R"doc(< lat/lon will be converted to degrees°minutes'seconds.seconds''E/S
E/W)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_utm_to_latlon =
R"doc(Convert utm coordinates to latitude longitude using Geographic lib

Parameter ``northing``:
    northing in meters

Parameter ``easting``:
    easting in meters

Parameter ``zone``:
    utm zone number (1-60)

Parameter ``northern_hemisphere``:
    if true, northern hemisphere, else southern hemisphere

Returns:
    (list of latitude, list of longitudes))doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_utm_to_latlon_2 =
R"doc(Convert utm coordinates to latitude longitude using Geographic lib

Parameter ``northing``:
    northing in meters

Parameter ``easting``:
    easting in meters

Parameter ``zone``:
    utm zone number (1-60)

Parameter ``northern_hemisphere``:
    if true, northern hemisphere, else southern hemisphere

Returns:
    (list of latitude, list of longitudes))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


