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


static const char *__doc_themachinethatgoesping_navigation_GeoLocation =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_2 =
R"doc(Construct an GeoLocation object from an existing GeoLocationUTM object
(this allows for implicit conversion from GeoLocationUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) unlike the default GeoLocation structure, this object stores
local northing and easting coordinates. These coordintaes can be
converted to UTM coordinates if the zone and hemisphere are known.)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_GeoLocationLocal = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_GeoLocationLocal_2 =
R"doc(Construct an GeoLocationLocal object from an existing GeoLocation
object (this allows for implicit conversion from GeoLocation class))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_GeoLocationLocal_3 =
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

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_easting = R"doc(< in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_from_geolocationutm =
R"doc(Construct convert a GeoLocationUTM Object to local (stripping zone and
hemisphere)

Parameter ``location_utm``:
    valid GeoLocation object

Parameter ``northing_offset``:
    in m, is substracted from northing coordinate

Parameter ``offset_easting``:
    in m, is substracted fromeasting coordinate

Returns:
    GeoLocationLocal)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_northing = R"doc(< in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_to_geolocationutm =
R"doc(Convert a utm geolocation to a unprojected location

Parameter ``location_local``:
    $Parameter ``zone``:

UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``northing_offset``:
    in m, is added to northing coordinate

Parameter ``offset_easting``:
    in m, is added to easting coordinate

Returns:
    GeoLocationUTM)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationLocal_z = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_2 =
R"doc(Construct an GeoLocationUTM object from an existing GeoLocationLocal
object (using a known zone and hemisphere)

Parameter ``location_local``:
    $Parameter ``zone``:

UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``offset_northing``:
    in m, is added to northing coordinate

Parameter ``offset_easting``:
    in m, is added to easting coordinate)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_3 =
R"doc(A structure to store a georeferenced location and attitude (e.g. of a
sensor) unlike the default GeoLocation structure, this object stores
utm coordinates)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_GeoLocationUTM = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_GeoLocationUTM_2 =
R"doc(Construct an GeoLocationUTM object from an existing GeoLocation object
(this allows for implicit conversion from GeoLocation class))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_GeoLocationUTM_3 =
R"doc(Construct an GeoLocationUTM object from an existing GeoLocationLocal
object (using a known zone and hemisphere)

Parameter ``location_local``:
    $Parameter ``zone``:

UTM/UPS zone number

Parameter ``northern_hemisphere``:
    if true: northern hemisphere, else: southern hemisphere

Parameter ``offset_northing``:
    in m, is added to northing coordinate

Parameter ``offset_easting``:
    in m, is added to easting coordinate)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_GeoLocationUTM_4 =
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

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_easting = R"doc(< in m, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_from_geolocation =
R"doc(Construct convert a GeoLocation Object to UTM

Parameter ``location``:
    valid GeoLocation object

Parameter ``setzone``:
    set a prefered UTM zone negative means automatic, zero means UPS,
    positive means a particular UTM zone

Returns:
    GeoLocationUTM)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_northern_hemisphere = R"doc(< if true: northern hemisphere, else: southern hemisphere)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_northing = R"doc(< in m, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_to_geolocation =
R"doc(Convert a utm geolocation to a unprojected location

Parameter ``location_utm``:
    $Returns:

GeoLocation)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_z = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocationUTM_zone = R"doc(< UTM/UPS zone number)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_GeoLocation = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_GeoLocation_2 =
R"doc(Construct an GeoLocation object from an existing GeoLocationUTM object
(this allows for implicit conversion from GeoLocationUTM class))doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_GeoLocation_3 =
R"doc(Construct a new GeoLocation object

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

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_latitude = R"doc(< in °, positive northwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_longitude = R"doc(< in °, positive eastwards)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_operator_eq =
R"doc(Check if two GeoLocation objects are equal

Parameter ``rhs``:
    $Returns:

true if equal

Returns:
    false if not equal)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_operator_ne =
R"doc(Construct a new GeoLocation object from a string

Parameter ``str``:
    string containing the location in the format
    "latitude,longitude,z,yaw,pitch,roll")doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_GeoLocation_z = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets =
