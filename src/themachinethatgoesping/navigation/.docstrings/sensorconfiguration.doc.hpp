//sourcehash: d6d27e823367c0a8c220608b5f0d9ffbb53b2c4571ae1296c747d994b6bb4914

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_add_target_subarray =
R"doc(Register (or overwrite) a single named subarray offset for a target.

A subarray offset is a small SensorPose in the target (transducer)
frame that compute_target_pose can add to the target pose to obtain
the pose of a specific transmit subarray or the receive-array phase
center. The position is always applied; the rotation is only composed
when it is not the identity (see SensorPose::has_zero_rotation).

Args:
    target_id: parent target
    subarray_id: name of the subarray (e.g. "0"/"1"/"2" for tx
                 port/center/starboard, "RX")
    subarray_offsets: offset pose in the target frame)doc";

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_combine_target_subarray =
R"doc(Combine a target pose with a subarray offset (target/array frame) into
the vessel-static frame.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_compute_position_system_offset =
R"doc(Compute the location of the active position-system reference point
relative to the vessel reference point, in the surface (reference-
heading) frame.

This is the heading-referenced translation between the position system
and the vessel reference point: vessel_rotation(reference_heading) ·
position_source_lever_arm. It carries the full horizontal antenna
lever arm (not only its vertical component), so it can be used to
convert beam positions referenced to the positioning system (e.g.
Kongsberg .all XYZ88) into the vessel-reference-point convention (e.g.
Kongsberg .kmall).

Args:
    sensor_data: Sensordata (heading/pitch/roll are used)
    reference_heading_in_degrees: heading (deg) removed from the
                                  orientation (transmit heading); 0 =
                                  keep the absolute world heading
    at_waterline: if true, replace the antenna height by the waterline
                  offset, i.e. project the position-system point onto
                  the water surface (the horizontal reference of the
                  .all XYZ88 beam positions); if false, use the true
                  antenna height (position_source.z)

Returns:
    {x, y, z} of the position-system reference point in the surface
    frame (metres))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_compute_target_pose =
R"doc(Compute the ready-to-trace pose (position + ship-frame orientation) of
a target.

Unlike compute_target_position (which returns a geolocation), this
bakes the target installation, the vessel attitude and the removal of
a common reference heading into a single pose, so a raytracer can
consume it without re-composing installation/attitude/heading. The
orientation is vessel_rotation(reference_heading) ·
target_installation and the position is that SAME reference-relative
vessel_rotation applied to the body-frame lever arm (z reduced to the
depth below the waterline). Pass the SAME reference_heading (the
heading at transmit time) for every target of a ping so all poses
share one surface frame.

Args:
    target_id: name of the target (e.g. "MBES")
    sensor_data: Sensordata (heading/pitch/roll + depth/heave)
    reference_heading_in_degrees: heading (deg) removed from the
                                  orientation (transmit heading)
    subarray_id: optional name of a registered subarray offset of the
                 target to add to the pose (e.g. "0"/"1"/"2" for a
                 transmit subarray, "RX" for the receive phase
                 center); "" = none
    subarray_pose: optional explicit subarray offset (target frame)
                   that overrides ``subarray_id;`` handy for debugging
                   or one-off corrections

Returns:
    target pose (position + ship-frame Rotation))doc";

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_ensure_subarray_poses =
R"doc((Re)build _target_subarray_poses from the current targets + subarray
offsets if stale.)doc";

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
    const datastructures::SensorPose& offsets of the attitude sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_depth_source =
R"doc(Get the registered depth sensor offsets

Returns:
    const datastructures::SensorPose& offsets of the depth sensor)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_heading_source =
R"doc(Get the registered compass offsets

Returns:
    const datastructures::SensorPose& offsets of the compass)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_model_name = R"doc(Echosounder model name, or empty string if not set.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_model_subarray_offset =
R"doc(A single hardcoded subarray offset for a model (convenience for
building a manual
       subarray_pose, e.g. for compute_target_pose debugging).
Args:
    model_name: echosounder model
    subarray_id: "0"/"1"/"2"/"RX"

Returns:
    the offset pose (throws std::out_of_range if the model or subarray
    is unknown))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_model_subarray_offsets =
