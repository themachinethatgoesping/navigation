// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolator.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("navigationinterpolator should support common functions", TESTTAG)
{
    // // initialize coordinate system with one target
    NavigationInterpolator     scs;
    datastructures::PositionalOffsets targetOffsets(1, 2, 3, 0, 0, 0);
    scs.add_target("mbes", targetOffsets);
    // scs.set_offsets_position_system(10, 20, 30);
    // scs.set_offsets_compass(12);
    // scs.set_offsets_motion_sensor(1, -2, 3);
    // scs.set_offsets_depth_sensor(4, 5, -6);

    // // copy constructor
    // NavigationInterpolator scs2(scs);

    // // eq operator
    // REQUIRE(scs == scs2);
    // scs.add_target("sbes", targetOffsets);
    // REQUIRE(scs != scs2);
    // scs2.add_target("sbes", targetOffsets);
    // REQUIRE(scs == scs2);
    // scs.set_offsets_position_system(11, 20, 30);
    // REQUIRE(scs != scs2);

    // // string conversion
    // scs.print(std::cerr);
    // REQUIRE(scs.info_string().size() > 0);

    // // serialization
    // auto buffer = scs.to_binary();
    // auto scs3   = NavigationInterpolator::from_binary(buffer);
    // REQUIRE(scs == scs3);
}

// TEST_CASE(
//     "navigationinterpolator should reproduce precomputed rotations when settings sensor offsets",
//     TESTTAG)
// {
//     // initialize offsets
//     datastructures::PositionalOffsets targetOffsets(1, 2, 3, 0, 0, 0);

//     SECTION("test depth sensor offsets")
//     {
//         NavigationInterpolator scs;
//         scs.add_target("mbes", targetOffsets);
//         scs.set_offsets_depth_sensor(0, 0, 10);

//         REQUIRE(scs.compute_target_position("mbes", datastructures::SensorDataLocal()).z == -7);
//     }

//     SECTION("test imu sensor offsets")
//     {
//         NavigationInterpolator scs;
//         scs.add_target("mbes", targetOffsets);

//         datastructures::SensorDataLocal sensor_data;
//         sensor_data.compass_heading = 90;
//         sensor_data.imu_roll        = 0;
//         sensor_data.imu_pitch       = 20;
//         sensor_data.imu_yaw         = 130; // should not influence the results

//         // imu yaw offset should not influence the resulting yaw because that is influenced only by
//         // the compass_heading but imu yaw offset of 90° should swap pitch and roll
//         scs.set_offsets_motion_sensor(90, 0, 0);
//         auto position = scs.compute_target_position("mbes", sensor_data);

//         REQUIRE(position.yaw == Approx(90));
//         CHECK(position.pitch == Approx(0.0).scale(1.0));
//         REQUIRE(position.roll == Approx(-20));

//         sensor_data.imu_roll  = 10;
//         sensor_data.imu_pitch = 0;

//         position = scs.compute_target_position("mbes", sensor_data);
//         REQUIRE(position.yaw == Approx(90));
//         CHECK(position.pitch == Approx(10.0));
//         REQUIRE(position.roll == Approx(0).scale(1.0));

//         scs.set_offsets_motion_sensor(0, 1, 2);
//         position = scs.compute_target_position("mbes", sensor_data);
//         REQUIRE(position.yaw == Approx(90));
//         CHECK(position.pitch == Approx(-0.9902670948));
//         REQUIRE(position.roll == Approx(8.001202844));
//     }
// }

// TEST_CASE("navigationinterpolator should reproduce precomputed rotations", TESTTAG)
// {
//     // initialize offsets
//     NavigationInterpolator     scs;
//     datastructures::PositionalOffsets targetOffsets1(1, 2, 3, 0, 0, 0);
//     datastructures::PositionalOffsets targetOffsets2(1, 2, 3, 45, 5, 10);

//     scs.add_target("mbes", targetOffsets1);
//     scs.add_target("sbes", targetOffsets2);

//     SECTION("NO_SENSOR_VALUES")
//     {
//         auto position_mbes = scs.compute_target_position("mbes", datastructures::SensorDataLocal());
//         auto position_sbes = scs.compute_target_position("sbes", datastructures::SensorDataLocal());

//         datastructures::GeoLocationLocal expected_result_mbes(1, 2, 3, 0, 0, 0);
//         datastructures::GeoLocationLocal expected_result_sbes(1, 2, 3, 45, 5, 10);

