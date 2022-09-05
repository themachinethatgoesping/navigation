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


static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator =
R"doc(The NavInterpolator class: Interpolate attitude information and
transform the values using the offsets specified in the sensor
configuration class This is an interface class that specifies attitude
information but not the position)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_I_NavigationInterpolator =
R"doc(Construct a new i navigationinterpolator interface

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_I_NavigationInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_add_target =
R"doc(add a target sensor with positional offsets

Parameter ``target_id``:
    name of the target sensor

Parameter ``x``:
    x position of the sensor in m, positive forward

Parameter ``y``:
    y position of the sensor in m, positive starboard

Parameter ``z``:
    z position of the sensor in m, positive down

Parameter ``yaw``:
    yaw angle of the sensor in °, positive clockwise

Parameter ``pitch``:
    pitch angle of the sensor in °, positive is bow up

Parameter ``roll``:
    roll angle of the sensor in °, positive is port up)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_add_target_2 =
R"doc(add a target sensor with positional offsets

Parameter ``target_id``:
    name of the target sensor

Parameter ``sensor_offsets``:
    structure that contains the sensor position)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude = R"doc(< interpolator that stores attitude data (pitch and roll))doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_attitude_2 =
R"doc(direct reference to the attitude data interpolator

Returns:
    interpolator_attitude&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth =
R"doc(< interpolator that stores depth data (depth, positive downwards) <
[m])doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_depth_2 =
R"doc(direct reference to the depth data interpolator

Returns:
    interpolator_depth&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading = R"doc(< interpolator that stores compass data (yaw/heading) [°])doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heading_2 =
R"doc(direct reference to the compass data interpolator

Returns:
    interpolator_heading&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave =
R"doc(< interpolator that stores heave data (relative change in depth, <
positive upwards) [m])doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_interpolator_heave_2 =
R"doc(direct reference to the depth data interpolator

Returns:
    interpolator_depth&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_sensor_configuration = R"doc(< sensor configuration that stores the offsets)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_sensor_configuration_2 =
R"doc(direct reference to the sensor configuration

Returns:
    SensorConfiguration&)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_attitude =
R"doc(Set the attitude data (no yaw, ythis is set in set_data_heading)

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``pitch``:
    in °, positive is bow up

Parameter ``roll``:
    in °, positive is port up)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_depth =
R"doc(Set the depth data

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``depth``:
    in meters, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_heading =
R"doc(Set the compass data

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``heading``:
    in °, positive clockwise (north is 0°))doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_data_heave =
R"doc(Set the heave data

Parameter ``timestamp``:
    in seconds since epoch

Parameter ``heave``:
    in meters, positive upwards)doc";

static const char *__doc_themachinethatgoesping_navigation_I_NavigationInterpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode for the attitude, compass, heave and depth
interpolators

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon =
R"doc(The NavInterpolator class: Interpolate navigation (lat/lon) values and
attitude information and transform the values using the offsets
specified in the sensor configuration class)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_NavigationInterpolatorLatLon =
R"doc(Construct a new i navigationinterpolator interface

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_NavigationInterpolatorLatLon_2 = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLatLon_serialize = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal =
R"doc(The NavInterpolator class: Interpolate navigation (northing/easting no
zone specified) values and attitude information and transform the
values using the offsets specified in the sensor configuration class)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_NavigationInterpolatorLocal =
R"doc(Construct a new i navigationinterpolator interface

Parameter ``extrapolation_mode``:
    extrapolate, fail or nearest)doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_NavigationInterpolatorLocal_2 = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_NavigationInterpolatorLocal_serialize = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_offsets_attitude_source =
R"doc(Get the attitude sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the attitude
    sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_offsets_depth_source =
R"doc(Get the registered depth sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the depth
    sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_offsets_heading_source =
R"doc(Get the registered compass offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the compass)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_offsets_position_source =
R"doc(Get the registered position system offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the position
    system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_offsets_target =
R"doc(Get stored target offsets of a specified target

Parameter ``target_id``:
    name of the registered target