R"doc(Hardcoded transmit/receive subarray phase-center offsets for a known
echosounder model.

Returns a flat map with the transmit subarrays keyed "0" (port), "1"
(center), "2" (starboard) — or just "0" for single-array systems —
plus the receive-array phase center keyed "RX". All offsets are
SensorPoses in the transducer frame (x forward, y starboard, z down,
metres). The map is empty for an unknown model. Source: QPS dm-0423 /
Kongsberg.

Args:
    model_name: echosounder model (case-insensitive, optional leading
                "EM" ignored))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_position_source =
R"doc(Get the registered position system offsets

Returns:
    const datastructures::SensorPose& offsets of the position system)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_position_source_motion_compensated =
R"doc(Get whether the position source is motion compensated.

See set_position_source_motion_compensated.

Returns:
    true if the logged position is already re the vessel reference
    point)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_printer_style = R"doc(current print() table layout (see set_printer_style))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_system_rotation =
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
    reference_heading_in_degrees: heading (deg) removed from the
                                  result so it is expressed relative
                                  to that heading (0 = absolute world
                                  heading)

Returns:
    Rotation of the sensor system relative to the (reference) world
    reference system)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target =
R"doc(Get stored target offsets of a specified target

Args:
    target_id: name of the registered target

Returns:
    const datastructures::SensorPose& offsets of the target)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_2 =
R"doc(Get a target's static pose, optionally combined with one of its
subarray phase centers.

The subarray offset lives in the target (transducer/array) frame; the
returned combined pose is in the vessel-static frame (independent of
vessel attitude), so compute_target_pose can rotate it in one step.
Registered subarrays return a precomputed pose; a custom
``subarray_pose`` is combined on the fly.

Args:
    target_id: registered target
    subarray_id: registered subarray of the target ("" = none, returns
                 the plain target)
    subarray_pose: optional explicit subarray offset (target frame)
                   overriding ``subarray_id``

Returns:
    the (combined) target pose in the vessel-static frame)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_ids =
R"doc(Get the ids of the registered targets

Returns:
    std::vector<std::string_view>)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_subarray =
R"doc(Get a single registered subarray offset.
Args:
    target_id: parent target
    subarray_id: name of the subarray

Returns:
    the subarray offset pose (throws std::out_of_range if not
    registered))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_subarray_ids = R"doc(Ids of the subarray offsets registered for a target (empty if none).)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_subarrays =
R"doc(Get all subarray offsets of a target.
Args:
    target_id: parent target

Returns:
    map<subarray_id, offset pose> (throws std::out_of_range if the
    target has none))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_targets =
R"doc(Get the map of stored target offsets objects

Returns:
    const std::unordered_map<std::string, datastructures::SensorPose>&)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_transducer_configuration = R"doc(Transducer configuration string, or empty string if not set.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_get_vessel_rotation =
R"doc(Compute the offset-corrected vessel orientation as a Rotation.

Applies the registered sensor mounting offsets to the raw sensor_data
attitude: the attitude source (IMU) mounting offset is removed with a
rotation operation (raw ⊗ offset⁻¹, i.e. yaw/pitch/roll are NOT simply
added) and the heading source offset is subtracted from the heading --
both only when they are not already applied to the logged data
(SensorPose::ypr_offsets_applied). The heading is then expressed
relative to reference_heading_in_degrees. Use rotation.ypr() to obtain
the {yaw, pitch, roll} angles.

Args:
    sensor_data: Sensordata (only heading, pitch and roll are used)
    reference_heading_in_degrees: heading (deg) removed from the
                                  orientation so the result is
                                  expressed in the surface frame of
                                  that heading (0 = keep the absolute
                                  world heading); for a receive pose
                                  sampled after transmit this keeps
                                  the residual yaw (vessel turn since
                                  transmit)

