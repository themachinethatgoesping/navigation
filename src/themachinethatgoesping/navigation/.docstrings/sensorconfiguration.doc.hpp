//sourcehash: ec196ee88ddb66fa59d4650882426355c9e5f17d9bec9ceaa4e11bcd0bd35362

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


static const char *mkd_doc_hash = R"doc()doc";

static const char *mkd_doc_hash_operator_call = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration =
R"doc(A coordinate system that allows for specifying sensor offsets (e.g.
gps antenna and attitude sensor) and target offsets (e.g. MBES). Call
the class and specify target_id and current sensor data to derive the
geolocation and attitude of the specified targets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_SensorConfiguration =
R"doc(Construct a new, empty Sensor Coordinate System object After
construction: add sensor offsets and targets (offsets) Then compute
target positions for sensor data)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_add_target =
R"doc(add a target (e.g. MBES) with offsets to the sensor position system

Args:
    target_id: name of the target for reference
    x: x-offset of the target (in meters, positive forward)
    y: y-offset of the target (in meters, positive starboard)
    z: z-offset of the target (in meters, positive down)
    yaw: yaw offset of the target (right-handed around the z-axis) (in
         degrees, 90° = east)
    pitch: pitch offset of the target (right-handed around the y-axis)
           (in degrees, positive = bow up)
    roll: roll offset of the target (right-handed around the x-axis)
          (in degrees, positive = port up))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_add_target_2 =
R"doc(add a target (e.g. MBES) with offsets to the sensor position system

Args:
    target_id: name of the target for reference
    target_offsets: mounting offsets of the target)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_add_targets =
R"doc(add targets (e.g. MBES) with given target_ids and offsets to the
sensor position system

Args:
    targets: map<target_id, target_offsets> of target offsets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_can_merge_targets_with =
R"doc(Check if the given SensorConfiguration includes a target (offsets)
that is incompatible with the given SensorConfiguration targets

Returns:
    false if the same target_id is registered with different offsets,
    true otherwise)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Args:
    target_id: name of the target (e.g. "MBES")
    sensor_data: SensordataLatLon / this structure includes latitude
                 and longitude information

Returns:
    datastructures::GeolocationLatLon  / this structure includes
                   latitude and longitude information)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position_2 =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Args:
    target_id: name of the target (e.g. "MBES")
    sensor_data: SensordataUTM / this structure includes
                 northing/easting and utm zone or hemisphere
                 information

Returns:
    datastructures::GeolocationUTM  / this structure includes
                   northing/easting and utm zone or hemisphere
                   information)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position_3 =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Args:
    target_id: name of the target (e.g. "MBES")
    sensor_data: SensordataLocal / this structure includes
                 northing/easting but no zone or hemisphere
                 information

Returns:
    datastructures::GeolocationLocal  / this structure includes
                   northing/easting but no zone or hemisphere
                   information)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_position_4 =
R"doc(Compute the position of the target "target_id" based on the sensor
data "sensor_data"

Args:
    target_id: name of the target (e.g. "MBES")
    sensor_data: Sensordata / this structure includes no coordinate
                 information

Returns:
    datastructures::GeolocationLocal  / this structure includes
                   northing and east, which are set relative to the
                   sensor coordinate system center)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_from_stream =
R"doc(Read the sensor configuration from a stream.
Warning: there is no error checking!

Args:
    is: 

Returns:
    SensorConfiguration)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_attitude_source =
R"doc(Get the attitude sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the attitude
    sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_depth_source =
R"doc(Get the registered depth sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the depth
    sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_heading_source =
R"doc(Get the registered compass offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the compass)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_position_source =
R"doc(Get the registered position system offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the position
    system)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_system_rotation_as_quat =
R"doc(Compute the rotation of the sensor coordinate system (relative to the
world reference coordinate system) using the sensor data and
(rotation) offsets. Note: if heading is used the
attitude_source_offset yaw will be used to correct the
attitude_source_offset roll and pitch but will not be added to the
heading

Args:
    sensor_data: Sensor data object (used are: heading, pitch, roll)
    offsets_heading_source: Offsets of the compass (used is only yaw
                            offset)
    offsets_attitude_source: Offsets of the IMU (used are yaw, pitch
                             and roll), if heading is used, yaw is
                             used to correct pitch, and roll but not
                             added to the heading