R"doc(A structure to store positional offsets (e.g. of a sensor) relative to
the vessel coordinate system)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_PositionalOffsets = R"doc(Construct a new Sensor Position object (all offsets set to 0))doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_PositionalOffsets_2 =
R"doc(Construct a new PositionalOffsets object

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

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_pitch = R"doc(< in °, positive means bow up)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_roll = R"doc(< in °, positive means port up)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_x = R"doc(< in m, positive foorward)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_y = R"doc(< in m, positive starboard)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_yaw = R"doc(< in °, 0° is north, 90° is east)doc";

static const char *__doc_themachinethatgoesping_navigation_PositionalOffsets_z = R"doc(< in m, positive downwards)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem =
R"doc(A coordinate system that allows for specifying sensor offsets (e.g.
gps antenna and motion sensor) and target offsets (e.g. MBES) to
derive the geolocation and attitude of the specified targets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_CompassOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_DepthSensorOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Heading = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Heave = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Lat = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Latlon_set = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Lon = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_MotionSensorOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Pitch = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_PositionSystemOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Roll = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_RotationPoint_X = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_RotationPoint_Y = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_RotationPoint_Z = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_SensorCoordinateSystem = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_TargetOffsetIDs = R"doc(< TargetId (position in vector) for each registered key)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_TargetOffsets = R"doc(< Positional offsets of registered targets)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_X = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Y = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Yaw = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_Z = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_compassOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_depthSensorOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_motionSensorOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_positionSystemOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_rotationPoint = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetDepth =
R"doc(get_targetDepth: Get the depth of the target including depth sensor
values and heave including motion correction)

Parameter ``key:``:
    Name of the target

Returns:
    return depth (world coordinates))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetLatLon =
R"doc(get_targetLatLon: Get the lat lon position of the target using all
offsets and the position from the position system

Parameter ``key:``:
    Name of the target

Returns:
    return latitude and longitude of the target in °)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetPosSysDistanceAndAzimuth =
R"doc(get_targetPosSysDistanceAndAzimuth: Get the target distance and
azimuth (0° Noth, 90° East) of the Position system towards the target

Parameter ``key:``:
    Name of the target

Parameter ``radians:``:
    if true will output heading as radians (otherwise degrees)

Returns:
    return distance,azimuth (0° Noth, 90° East) coordinates in
    meters,° (relative to the position system, includtion motion and
    depth corrections))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetXY =
R"doc(get_targetXY: Get the depth of the target including depth sensor
values and heave including motion correction)

Parameter ``key:``:
    Name of the target

Parameter ``use_VesselXY:``:
    Include the _X and _Y coordinates from the vessel (or not)

Returns:
    return x,y coordinates in meters (x=northing,y=easting) (relative
    to _X,_Y from position system, includtion motion and depth
    corrections))doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetYPR = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_targetYPR_as_Quat = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_use_motionSensorYaw = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_vesselDepth =
R"doc(get_vesselDepth: Get the depth of the vessel including depth sensor
values and heave including motion correction)

Returns:
    depth of the vessel point)doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_vesselQuat = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_get_vesselYPR = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_compassHeading = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_compassOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_compassOffsets_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_depthSensorDepth = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_depthSensorOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_depthSensorOffsets_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_heaveSensorHeave = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_motionSensorOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_motionSensorOffsets_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_motionSensorPR = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_motionSensorYPR = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_positionSystemLatLon = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_positionSystemOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_positionSystemOffsets_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_positionSystemXY = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_rotationPoint = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_rotationPointZ = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_targetOffsets = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_targetOffsets_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_use_motionSensorYaw = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_vesselPointWaterlineOffset = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_vesselSensorValuesLatLon = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_set_vesselSensorValuesXY = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_SensorCoordinateSystem_use_motionSensorYaw = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_dms_to_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_latitude_to_string =
R"doc(convert a latitude value to a string

Parameter ``latitude``:
    value to be converted

Parameter ``precission``:
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

Parameter ``precission``:
    number of digits behind the .

Parameter ``format``:
    latlon format (degrees°N/S, degrees°minutes'N/S or
    degrees°minutes'seconds''N/S)

Returns:
    converted latitude string)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format = R"doc(lat/lon format specificaionts)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_degrees = R"doc(< lat/lon will be converted to degrees.degrees°N/S E/W)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_minutes = R"doc(< lat/lon will be converted to degrees°minutes.minutes'E/S E/W)doc";

static const char *__doc_themachinethatgoesping_navigation_navtools_t_latlon_format_seconds =
R"doc(< lat/lon will be converted to degrees°minutes'seconds.seconds''E/S
E/W)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