Returns:
    vessel orientation (Rotation), heading measured relative to
    reference_heading)doc";

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_has_target_subarray = R"doc(true if the target has a subarray offset with the given id.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_has_target_subarrays = R"doc(true if the target has any registered subarray offsets.)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_invalidate_hash_cache =
R"doc(Invalidate the cached binary hash and derived caches (call from every
mutating method))doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_model_name = R"doc(echosounder model (e.g. "EM2040"); set by format readers)doc";

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_position_source_motion_compensated = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_printer_style_a =
R"doc(Display preference for __printer__ only (NOT serialized, NOT part of
equality/hash): true = one row per target (compact table); false =
transposed (fields as rows, with an explanation column). Toggle with
set_printer_style / print(optionA=...).)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_remove_target =
R"doc(Remove the target with the specified target_id

Args:
    target_id: name of the registered target)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_remove_target_subarrays = R"doc(Remove all subarray offsets of a target.)doc";

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_model_name = R"doc(Set the echosounder model name (e.g. "EM2040", "EM710").)doc";

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

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_source_motion_compensated =
R"doc(Set whether the position source is motion compensated.

When true, the logged position is already referenced to the vessel
reference point (the PU applied the antenna-to-reference-point lever
arm, e.g. Kongsberg .all P{n}M=1 or .kmall POSI C=On). In that case
compute_position_system_offset returns {0,0,0} instead of the
geometric antenna lever arm, so beam positions referenced to the
positioning system are not double-corrected.

Args:
    motion_compensated: true if the position is already re the vessel
                        reference point)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_printer_style =
R"doc(select the print()/info_string() table layout: true = one row per
target (default, compact), false = transposed (fields x/y/z/... as
rows, records as columns + explanation).)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_subarrays_by_role =
R"doc(Attach a flat subarray-offset map to every registered target by its
role, so a head only carries the offsets of the array(s) it actually
contains.

The transmit subarrays (all keys except "RX") are attached to transmit
targets (id starts with "TX"), the receive phase center ("RX") to
receive targets (id starts with "RX"), and a combined transmit/receive
target (id starts with "TRX") receives both. Targets that match no
role (e.g. "0") are left untouched. No-op if ``subarrays`` is empty.

Args:
    subarrays: flat map<subarray_id, offset pose> as returned by
               get_model_subarray_offsets)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_target_subarrays =
R"doc(Replace all subarray offsets of a target with the given map.
Args:
    target_id: parent target
    subarrays: map<subarray_id, offset pose in the target frame>)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_target_subarrays_from_model =
R"doc(Set the subarray offsets of a target from the hardcoded per-model
preset.

Looks the model up with get_model_subarray_offsets and stores the
result on ``target_id.`` Does nothing if the model is unknown
(get_model_subarray_offsets returns an empty map).

Args:
    target_id: parent target
    model_name: echosounder model (e.g. "EM2040", "EM2040P", "2042");
                case-insensitive, an optional leading "EM" is ignored)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_transducer_configuration =
R"doc(Set the transducer configuration string (e.g. "DualRx",
"SingleTxSingleRx", "STC0").)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_set_waterline_offset =
R"doc(Set the waterline offset Negative waterline offset means that z=0 is
below the waterline

Args:
    waterline_offset:)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_subarray_poses_cached =
R"doc(Derived cache: each registered subarray phase center combined with its
target, expressed in the vessel-static frame (position target.xyz +
target.rotation·subarray.xyz, rotation
target.rotation·subarray.rotation). Keyed [target_id][subarray_id] —
linked to _target_subarray_offsets by the same keys — and rebuilt on
demand whenever the configuration changes. Not serialized (fully
derived from _target_offsets + _target_subarray_offsets).)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_target_offsets = R"doc(TargetId (position in vector) for each registered target_id)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_target_subarray_offsets =
R"doc(Optional named subarray offsets per target. Keyed
[target_id][subarray_id]; each entry is a SensorPose in the target
(transducer) frame that compute_target_pose can add to the target pose
to obtain a per-subarray phase center (e.g. multibeam transmit
subarrays port/center/starboard and the receive-array phase center).)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_target_subarray_poses = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_to_stream =
R"doc(Write the sensor configuration to a stream.
Warning: there is no error checking!

Args:
    os:)doc";

static const char *mkd_doc_themachinethatgoesping_navigation_SensorConfiguration_transducer_configuration = R"doc(configuration string (e.g. "DualRx", "STC0"); set by format readers)doc";

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