//         REQUIRE(position_mbes == expected_result_mbes);
//         REQUIRE(position_sbes == expected_result_sbes);

//         REQUIRE(scs.get_offsets_target("mbes") == targetOffsets1);
//         REQUIRE(scs.get_offsets_target("sbes") == targetOffsets2);
//     }

//     SECTION("SENSOR_VALUES no roll/pitch")
//     {
//         // initialize sensor data
//         datastructures::SensorDataLocal sensor_data;
//         sensor_data.gps_z           = 5;
//         sensor_data.compass_heading = 0;
//         sensor_data.imu_yaw         = 40; // ignored because compass_heading is valid
//         sensor_data.imu_pitch       = 0;
//         sensor_data.imu_roll        = 0;
//         sensor_data.gps_northing    = 10;
//         sensor_data.gps_easting     = 20;

//         // compute sensor positions
//         auto position_mbes = scs.compute_target_position("mbes", sensor_data);
//         auto position_sbes = scs.compute_target_position("sbes", sensor_data);
//         auto relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         auto relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         // check results
//         REQUIRE(position_mbes.z == Approx(8.0));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(1.0));
//         CHECK(relative_position_mbes.easting == Approx(2.0));
//         CHECK(position_mbes.northing == Approx(11));
//         REQUIRE(position_mbes.easting == Approx(22));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(0.0));
//         CHECK(position_mbes.pitch == Approx(0.0));
//         CHECK(position_mbes.roll == Approx(0.0));
//         CHECK(position_sbes.yaw == Approx(45));
//         CHECK(position_sbes.pitch == Approx(5));
//         REQUIRE(position_sbes.roll == Approx(10));

//         // scenario 0.2
//         // initialize sensor data
//         sensor_data.gps_z           = 5;
//         sensor_data.compass_heading = 180;
//         sensor_data.imu_yaw         = 40; // ignored because compass_heading is valid
//         sensor_data.imu_pitch       = 0;
//         sensor_data.imu_roll        = 0;
//         sensor_data.gps_northing    = 10;
//         sensor_data.gps_easting     = 20;

//         // compute sensor positions
//         position_mbes = scs.compute_target_position("mbes", sensor_data);
//         position_sbes = scs.compute_target_position("sbes", sensor_data);
//         relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         // check results
//         REQUIRE(position_mbes.z == Approx(8.0));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(-1.0));
//         REQUIRE(relative_position_mbes.easting == Approx(-2.0));
//         CHECK(position_mbes.northing == Approx(9));
//         REQUIRE(position_mbes.easting == Approx(18));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(180.0));
//         CHECK(position_mbes.pitch == Approx(0.0));
//         CHECK(position_mbes.roll == Approx(0.0));
//         CHECK(position_sbes.yaw == Approx(225));
//         CHECK(position_sbes.pitch == Approx(5));
//         REQUIRE(position_sbes.roll == Approx(10));

//         // scenario 0.3
//         // initialize sensor data
//         sensor_data.gps_z           = 5;
//         sensor_data.compass_heading = 90;
//         sensor_data.imu_yaw         = 40; // ignored because compass_heading is valid
//         sensor_data.imu_pitch       = 0;
//         sensor_data.imu_roll        = 0;
//         sensor_data.gps_northing    = 10;
//         sensor_data.gps_easting     = 20;

//         // compute sensor positions
//         position_mbes = scs.compute_target_position("mbes", sensor_data);
//         position_sbes = scs.compute_target_position("sbes", sensor_data);
//         relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         // check results
//         REQUIRE(position_mbes.z == Approx(8.0));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(-2.0));
//         CHECK(relative_position_mbes.easting == Approx(1.0));
//         CHECK(position_mbes.northing == Approx(8));
//         REQUIRE(position_mbes.easting == Approx(21));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(90.0));
//         CHECK(position_mbes.pitch == Approx(0.0));
//         CHECK(position_mbes.roll == Approx(0.0));
//         CHECK(position_sbes.yaw == Approx(135));
//         CHECK(position_sbes.pitch == Approx(5));
//         CHECK(position_sbes.roll == Approx(10));
//     }

