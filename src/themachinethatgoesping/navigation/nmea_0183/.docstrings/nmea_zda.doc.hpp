//sourcehash: d03f4cf2dbab3409a964e14f73f0f8e247817777045091e773df7884f18cc07d

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


static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA =
R"doc( The NMEA ZDA datagram contains the universal time code (UTC),
 get_day, get_month, get_year
and local time zone offsets.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_NMEA_ZDA =
R"doc(Construct a new nmea zda object from an existing NMEA_Base datagram

Args:
    base: Underlying NMEA_Base datagram
    check: Check if the NMEA string is valid)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_get_day = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_get_local_zone_hours = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_get_local_zone_minutes = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_get_month = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_get_utc_time_string = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_get_year = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_to_date_string =
R"doc(Convert the datagram into a date time string
       Note: this function uses to_timestamp()

Args:
    format: Format string (see https://howardhinnant.github.io/date/da
            te.html#to_stream_formatting)

Returns:
    date time string)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_to_timestamp =
R"doc(Convert the datagram into a unixtime stamp

Returns:
    unixtime (seconds since 1970-01-01 00:00:00 UTC))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


