//sourcehash: 27fd04c208d97800c0759647c7cb1de6daa51554c102e25a05f5ab5d9a553794

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


static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector =
R"doc(A base template class to store a vector of data elements with
timestamps. Provides direct access to internal vectors via const and
non-const references.

Template Args:
    T_DataType: The type of data elements stored (e.g., Geolocation,
                Sensordata)
    T_Derived: The derived class type (for CRTP pattern))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_DataVector = R"doc(Construct an empty DataVector)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_DataVector_2 =
R"doc(Construct a DataVector with pre-allocated capacity
Args:
    capacity: number of elements to reserve)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_DataVector_3 =
R"doc(Construct a DataVector from existing data
Args:
    timestamps: vector of timestamps
    data: vector of data elements (must be same size as timestamps))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_add_base_info_to_printer = R"doc(Helper for derived class printer)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_at =
R"doc(Get data element at index
Args:
    index: position in the vector

Returns:
    const reference to data element)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_at_2 =
R"doc(Get data element at index (non-const)
Args:
    index: position in the vector

Returns:
    reference to data element)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_clear = R"doc(Clear all elements)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_data = R"doc(data elements)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_data_2 =
R"doc(Get non-const reference to data vector
Returns:
    reference to data elements)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_empty =
R"doc(Check if the vector is empty
Returns:
    true if no elements are stored)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_get_data =
R"doc(Get const reference to data vector
Returns:
    const reference to data elements)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_get_timestamps =
R"doc(Get const reference to timestamps vector
Returns:
    const reference to timestamps)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_read_from_stream = R"doc(Read base data from stream (for derived class from_stream))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_reserve =
R"doc(Reserve capacity for n elements
Args:
    n: number of elements to reserve space for)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_resize =
R"doc(Resize the vectors
Args:
    n: new size)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_size =
R"doc(Get the number of elements
Returns:
    size_t number of elements stored)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_timestamp_at =
R"doc(Get timestamp at index
Args:
    index: position in the vector

Returns:
    timestamp value)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_timestamps = R"doc(timestamps in seconds since epoch)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_timestamps_2 =
R"doc(Get non-const reference to timestamps vector
Returns:
    reference to timestamps)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_datastructures_DataVector_write_to_stream = R"doc(Write base data to stream (for derived class to_stream))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