//     SECTION("SENSOR_VALUES XY coordinates")
//     {
//         datastructures::SensorDataLocal sensor_data;
//         // scenario 1
//         sensor_data.gps_z           = 5;
//         sensor_data.compass_heading = 25;
//         sensor_data.imu_yaw         = 40;
//         sensor_data.imu_pitch       = 20;
//         sensor_data.imu_roll        = 10;
//         sensor_data.gps_northing    = 10;
//         sensor_data.gps_easting     = 20;

//         // compute sensor positions
//         auto position_mbes = scs.compute_target_position("mbes", sensor_data);
//         auto position_sbes = scs.compute_target_position("sbes", sensor_data);
//         auto relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         auto relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         // check results
//         REQUIRE(position_mbes.z == Approx(7.7605814142));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(1.262868183));
//         CHECK(relative_position_mbes.easting == Approx(2.1873166684));
//         CHECK(position_mbes.northing == Approx(11.262868183));
//         CHECK(position_mbes.easting == Approx(22.1873166684));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(25.0));
//         CHECK(position_mbes.pitch == Approx(20.0));
//         CHECK(position_mbes.roll == Approx(10.0));
//         CHECK(position_sbes.yaw == Approx(71.4260001287));
//         CHECK(position_sbes.pitch == Approx(11.9252923155));
//         CHECK(position_sbes.roll == Approx(31.4141895033));

//         // scenario 2
//         sensor_data.gps_z           = -5;
//         sensor_data.compass_heading = -35;
//         sensor_data.imu_yaw         = 40;
//         sensor_data.imu_pitch       = -5;
//         sensor_data.imu_roll        = -15;
//         sensor_data.gps_northing    = -23;
//         sensor_data.gps_easting     = -20;

//         // compute sensor positions
//         position_mbes = scs.compute_target_position("mbes", sensor_data);
//         position_sbes = scs.compute_target_position("sbes", sensor_data);
//         relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         CHECK(position_mbes.z == Approx(-2.5417620175));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(2.1995298195));
//         CHECK(relative_position_mbes.easting == Approx(1.7661071866));
//         CHECK(position_mbes.northing == Approx(-20.8004701805));
//         CHECK(position_mbes.easting == Approx(-18.2338928134));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(325.0));
//         CHECK(position_mbes.pitch == Approx(-5.0));
//         CHECK(position_mbes.roll == Approx(-15.0));
//         CHECK(position_sbes.yaw == Approx(7.2216796191));
//         CHECK(position_sbes.pitch == Approx(11.7764820146));
//         CHECK(position_sbes.roll == Approx(-4.429576033));

//         // scenario 3
//         sensor_data.gps_z           = 3;
//         sensor_data.compass_heading = NAN;
//         sensor_data.imu_yaw         = 30;
//         sensor_data.imu_pitch       = -5;
//         sensor_data.imu_roll        = -15;
//         sensor_data.gps_northing    = 100;
//         sensor_data.gps_easting     = -20;

//         // compute sensor positions
//         position_mbes = scs.compute_target_position("mbes", sensor_data);
//         position_sbes = scs.compute_target_position("sbes", sensor_data);
//         relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         CHECK(position_mbes.z == Approx(5.4582379825));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(-0.671075227));
//         CHECK(relative_position_mbes.easting == Approx(2.7398401525));
//         CHECK(position_mbes.northing == Approx(99.328924773));
//         CHECK(position_mbes.easting == Approx(-17.2601598475));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(30.0));
//         CHECK(position_mbes.pitch == Approx(-5.0));
//         CHECK(position_mbes.roll == Approx(-15.0));
//         CHECK(position_sbes.yaw == Approx(72.2216796191));
//         CHECK(position_sbes.pitch == Approx(11.7764820146));
//         CHECK(position_sbes.roll == Approx(-4.429576033));

//         // scenario 4
//         sensor_data.gps_z           = -2000;
//         sensor_data.compass_heading = -470;
//         sensor_data.imu_yaw         = 40;
//         sensor_data.imu_pitch       = -59;
//         sensor_data.imu_roll        = 1;
//         sensor_data.gps_northing    = 23;
//         sensor_data.gps_easting     = -1000;

//         // compute sensor positions
//         position_mbes = scs.compute_target_position("mbes", sensor_data);
//         position_sbes = scs.compute_target_position("sbes", sensor_data);
//         relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         CHECK(position_mbes.z == Approx(-1997.5799764953));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(relative_position_mbes.northing == Approx(2.5433504005));
//         CHECK(relative_position_mbes.easting == Approx(1.2941618821));
//         CHECK(position_mbes.northing == Approx(25.5433504005));
//         CHECK(position_mbes.easting == Approx(-998.7058381179));

