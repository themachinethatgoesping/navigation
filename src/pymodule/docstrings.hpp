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


static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration =
R"doc(A coordinate system that allows for specifying sensor offsets (e.g.
gps antenna and motion sensor) and target offsets (e.g. MBES). Call
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

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_compass_offsets = R"doc(Static Roll,Pitch,Yaw (installation) offsets of the motion sensor)doc";

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

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_depth_sensor_offsets = R"doc(Static x,y,z (installation) Offsets of the PositionSystem)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_compass_offsets =
R"doc(Get the registered compass offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the compass)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_depth_sensor_offsets =
R"doc(Get the registered depth sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the depth
    sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_motion_sensor_offsets =
R"doc(Get the motion sensor offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the motion
    sensor)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_position_system_offsets =
R"doc(Get the registered position system offsets

Returns:
    const datastructures::PositionalOffsets& offsets of the position
    system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_system_rotation_as_quat =
R"doc(Compute the rotation of the sensor coordinate system (relative to the
world reference coordinate system) using the sensor data and
(rotation) offsets. Note1: If compass_heading in SensorData is NAN,
the imu_yaw is used (and compass_offsets are ignored) Note2: if
compass_heading is used the motion_sensor_offset yaw will be used to
correct the motion_sensor_offset roll and pitch but will not be added
to the heading

Parameter ``sensor_data``:
    Sensor data object (used are: compass_heading, imu_yaw, imu_pitch,
    imu_roll)

Parameter ``compass_offsets``:
    Offsets of the compass (used is only yaw offset)

Parameter ``motion_sensor_offsets``:
    Offsets of the IMU (used are yaw, pitch and roll), if
    compass_heading is used, yaw is used to correct pitch, and roll
    but not added to the heading

Returns:
    Eigen::Quaterniond Rotation of the sensor system compared to the
    world reference system)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_get_target_offsets =
R"doc(Get stored target offsets of a specified target

Parameter ``target_id``:
    name of the registered target

Returns:
    const datastructures::PositionalOffsets& offsets of the target)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_motion_sensor_offsets = R"doc(TargetId (position in vector) for each registered target_id)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_position_system_offsets = R"doc(Static Yaw (installation) Offsets of CompassOffsets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_compass_offsets =
R"doc(Set the compass offsets

Parameter ``yaw``:
    yaw offset of the compass (right-handed around the z-axis) (in
    degrees, 90° = east))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_compass_offsets_2 =
R"doc(Set the compass offsets

Parameter ``sensor_offsets``:
    offsets structure (only yaw is used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_depth_sensor_offsets =
R"doc(Set the depth sensor offsets

Parameter ``x``:
    x-offset of the depth sensor (in meters, positive forward)

Parameter ``y``:
    y-offset of the depth sensor (in meters, positive starboard)

Parameter ``z``:
    z-offset of the depth sensor (in meters, positive down))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_depth_sensor_offsets_2 =
R"doc(Set the depth sensor offsets

Parameter ``sensor_offsets``:
    offsets structure (only x, y and z are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_motion_sensor_offsets =
R"doc(Set the motion sensor offsets

Parameter ``sensor_offsets``:
    offsets structure (only yaw, pitch and roll are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_motion_sensor_offsets_2 =
R"doc(Set the motion sensor offsets

Parameter ``yaw``:
    yaw offset of the motion sensor (right-handed around the z-axis)
    (in degrees, 90° = east)

Parameter ``pitch``:
    pitch offset of the motion sensor (right-handed around the y-axis)
    (in degrees, positive = bow up)

Parameter ``roll``:
    roll offset of the motion sensor (right-handed around the x-axis)
    (in degrees, positive = port up))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_system_offsets =
R"doc(Set the position system offsets

Parameter ``x``:
    x-offset of the depth sensor (in meters, positive forward)

Parameter ``y``:
    y-offset of the depth sensor (in meters, positive starboard)

Parameter ``z``:
    z-offset of the depth sensor (in meters, positive down))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_set_position_system_offsets_2 =
R"doc(Set the position system offsets

Parameter ``sensor_offsets``:
    offsets structure (only x, y and z are used))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorConfiguration_target_offsets = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_GeoLocationLatLon =
R"doc(in °, positive eastwards

