/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.
 */

#define __EXPAND(x)                                      x
#define __COUNT(_1, _2, _3, _4, _5, _6, _7, COUNT, ...)  COUNT
#define __VA_SIZE(...)                                   __EXPAND(__COUNT(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1))
#define __CAT1(a, b)                                     a ## b
#define __CAT2(a, b)                                     __CAT1(a, b)
#define __DOC1(n1)                                       __doc_##n1
#define __DOC2(n1, n2)                                   __doc_##n1##_##n2
#define __DOC3(n1, n2, n3)                               __doc_##n1##_##n2##_##n3
#define __DOC4(n1, n2, n3, n4)                           __doc_##n1##_##n2##_##n3##_##n4
#define __DOC5(n1, n2, n3, n4, n5)                       __doc_##n1##_##n2##_##n3##_##n4##_##n5
#define __DOC6(n1, n2, n3, n4, n5, n6)                   __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define __DOC7(n1, n2, n3, n4, n5, n6, n7)               __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define DOC(...)                                         __EXPAND(__EXPAND(__CAT2(__DOC, __VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets =
R"doc(A structure to set sensor or target offsets relative to the vessel
coordinate system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_SensorPositionOffsets = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_SensorPositionOffsets_2 =
R"doc(Construct a new SensorPositionOffsets object

Parameter ``x``:
    in m, positive foorward

Parameter ``y``:
    in m, positive starboard

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_x = R"doc(< in m, positive foorward)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_y = R"doc(< in m, positive starboard)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorPositionOffsets_z = R"doc(< in m, positive downwards)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