Returns:
    const datastructures::PositionalOffsets& offsets of the target)doc";

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
    Eigen::Quaterniond Rotation of the sensor system compared to the
    world reference system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_attitude_source = R"doc(< Static Roll,Pitch,Yaw (installation) offsets of the attitude sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_depth_source = R"doc(< Static xy,z (installation) Offsets of the depth sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_heading_source = R"doc(< Static Yaw (installation) Offsets of CompassOffsets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_offsets_position_source = R"doc(< Static x,y,z (installation) Offsets of the PositionSystem)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_attitude_source =
R"doc(Set the attitude sensor offsets

Parameter ``sensor_offsets``:
    offsets structure (only yaw, pitch and roll are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_attitude_source_2 =
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

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_depth_source =
R"doc(Set the depth sensor offsets

Parameter ``x``:
    x-offset of the depth sensor (in meters, positive forward)

Parameter ``y``:
    y-offset of the depth sensor (in meters, positive starboard)

Parameter ``z``:
    z-offset of the depth sensor (in meters, positive down))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_depth_source_2 =
R"doc(Set the depth sensor offsets

Parameter ``sensor_offsets``:
    offsets structure (only x, y and z are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_heading_source =
R"doc(Set the compass offsets

Parameter ``yaw``:
    yaw offset of the compass (right-handed around the z-axis) (in
    degrees, 90° = east))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_heading_source_2 =
R"doc(Set the compass offsets

Parameter ``sensor_offsets``:
    offsets structure (only yaw is used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_position_source =
R"doc(Set the position system offsets

Parameter ``x``:
    x-offset of the depth sensor (in meters, positive forward)

Parameter ``y``:
    y-offset of the depth sensor (in meters, positive starboard)

Parameter ``z``:
    z-offset of the depth sensor (in meters, positive down))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_offsets_position_source_2 =
R"doc(Set the position system offsets

Parameter ``sensor_offsets``:
    offsets structure (only x, y and z are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_target_offsets = R"doc(< TargetId (position in vector) for each registered target_id)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) This structure does not store any coordinates except the depth
(z))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) Unlike the base GeoLocation object, this also stores latitude
and longitude coordinates)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_2 =
R"doc(Construct an GeoLocationLatLon object from an existing GeoLocationUTM
object (this allows for implicit conversion from GeoLocationUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_GeoLocationLatLon = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_GeoLocationLatLon_2 =
R"doc(Construct a new Sensor Data Lat Lon object using a base sensor data
object

Parameter ``location``:
    $Parameter ``latitude``:

in °, positive northwards

Parameter ``longitude``:
    in °, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_GeoLocationLatLon_3 =
R"doc(Construct an GeoLocationLatLon object from an existing GeoLocationUTM
object (this allows for implicit conversion from GeoLocationUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_GeoLocationLatLon_4 =
R"doc(Construct a new GeoLocationLatLon object

Parameter ``latitude``:
    in °, positive northwards

Parameter ``longitude``:
    in °, positive eastwards

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_latitude = R"doc(< in °, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_longitude = R"doc(< in °, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_operator_eq =
R"doc(Check if two GeoLocationLatLon objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_operator_ne =
R"doc(Construct a new GeoLocationLatLon object from a string

Parameter ``str``:
    string containing the location in the format
    "latitude,longitude,z,yaw,pitch,roll")doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) unlike the default GeoLocation structure, this object stores
local northing and easting coordinates. These coordinates can be
converted to UTM coordinates if the zone and hemisphere are known.)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_GeoLocationLocal = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_GeoLocationLocal_2 =
R"doc(Construct a new GeoLocationLocal object

Parameter ``location``:
    $Parameter ``northing``:

in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_GeoLocationLocal_3 =
R"doc(Construct a new GeoLocationLocal object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_easting = R"doc(< in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_northing = R"doc(< in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_2 =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) unlike the default GeoLocation structure, this object stores
utm coordinates)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_GeoLocationUTM = R"doc(Construct a new Sensor Position object)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_GeoLocationUTM_2 =
R"doc(Construct an GeoLocationUTM object from an existing GeoLocationLocal
object (using a known zone and hemisphere)

Parameter ``location_local``:
    $Parameter ``zone``:

UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_GeoLocationUTM_3 =
R"doc(Construct an GeoLocationUTM object from an existing GeoLocationLatLon
object (this allows for implicit conversion from GeoLocationLatLon
class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_GeoLocationUTM_4 =
R"doc(Construct a new GeoLocationUTM object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``zone``:
    UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_from_geolocation_latlon =
R"doc(Construct convert a GeoLocationLatLon Object to UTM

Parameter ``location``:
    valid GeoLocationLatLon object

Parameter ``setzone``:
    set a preferred UTM zone negative means automatic, zero means UPS,
    positive means a particular UTM zone

Returns:
    GeoLocationUTM)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_northern_hemisphere = R"doc(< if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_to_geolocation_latlon =
R"doc(Convert a utm geolocationlatlon to an unprojected location

Parameter ``location_utm``:
    $Returns:

GeoLocationLatLon)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_zone = R"doc(< UTM/UPS zone number)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_GeoLocation = R"doc(Construct a new Position object)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_GeoLocation_2 =
R"doc(Construct a new GeoLocation object

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_operator_eq =
R"doc(Check if two GeoLocation objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_operator_ne =
R"doc(Construct a new GeoLocation object from a string

Parameter ``str``:
    string containing the location in the format
    "latitude,longitude,z,yaw,pitch,roll")doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_z = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets =
