//sourcehash: 0e512466b36b0524875808d2b763858b95f2bbdd93469771315c6f0b871d11c7

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


static const char *__doc_hash = R"doc()doc";

static const char *__doc_hash_operator_call = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration =
R"doc(A coordinate system that allows for specifying sensor offsets (e.g.
gps antenna and attitude sensor) and target offsets (e.g. MBES). Call
the class and specify target_id and current sensor data to derive the
geolocation and attitude of the specified targets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_SensorConfiguration =
R"doc(Construct a new, empty Sensor Coordinate System object After
construction: add sensor offsets and targets (offsets) Then compute
target positions for sensor data)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_add_target =
R"doc(add a target (e.g. MBES) with offsets to the sensor position system

Parameter ``target_id``:
    name of the target for reference

Parameter ``x``:
    x-offset of the target (in meters, positive forward)

Parameter ``y``:
    y-offset of the target (in meters, positive starboard)

Parameter ``z``:
    z-offset of the target (in meters, positive down)

Parameter ``yaw``:
    yaw offset of the target (right-handed around the z-axis) (in
    degrees, 90° = east)

Parameter ``pitch``:
    pitch offset of the target (right-handed around the y-axis) (in
    degrees, positive = bow up)

Parameter ``roll``:
    roll offset of the target (right-handed around the x-axis) (in
    degrees, positive = port up))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_add_target_2 =
R"doc(add a target (e.g. MBES) with offsets to the sensor position system

Parameter ``target_id``:
    name of the target for reference

Parameter ``target_offsets``:
    mounting offsets of the target)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_add_targets =
R"doc(add targets (e.g. MBES) with given target_ids and offsets to the
sensor position system

Parameter ``targets``:
    map<target_id, target_offsets> of target offsets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_can_merge_targets_with =
R"doc(Check if the given SensorConfiguration includes a target (offsets)
that is incompatible with the given SensorConfiguration targets

Returns:
    false if the same target_id is registered with different offsets,
    true otherwise)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``sensor_data``:
    SensorDataLatLon / this structure includes latitude and longitude
    information

Returns:
    datastructures::GeoLocationLatLon / this structure includes
    latitude and longitude information)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position_2 =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``sensor_data``:
    SensorDataUTM / this structure includes northing/easting and utm
    zone or hemisphere information

Returns:
    datastructures::GeoLocationUTM / this structure includes
    northing/easting and utm zone or hemisphere information)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position_3 =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``sensor_data``:
    SensorDataLocal / this structure includes northing/easting but no
    zone or hemisphere information

Returns:
    datastructures::GeoLocationLocal / this structure includes
    northing/easting but no zone or hemisphere information)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position_4 =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Parameter ``target_id``:
    name of the target (e.g. "MBES")

Parameter ``sensor_data``:
    SensorData / this structure includes no coordinate information

Returns:
    datastructures::GeoLocationLocal / this structure includes
    northing and east, which are set relative to the sensor coordinate
    system center)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_from_stream =
R"doc(Read the sensor configuration from a stream. Warning: there is no
error checking!

Parameter ``is``:
    $Returns:

SensorConfiguration)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_attitude_source =
R"doc(Get the attitude sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the attitude
    sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_depth_source =
R"doc(Get the registered depth sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the depth
    sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_heading_source =
R"doc(Get the registered compass offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the compass)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_position_source =
R"doc(Get the registered position system offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the position
    system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_system_rotation_as_quat =
R"doc(Compute the rotation of the sensor coordinate system (relative to the
world reference coordinate system) using the sensor data and
(rotation) offsets. Note: if heading is used the
attitude_source_offset yaw will be used to correct the
attitude_source_offset roll and pitch but will not be added to the
heading

Parameter ``sensor_data``:
    Sensor data object (used are: heading, pitch, roll)

Parameter ``offsets_heading_source``:
    Offsets of the compass (used is only yaw offset)