Construct a new Sensor Position object (all offsets set to 0))doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_latitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLatLon_longitude = R"doc(in °, positive northwards)doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_easting = R"doc(in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationLocal_northing = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_northern_hemisphere = R"doc(UTM/UPS zone number)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_to_geolocation_latlon =
R"doc(Convert a utm geolocationlatlon to an unprojected location

Parameter ``location_utm``:
    $Returns:

GeoLocationLatLon)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocationUTM_zone = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_pitch = R"doc(in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_roll = R"doc(in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_yaw = R"doc(in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_GeoLocation_z = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_pitch = R"doc(in °, positive means clockwise rotation)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_roll = R"doc(in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_x = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_y = R"doc(in m, positive forward)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_yaw = R"doc(in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_PositionalOffsets_z = R"doc(in m, positive starboard)doc";

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
    $Parameter ``gps_latitude``:

in °, positive northwards

Parameter ``gps_longitude``:
    in °, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_SensorDataLatLon_3 =
R"doc(Construct an SensorDataLatLon object from an existing SensorDataUTM
object (this allows for implicit conversion from SensorDataUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_SensorDataLatLon_4 =
R"doc(Construct a new SensorDataLatLon object

Parameter ``gps_latitude``:
    in °, positive northwards

Parameter ``gps_longitude``:
    in °, positive eastwards

Parameter ``gps_z``:
    in m, positive downwards

Parameter ``heave_heave``:
    from heave sensor, will be added to gps_z in m, positive upwards

Parameter ``compass_heading``:
    from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90°
    is east

Parameter ``imu_yaw``:
    in °, 0° is north, 90° is east

Parameter ``imu_pitch``:
    in °, positive means bow up

Parameter ``imu_roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_gps_latitude = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLatLon_gps_longitude = R"doc(in °, positive northwards)doc";

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
    $Parameter ``gps_northing``:

in m, positive northwards

Parameter ``gps_easting``:
    in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_SensorDataLocal_3 =
R"doc(Construct a new SensorDataLocal object

Parameter ``gps_northing``:
    in m, positive northwards

Parameter ``gpd_easting``:
    in m, positive eastwards

Parameter ``gps_z``:
    in m, positive downwards

Parameter ``heave_heave``:
    from heave sensor, will be added to gps_z in m, positive upwards

Parameter ``compass_heading``:
    from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90°
    is east

Parameter ``imu_yaw``:
    in °, 0° is north, 90° is east

Parameter ``imu_pitch``:
    in °, positive means bow up

Parameter ``imu_roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_gps_easting = R"doc(in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataLocal_gps_northing = R"doc()doc";

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
    $Parameter ``gps_northing``:

in m, positive northwards

Parameter ``gps_easting``:
    in m, positive eastwards

Parameter ``gps_zone``:
    UTM/UPS zone number

Parameter ``gps_northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_3 =
R"doc(Construct an SensorDataUTM object from an existing SensorDataLocal
object (using a known zone and hemisphere)

Parameter ``data_local``:
    $Parameter ``gps_zone``:

UTM/UPS zone number

Parameter ``gps_northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_4 =
R"doc(Construct an SensorDataUTM object from an existing SensorDataLatLon
object (this allows for implicit conversion from SensorDataLatLon
class))doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_SensorDataUTM_5 =
R"doc(Construct a new SensorDataUTM object

Parameter ``gps_northing``:
    in m, positive northwards

Parameter ``gpd_easting``:
    in m, positive eastwards

Parameter ``gps_zone``:
    UTM/UPS zone number

Parameter ``gps_northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``gps_z``:
    in m, positive downwards

Parameter ``heave_heave``:
    from heave sensor, will be added to gps_z in m, positive upwards

Parameter ``compass_heading``:
    from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90°
    is east

Parameter ``imu_yaw``:
    in °, 0° is north, 90° is east

Parameter ``imu_pitch``:
    in °, positive means bow up

Parameter ``imu_roll``:
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

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_gps_northern_hemisphere = R"doc(UTM/UPS zone number)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorDataUTM_gps_zone = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_SensorData = R"doc(Construct a new SensorData object)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_SensorData_2 =
R"doc(Construct a new SensorData object

Parameter ``gps_z``:
    in m, positive downwards

Parameter ``heave_heave``:
    from heave sensor, will be added to gps_z in m, positive upwards

Parameter ``compass_heading``:
    from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90°
    is east

Parameter ``imu_yaw``:
    in °, 0° is north, 90° is east

Parameter ``imu_pitch``:
    in °, positive means bow up

Parameter ``imu_roll``:
    in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_compass_heading = R"doc(from heave sensor, will be added to gps_z in m, positive upwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_gps_z = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_heave_heave = R"doc(in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_imu_pitch = R"doc(from motion sensor, in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_imu_roll = R"doc(from motion sensor, in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_imu_yaw =
R"doc(from compass, replaces imu_yaw if not NAN, in °, 0° is north, 90° is
east)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_operator_eq =
R"doc(Check if two SensorData objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_datastructures_SensorData_printer = R"doc()doc";

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

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_degrees = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_minutes = R"doc(lat/lon will be converted to degrees.degrees°N/S E/W)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_seconds = R"doc(lat/lon will be converted to degrees°minutes.minutes'E/S E/W)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