Returns:
    Eigen::Quaternion<float> Rotation of the sensor system compared to
          the world reference system)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target =
R"doc(Get stored target offsets of a specified target

Args:
    target_id: name of the registered target

Returns:
    const datastructures::PositionalOffsets& offsets of the target)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_ids =
R"doc(Get the ids of the registered targets

Returns:
    std::vector<std::string_view>)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_targets =
R"doc(Get the map of stored target offsets objects

Returns:
    const std::unordered_map<std::string,
    datastructures::PositionalOffsets>&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_waterline_offset =
R"doc(Get the waterline offset Negative waterline offset means that z=0 is
below the waterline

Returns:
    waterline_offset)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_has_target =
R"doc(Checks if the sensor configuration has a target with the specified ID.

Args:
    target_id: The ID of the target to check for.

Returns:
    True if the sensor configuration has the target, false otherwise.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_invalidate_hash_cache = R"doc(Invalidate the cached binary hash (call from every mutating method))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_attitude_source = R"doc(Static Roll,Pitch,Yaw (installation) offsets of the attitude sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_depth_source = R"doc(Static xy,z (installation) Offsets of the depth sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_heading_source = R"doc(Static Yaw (installation) Offsets of CompassOffsets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_position_source = R"doc(Static x,y,z (installation) Offsets of the PositionSystem)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_operator_eq =
R"doc(Compare two SensorConfiguration objects for equality

Args:
    other: SensorConfiguration object to compare to

Returns:
    true false)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_operator_ne =
R"doc(Compare two SensorConfiguration objects for inequality

Args:
    other: SensorConfiguration object to compare to

Returns:
    true false)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_remove_target =
R"doc(Remove the target with the specified target_id

Args:
    target_id: name of the registered target)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_remove_targets = R"doc(Remove all stored targets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_attitude_source =
R"doc(Set the attitude sensor offsets

Args:
    sensor_offsets: offsets structure (only yaw, pitch and roll are
                    used))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_attitude_source_2 =
R"doc(Set the attitude sensor offsets

Args:
    yaw: yaw offset of the attitude sensor (right-handed around the
         z-axis) (in degrees, 90° = east)
    pitch: pitch offset of the attitude sensor (right-handed around
           the y-axis) (in degrees, positive = bow up)
    roll: roll offset of the attitude sensor (right-handed around the
          x-axis) (in degrees, positive = port up))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_depth_source =
R"doc(Set the depth sensor offsets

Args:
    x: x-offset of the depth sensor (in meters, positive forward)
    y: y-offset of the depth sensor (in meters, positive starboard)
    z: z-offset of the depth sensor (in meters, positive down))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_depth_source_2 =
R"doc(Set the depth sensor offsets

Args:
    sensor_offsets: offsets structure (only x, y and z are used))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_heading_source =
R"doc(Set the compass offsets

Args:
    yaw: yaw offset of the compass (right-handed around the z-axis)
         (in degrees, 90° = east))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_heading_source_2 =
R"doc(Set the compass offsets

Args:
    sensor_offsets: offsets structure (only yaw is used))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_source =
R"doc(Set the position system offsets

Args:
    x: x-offset of the depth sensor (in meters, positive forward)
    y: y-offset of the depth sensor (in meters, positive starboard)
    z: z-offset of the depth sensor (in meters, positive down))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_source_2 =
R"doc(Set the position system offsets

Args:
    sensor_offsets: offsets structure (only x, y and z are used))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_waterline_offset =
R"doc(Set the waterline offset Negative waterline offset means that z=0 is
below the waterline

Args:
    waterline_offset:)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_target_offsets = R"doc(TargetId (position in vector) for each registered target_id)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_to_stream =
R"doc(Write the sensor configuration to a stream.
Warning: there is no error checking!

Args:
    os:)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_waterline_offset = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_without_targets =
R"doc(Return the SensorConfiguration object without registered targets

Returns:
    SensorConfiguration)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_hash_value =
R"doc(Boost hash function

Args:
    object: object to hash

Returns:
    std::size_t)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