Parameter ``offsets_attitude_source``:
    Offsets of the IMU (used are yaw, pitch and roll), if heading is
    used, yaw is used to correct pitch, and roll but not added to the
    heading

Returns:
    Eigen::Quaternion<float> Rotation of the sensor system compared to
    the world reference system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_target =
R"doc(Get stored target offsets of a specified target

Parameter ``target_id``:
    name of the registered target

Returns:
    const datastructures::PositionalOffsets& offsets of the target)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_ids =
R"doc(Get the ids of the registered targets

Returns:
    std::vector<std::string_view>)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_targets =
R"doc(Get the map of stored target offsets objects

Returns:
    const std::unordered_map<std::string,
    datastructures::PositionalOffsets>&)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_attitude_source =
R"doc(< Static Roll,Pitch,Yaw (installation) offsets of the attitude <
sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_depth_source = R"doc(< Static xy,z (installation) Offsets of the depth sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_heading_source = R"doc(< Static Yaw (installation) Offsets of CompassOffsets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_position_source = R"doc(< Static x,y,z (installation) Offsets of the PositionSystem)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_operator_eq =
R"doc(Compare two SensorConfiguration objects for equality

Parameter ``other``:
    SensorConfiguration object to compare to

Returns:
    true

Returns:
    false)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_operator_ne =
R"doc(Compare two SensorConfiguration objects for inequality

Parameter ``other``:
    SensorConfiguration object to compare to

Returns:
    true

Returns:
    false)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_remove_target =
R"doc(Remove the target with the specified target_id

Parameter ``target_id``:
    name of the registered target)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_remove_targets = R"doc(Remove all stored targets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_attitude_source =
R"doc(Set the attitude sensor offsets

Parameter ``sensor_offsets``:
    offsets structure (only yaw, pitch and roll are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_attitude_source_2 =
R"doc(Set the attitude sensor offsets

Parameter ``yaw``:
    yaw offset of the attitude sensor (right-handed around the z-axis)
    (in degrees, 90° = east)

Parameter ``pitch``:
    pitch offset of the attitude sensor (right-handed around the
    y-axis) (in degrees, positive = bow up)

Parameter ``roll``:
    roll offset of the attitude sensor (right-handed around the
    x-axis) (in degrees, positive = port up))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_depth_source =
R"doc(Set the depth sensor offsets

Parameter ``x``:
    x-offset of the depth sensor (in meters, positive forward)

Parameter ``y``:
    y-offset of the depth sensor (in meters, positive starboard)

Parameter ``z``:
    z-offset of the depth sensor (in meters, positive down))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_depth_source_2 =
R"doc(Set the depth sensor offsets

Parameter ``sensor_offsets``:
    offsets structure (only x, y and z are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_heading_source =
R"doc(Set the compass offsets

Parameter ``yaw``:
    yaw offset of the compass (right-handed around the z-axis) (in
    degrees, 90° = east))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_heading_source_2 =
R"doc(Set the compass offsets

Parameter ``sensor_offsets``:
    offsets structure (only yaw is used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_source =
R"doc(Set the position system offsets

Parameter ``x``:
    x-offset of the depth sensor (in meters, positive forward)

Parameter ``y``:
    y-offset of the depth sensor (in meters, positive starboard)

Parameter ``z``:
    z-offset of the depth sensor (in meters, positive down))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_source_2 =
R"doc(Set the position system offsets

Parameter ``sensor_offsets``:
    offsets structure (only x, y and z are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_target_offsets = R"doc(< TargetId (position in vector) for each registered target_id)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_to_stream =
R"doc(Write the sensor configuration to a stream. Warning: there is no error
checking!

Parameter ``os``:)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_without_targets =
R"doc(Return the SensorConfiguration object without registered targets

Returns:
    SensorConfiguration)doc";

static const char *__doc_themachinethatgoesping_navigation_hash_value =
R"doc(Boost hash function

Parameter ``object``:
    object to hash

Returns:
    std::size_t)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


