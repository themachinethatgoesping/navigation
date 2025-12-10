//sourcehash: 5946d704ea84bfb1c54747fe06913f1adb8d20a9af9aa12ea751a125d9bd3881

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


static const char *mkd_doc__unnamed_class_at_themachinethatgoesping_navigation_navtools_hpp_594_67 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_compute_latlon_distance_m =
R"doc(Compute the distance in meters between two latitude-longitude
coordinates using the WGS84 ellipsoid.

Args:
    lat1: Latitude of the first coordinate.
    lon1: Longitude of the first coordinate.
    lat2: Latitude of the second coordinate.
    lon2: Longitude of the second coordinate.

Template Args:
    T_float: Floating-point type for latitude and longitude values.

Returns:
    Distance between the two coordinates in meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_compute_latlon_distance_m_2 =
R"doc(Compute the distance in meters between two latitude-longitude
coordinates using the WGS84 ellipsoid.

Args:
    geolocation_latlon_1: First latitude-longitude coordinate.
    geolocation_latlon_2: Second latitude-longitude coordinate.

Template Args:
    T_latlon_holder: Type that holds latitude and longitude values.

Returns:
    Distance between the two coordinates in meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_compute_latlon_distance_m_3 =
R"doc(Compute the distance in meters between two latitude-longitude
coordinates using the WGS84 ellipsoid.

Args:
    geolocation_latlon_1: First latitude-longitude coordinate.
    geolocation_latlon_2: Second latitude-longitude coordinate.

Template Args:
    T_latlon_holder: Type that holds latitude and longitude values as
                     a pair of floats.

Returns:
    Distance between the two coordinates in meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_compute_latlon_distances_m =
R"doc(Compute the distances in meters between consecutive latitude-longitude
coordinates using the WGS84 ellipsoid.

Args:
    latitudes: Vector of latitude values.
    longitudes: Vector of longitude values.

Template Args:
    T_return_container: Type of container to store the distances.
    T_float_container: Type of container that holds latitude and
                       longitude values as floats.

Returns:
    Vector of distances between consecutive coordinates in meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_compute_latlon_distances_m_2 =
R"doc(Compute the distances in meters between consecutive latitude-longitude
coordinates using the WGS84 ellipsoid.

Args:
    geo_locations_latlon: Vector of latitude-longitude coordinates.

Template Args:
    T_return_container: Type of container to store the distances.
    T_container: Type of container that holds latitude and longitude
                 values as a latlon holder type.

Returns:
    Vector of distances between consecutive coordinates in meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_cumulative_latlon_distances_m =
R"doc(Compute the cumulative distances in meters between consecutive
latitude-longitude coordinates using the WGS84 ellipsoid.

Args:
    latitudes: Vector of latitude values.
    longitudes: Vector of longitude values.

Template Args:
    T_return_container: Type of container to store the distances.
    T_float_container: Type of container that holds latitude and
                       longitude values as floats.

Returns:
    Vector of cumulative distances between consecutive coordinates in
    meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_cumulative_latlon_distances_m_2 =
R"doc(Compute the cumulative distances in meters between consecutive
latitude-longitude coordinates using the WGS84 ellipsoid.

Args:
    geo_locations_latlon: Vector of latitude-longitude coordinates.

Template Args:
    T_return_container: Type of container to store the distances.
    T_container: Type of container that holds latitude and longitude
                 values as a latlon holder type.

Returns:
    Vector of cumulative distances between consecutive coordinates in
    meters.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_dms_to_string = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_latitude_to_string =
R"doc(convert a latitude value to a string

Args:
    latitude: value to be converted
    precision: number of digits behind the .
    format: latlon format (degrees°N/S, degrees°minutes'N/S or
            degrees°minutes'seconds''N/S)

Returns:
    converted latitude string)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_latlon_to_utm =
R"doc(Convert latitudes and longitudes to utm coordinates using
GeographicLib

Args:
    lat: list of latitudes
    lon: list of longitudes
    setzone: utm output zone number (1-60), default (-1) determines
             zone using mean latitude and longitude

Returns:
    std::tuple<std::vector<double>, std::vector<double>, int, bool>)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_longitude_to_string =
R"doc(convert a latitude value to a string

Args:
    latitude: value to be converted
    precision: number of digits behind the .
    format: latlon format (degrees°N/S, degrees°minutes'N/S or
            degrees°minutes'seconds''N/S)

Returns:
    converted latitude string)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_t_latlon_format = R"doc(lat/lon format specifications)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_t_latlon_format_degrees = R"doc(lat/lon will be converted to degrees.degrees°N/S E/W)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_t_latlon_format_minutes = R"doc(lat/lon will be converted to degrees°minutes.minutes'E/S E/W)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_t_latlon_format_seconds = R"doc(lat/lon will be converted to degrees°minutes'seconds.seconds''E/S E/W)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_utm_to_latlon =
R"doc(Convert utm coordinates to latitude longitude using Geographic lib

Args:
    northing: northing in meters
    easting: easting in meters
    zone: utm zone number (1-60)
    northern_hemisphere: if true, northern hemisphere, else southern
                         hemisphere

Returns:
    (list of latitude, list of longitudes))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_navtools_utm_to_latlon_2 =
R"doc(Convert utm coordinates to latitude longitude using Geographic lib

Args:
    northing: northing in meters
    easting: easting in meters
    zone: utm zone number (1-60)
    northern_hemisphere: if true, northern hemisphere, else southern
                         hemisphere

Returns:
    (list of latitude, list of longitudes))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