//         REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
//         REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
//         REQUIRE(position_mbes.northing == position_sbes.northing);
//         REQUIRE(position_mbes.easting == position_sbes.easting);

//         CHECK(position_mbes.yaw == Approx(250.0));
//         CHECK(position_mbes.pitch == Approx(-59.0));
//         CHECK(position_mbes.roll == Approx(1.0));
//         CHECK(position_sbes.yaw == Approx(308.8301085148));
//         CHECK(position_sbes.pitch == Approx(-34.4198234806));
//         CHECK(position_sbes.roll == Approx(-36.6392731807));
//     }

//     SECTION("SENSOR_VALUES latitude and longitued")
//     {
//         datastructures::SensorDataLatLon sensor_data;

//         // scenario 5 (latlon)
//         sensor_data.gps_z           = 2000;
//         sensor_data.compass_heading = 470;
//         sensor_data.imu_yaw         = 40;
//         sensor_data.imu_pitch       = -59;
//         sensor_data.imu_roll        = 1;
//         sensor_data.gps_latitude    = 54.123;
//         sensor_data.gps_longitude   = -10.123;

//         auto position_mbes = scs.compute_target_position("mbes", sensor_data);
//         auto position_sbes = scs.compute_target_position("sbes", sensor_data);
//         auto relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         auto relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         CHECK(position_mbes.z == Approx(2002.4200235047));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(position_mbes.latitude == Approx(54.1229869952));
//         CHECK(position_mbes.longitude == Approx(-10.123067173));

//         CHECK(position_mbes.yaw == Approx(110.0));
//         CHECK(position_mbes.pitch == Approx(-59.0));
//         CHECK(position_mbes.roll == Approx(1.0));
//         CHECK(position_sbes.yaw == Approx(168.8301085148));
//         CHECK(position_sbes.pitch == Approx(-34.4198234806));
//         CHECK(position_sbes.roll == Approx(-36.6392731807));

//         // check if results with UTM are the same as with latlon
//         datastructures::GeoLocationUTM position_mbes_utm =
//             scs.compute_target_position("mbes", datastructures::SensorDataUTM(sensor_data));
//         datastructures::GeoLocationUTM position_sbes_utm =
//             scs.compute_target_position("sbes", datastructures::SensorDataUTM(sensor_data));
//         CHECK(position_mbes_utm == position_mbes);
//         CHECK(position_sbes_utm == position_sbes);

//         // scenario 6 (latlon)
//         sensor_data.gps_z           = 1000;
//         sensor_data.compass_heading = 360;
//         sensor_data.imu_yaw         = 40;
//         sensor_data.imu_pitch       = 9;
//         sensor_data.imu_roll        = -1;
//         sensor_data.gps_latitude    = -74.123;
//         sensor_data.gps_longitude   = 1.123;

//         // compute sensor positions
//         position_mbes = scs.compute_target_position("mbes", sensor_data);
//         position_sbes = scs.compute_target_position("sbes", sensor_data);
//         relative_position_mbes =
//             scs.compute_target_position("mbes",
//                 datastructures::SensorData(sensor_data)); // convert to SensorData (without xy coordinates)
//         relative_position_sbes = scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

//         CHECK(position_mbes.z == Approx(1002.7717041909));
//         REQUIRE(position_mbes.z == position_sbes.z);

//         CHECK(position_mbes.latitude == Approx(-74.1229869952));
//         CHECK(position_mbes.longitude == Approx(1.123067173));

//         CHECK(position_mbes.yaw == Approx(0.0));
//         CHECK(position_mbes.pitch == Approx(9.0));
//         CHECK(position_mbes.roll == Approx(-1.0));
//         CHECK(position_sbes.yaw == Approx(45.9361957025));
//         CHECK(position_sbes.pitch == Approx(12.0290113349));
//         CHECK(position_sbes.roll == Approx(15.7758445678));

//         // check if results with UTM are the same as with latlon
//         position_mbes_utm = scs.compute_target_position("mbes", datastructures::SensorDataUTM(sensor_data));
//         position_sbes_utm = scs.compute_target_position("sbes", datastructures::SensorDataUTM(sensor_data));
//         CHECK(position_mbes_utm == position_mbes);
//         CHECK(position_sbes_utm == position_sbes);
//     }
// }