R"doc(A structure to store positional offsets (e.g. of a sensor) relative to
the vessel coordinate system)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_PositionalOffsets = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_PositionalOffsets_2 =
R"doc(Construct a new PositionalOffsets object

Parameter ``x``:
    in m, positive forward

Parameter ``y``:
    in m, positive starboard

Parameter ``z``:
    in m, positive downwards

Parameter ``yaw``:
    positive means clockwise rotation

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_x = R"doc(< in m, positive forward)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_y = R"doc(< in m, positive starboard)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_yaw = R"doc(< in °, positive means clockwise rotation)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_z = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData =
R"doc(A structure to store a georeferenced location and attitude data from
different sensors (e.g. IMU, etc.) No gps coordinates are stored in
this structure (only depth).)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon =
R"doc(A structure to store a georeferenced location and attitude data from
different sensors (e.g. GPS, IMU, etc.))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_2 =
R"doc(Construct an SensorDataLatLon object from an existing SensorDataUTM
object (this allows for implicit conversion from SensorDataUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_SensorDataLatLon = R"doc(Construct a new SensorDataLatLon object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_SensorDataLatLon_2 =
R"doc(Construct a new Sensor Data Lat Lon object using a base sensor data
object

Parameter ``data``:
    $Parameter ``latitude``:

in °, positive northwards

Parameter ``longitude``:
    in °, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_SensorDataLatLon_3 =
R"doc(Construct an SensorDataLatLon object from an existing SensorDataUTM
object (this allows for implicit conversion from SensorDataUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_SensorDataLatLon_4 =
R"doc(Construct a new SensorDataLatLon object

Parameter ``latitude``:
    in °, positive northwards

Parameter ``longitude``:
    in °, positive eastwards

Parameter ``depth``:
    in m, positive downwards

Parameter ``heave``:
    from heave sensor, will be added to depth in m, positive upwards

Parameter ``heading``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_latitude = R"doc(< in °, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_longitude = R"doc(< in °, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_operator_eq =
R"doc(Check if two SensorDataLatLon objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal =
R"doc(A structure to store a georeferenced data and attitude data from
different sensors (e.g. GPS, IMU, etc.) Unlike SensorDataUTM, this
structure stores coordinates without zone and hemisphere information.)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_SensorDataLocal = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_SensorDataLocal_2 =
R"doc(Construct a new Sensor Data Local object using a base sensor data
object

Parameter ``data``:
    $Parameter ``northing``:

in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_SensorDataLocal_3 =
R"doc(Construct a new SensorDataLocal object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``depth``:
    in m, positive downwards

Parameter ``heave``:
    from heave sensor, will be added to depth in m, positive upwards

Parameter ``heading``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_easting = R"doc(< in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_northing = R"doc(< in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_operator_eq =
R"doc(Check if two SensorDataLocal objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_2 =
R"doc(A structure to store a georeferenced data and attitude data from
different sensors (e.g. GPS, IMU, etc.) Unlike SensorDataLatLon, this
structure stores UTM coordinates.)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_2 =
R"doc(Construct a new Sensor Data Local object using a base sensor data
object

Parameter ``data``:
    $Parameter ``northing``:

in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``utm_zone``:
    UTM/UPS zone number

Parameter ``utm_northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_3 =
R"doc(Construct an SensorDataUTM object from an existing SensorDataLocal
object (using a known zone and hemisphere)

Parameter ``data_local``:
    $Parameter ``utm_zone``:

UTM/UPS zone number

Parameter ``utm_northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_4 =
R"doc(Construct an SensorDataUTM object from an existing SensorDataLatLon
object (this allows for implicit conversion from SensorDataLatLon
class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_5 =
R"doc(Construct a new SensorDataUTM object

Parameter ``northing``:
    in m, positive northwards

Parameter ``easting``:
    in m, positive eastwards

Parameter ``utm_zone``:
    UTM/UPS zone number

Parameter ``utm_northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``depth``:
    in m, positive downwards

Parameter ``heave``:
    is added to depth in m, positive upwards

Parameter ``heading``:
    in °, 0° is north, 90° is east

Parameter ``pitch``:
    in °, positive means bow up

Parameter ``roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_from_sensordata =
R"doc(Construct convert a SensorDataLatLon Object to UTM

Parameter ``data``:
    valid SensorDataLatLon object

Parameter ``setzone``:
    set a preferred UTM zone negative means automatic, zero means UPS,
    positive means a particular UTM zone

Returns:
    SensorDataUTM)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_operator_eq =
R"doc(Check if two SensorDataUTM objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_to_sensordata =
R"doc(Convert a utm sensordatalatlon to an unprojected data

Parameter ``data_utm``:
    $Returns:

SensorDataLatLon)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_utm_northern_hemisphere = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_utm_zone = R"doc(< UTM/UPS zone number)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_SensorData = R"doc(Construct a new SensorData object)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_SensorData_2 =
R"doc(Construct a new SensorData object

Parameter ``depth``:
    from depth source, in m, positive downwards

Parameter ``heave``:
    from heave sensor, will be added to depth in m, positive upwards

Parameter ``heading``:
    from heading source, in °, 0° is north, 90° is east

Parameter ``pitch``:
    from attitude source, in °, positive means bow up

Parameter ``roll``:
    from attitude source, in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_depth = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_heading = R"doc(< from heading source in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_heave = R"doc(< from heave source, will be added to depth in m, positive upwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_operator_eq =
R"doc(Check if two SensorData objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_pitch = R"doc(< from attitude source, in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_roll = R"doc(< from attitude source, in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_serialize = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_NMEABase = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_NMEABase_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_fields = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_from_stream_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_field = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_field_as_double = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_field_as_int = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_name = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_sender = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_sentence = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_get_type = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_parse_fields = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_sentence = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_size = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEABase_to_stream_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA =
R"doc(The NMEA GGA datagram contains time, position, and fix. Typically
received from a global navigation satellite system (GNSS device).)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_NMEA_GGA =
R"doc(Construct a new nmea gga object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_age_of_differential_gps_data = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_altitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_coordinated_universal_time = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_differential_reference_station_id = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_geoidal_separation = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_horizontal_dilution_of_precision = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_latitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_longitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_number_of_satellites = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_quality = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GGA_quality_explained = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL =
R"doc(The NMEA GLL datagram contains time, position, and status. Typically
received from a global navigation satellite system (GNSS device).)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_NMEA_GLL =
R"doc(Construct a new nmea gll object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_coordinated_universal_time = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_latitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_longitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_mode_explained = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_GLL_status = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_HDT =
R"doc(The NMEA HDT datagram contains the true vessel heading typically
received from a compass.)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_HDT_NMEA_HDT =
R"doc(Construct a new nmea hdt object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_HDT_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_HDT_heading_degrees_true = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_HDT_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC =
R"doc(The NMEA RMC datagram contains time, date, position, course and speed
data. Typically received from a global navigation satellite system
(GNSS device).)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_NMEA_RMC =
R"doc(Construct a new nmea rmc object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_coordinated_universal_time = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_course_over_ground_degrees_true = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_date = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_latitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_longitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_magnetic_variation = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_mode_explained = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_speed_over_ground_knots = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_status = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_to_date_string =
R"doc(Convert the datagram into a date time string Note: this function uses
to_timestamp()

Parameter ``format``:
    Format string (see https://howardhinnant.github.io/date/date.html#
    to_stream_formatting)

Returns:
    date time string)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_RMC_to_timestamp =
R"doc(Convert the datagram into a unixtime stamp

Returns:
    unixtime (seconds since 1970-01-01 00:00:00 UTC))doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW =
R"doc(The NMEA VHW datagram contains the vessel's compass heading and the
speed relative to the water.)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_NMEA_VHW =
R"doc(Construct a new nmea vhw object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_speed_over_water_kmh = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_speed_over_water_knots = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_vessel_heading_magnetic = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VHW_vessel_heading_true = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW =
R"doc(The NMEA VLW datagram contains the distance of the vessel traveled by
the vessel.)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_NMEA_VLW =
R"doc(Construct a new nmea vlw object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_total_ground_distance_nautical_miles = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_total_water_distance_nautical_miles = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_trip_ground_distance_nautical_miles = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VLW_trip_water_distance_nautical_miles = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG =
R"doc(The NMEA VBW datagram contains the vessels course and speed over
ground.)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_NMEA_VTG =
R"doc(Construct a new nmea vtg object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_course_over_ground_degrees_magnetic = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_course_over_ground_degrees_true = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_speed_over_ground_kmh = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_VTG_speed_over_ground_knots = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA =
R"doc(The NMEA ZDA datagram contains the universal time code (UTC), day,
month, year and local time zone offsets.)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_NMEA_ZDA =
R"doc(Construct a new nmea zda object from an existing NMEABase datagram

Parameter ``base``:
    Underlying NMEABase datagram

Parameter ``check``:
    Check if the NMEA string is valid)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_coordinated_universal_time = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_day = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_local_zone_hours = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_local_zone_minutes = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_month = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_to_date_string =
R"doc(Convert the datagram into a date time string Note: this function uses
to_timestamp()

Parameter ``format``:
    Format string (see https://howardhinnant.github.io/date/date.html#
    to_stream_formatting)

Returns:
    date time string)doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_to_timestamp =
R"doc(Convert the datagram into a unixtime stamp

Returns:
    unixtime (seconds since 1970-01-01 00:00:00 UTC))doc";

static const char *__doc_themachinethatgoesping_navigation_nmea_0183_NMEA_ZDA_year = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

