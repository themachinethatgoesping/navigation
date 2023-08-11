// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/sensorconfiguration.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("sensorconfiguration should support common functions", TESTTAG)
{
    // initialize coordinate system with one target
    SensorConfiguration               scs;
    datastructures::PositionalOffsets targetOffsets("mbes", 1, 2, 3, 0, 0, 0);
    scs.add_target("mbes", targetOffsets);
    scs.set_position_source("gps", 10, 20, 30);
    scs.set_heading_source("compass", 12);
    scs.set_attitude_source("mru", 1, -2, 3);
    scs.set_depth_source("gps", 4, 5, -6);

    // copy constructor
    SensorConfiguration scs2(scs);

    // eq operator
    REQUIRE(scs == scs2);
    scs.add_target("sbes", targetOffsets);
    REQUIRE(scs != scs2);
    scs2.add_target("sbes", targetOffsets);
    REQUIRE(scs == scs2);
    scs.set_position_source("gps", 11, 20, 30);
    REQUIRE(scs != scs2);

    // string conversion
    // scs.print(std::cerr);
    REQUIRE(scs.info_string().size() > 0);

    // serialization
    auto buffer = scs.to_binary();
    auto scs3   = SensorConfiguration::from_binary(buffer);
    REQUIRE(scs == scs3);
}

TEST_CASE("sensorconfiguration should reproduce precomputed rotations when settings sensor offsets",
          TESTTAG)
{
    // initialize offsets
    datastructures::PositionalOffsets targetOffsets("gps", 1, 2, 3, 0, 0, 0);

    SECTION("test depth sensor offsets")
    {
        SensorConfiguration scs;
        scs.add_target("mbes", targetOffsets);
        scs.set_depth_source("gps", 0, 0, 10);

        REQUIRE(scs.compute_target_position("mbes", datastructures::SensorDataLocal()).z == -7);
    }

    SECTION("test imu sensor offsets")
    {
        SensorConfiguration scs;
        scs.add_target("mbes", targetOffsets);

        datastructures::SensorDataLocal sensor_data;
        sensor_data.heading = 90;
        sensor_data.roll    = 0;
        sensor_data.pitch   = 20;

        // imu yaw offset should not influence the resulting yaw because that is influenced only by
        // the heading but imu yaw offset of 90° should swap pitch and roll
        scs.set_attitude_source("gps", 90, 0, 0);
        auto position = scs.compute_target_position("mbes", sensor_data);

        REQUIRE(position.yaw == Catch::Approx(90));
        CHECK(position.pitch == Catch::Approx(0.0).scale(1.0));
        REQUIRE(position.roll == Catch::Approx(-20));

        sensor_data.roll  = 10;
        sensor_data.pitch = 0;

        position = scs.compute_target_position("mbes", sensor_data);
        REQUIRE(position.yaw == Catch::Approx(90));
        CHECK(position.pitch == Catch::Approx(10.0));
        REQUIRE(position.roll == Catch::Approx(0).scale(1.0));

        scs.set_attitude_source("gps", 0, 1, 2);
        position = scs.compute_target_position("mbes", sensor_data);
        REQUIRE(position.yaw == Catch::Approx(90));
        CHECK(position.pitch == Catch::Approx(-0.9902670948));
        REQUIRE(position.roll == Catch::Approx(8.001202844));
    }
}

TEST_CASE("sensorconfiguration merging operations", TESTTAG)
{
    // initialize offsets
    SensorConfiguration               scs;
    datastructures::PositionalOffsets targetOffsets1("sensor1", 1, 2, 3, 0, 0, 0);
    datastructures::PositionalOffsets targetOffsets2("sensor2", 1, 2, 3, 45, 5, 10);

    scs.set_attitude_source(targetOffsets1);
    scs.add_target("mbes", targetOffsets1);
    scs.add_target("sbes", targetOffsets2);

    SECTION("Correctly determine if sensor configurations can be merges")
    {
        auto scs2 = scs;
        REQUIRE(scs.can_merge_targets_with(scs2));

        // should still be mergeable if an additional target is present
        scs2.add_target("sbes2", targetOffsets2);
        REQUIRE(scs != scs2);
        REQUIRE(scs.can_merge_targets_with(scs2));

        // should be mergeable if a target is missing
        scs2.remove_target("sbes");
        REQUIRE(scs != scs2);
        REQUIRE(scs.can_merge_targets_with(scs2));

        // should not be mergeable if a duplicate target with different offsets is present
        scs2.add_target("sbes", targetOffsets1);
        REQUIRE(scs.can_merge_targets_with(scs2) == false);

        // should not be mergeable if the sensor offsets are not same
        // this check is not part of can_merge_targets_with anymore
        // scs2 = scs;
        // REQUIRE(scs.can_merge_targets_with(scs2));
        // scs.set_depth_source(targetOffsets1);
        // REQUIRE(scs.can_merge_targets_with(scs2) == false);
    }
}

TEST_CASE("sensorconfiguration should reproduce precomputed rotations", TESTTAG)
{
    // initialize offsets
    SensorConfiguration               scs;
    datastructures::PositionalOffsets targetOffsets1("sensor1", 1, 2, 3, 0, 0, 0);
    datastructures::PositionalOffsets targetOffsets2("sensor2", 1, 2, 3, 45, 5, 10);

    scs.add_target("mbes", targetOffsets1);
    scs.add_target("sbes", targetOffsets2);

    SECTION("NO_SENSOR_VALUES")
    {
        auto position_mbes = scs.compute_target_position("mbes", datastructures::SensorDataLocal());
        auto position_sbes = scs.compute_target_position("sbes", datastructures::SensorDataLocal());

        datastructures::GeoLocationLocal expected_result_mbes(1, 2, 3, 0, 0, 0);
        datastructures::GeoLocationLocal expected_result_sbes(1, 2, 3, 45, 5, 10);

        REQUIRE(position_mbes == expected_result_mbes);
        REQUIRE(position_sbes == expected_result_sbes);

        REQUIRE(scs.get_target("mbes") == targetOffsets1);
        REQUIRE(scs.get_target("sbes") == targetOffsets2);
    }

    SECTION("SENSOR_VALUES no roll/pitch")
    {
        // initialize sensor data
        datastructures::SensorDataLocal sensor_data;
        sensor_data.depth    = 5;
        sensor_data.heading  = 0;
        sensor_data.pitch    = 0;
        sensor_data.roll     = 0;
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        auto position_mbes          = scs.compute_target_position("mbes", sensor_data);
        auto position_sbes          = scs.compute_target_position("sbes", sensor_data);
        auto relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        auto relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        // check results
        REQUIRE(position_mbes.z == Catch::Approx(8.0));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(1.0));
        CHECK(relative_position_mbes.easting == Catch::Approx(2.0));
        CHECK(position_mbes.northing == Catch::Approx(11));
        REQUIRE(position_mbes.easting == Catch::Approx(22));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(0.0));
        CHECK(position_mbes.pitch == Catch::Approx(0.0));
        CHECK(position_mbes.roll == Catch::Approx(0.0));
        CHECK(position_sbes.yaw == Catch::Approx(45));
        CHECK(position_sbes.pitch == Catch::Approx(5));
        REQUIRE(position_sbes.roll == Catch::Approx(10));

        // scenario 0.2
        // initialize sensor data
        sensor_data.depth    = 5;
        sensor_data.heading  = 180;
        sensor_data.pitch    = 0;
        sensor_data.roll     = 0;
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        // check results
        REQUIRE(position_mbes.z == Catch::Approx(8.0));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(-1.0));
        REQUIRE(relative_position_mbes.easting == Catch::Approx(-2.0));
        CHECK(position_mbes.northing == Catch::Approx(9));
        REQUIRE(position_mbes.easting == Catch::Approx(18));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(180.0));
        CHECK(position_mbes.pitch == Catch::Approx(0.0));
        CHECK(position_mbes.roll == Catch::Approx(0.0));
        CHECK(position_sbes.yaw == Catch::Approx(225));
        CHECK(position_sbes.pitch == Catch::Approx(5));
        REQUIRE(position_sbes.roll == Catch::Approx(10));

        // scenario 0.3
        // initialize sensor data
        sensor_data.depth    = 5;
        sensor_data.heading  = 90;
        sensor_data.pitch    = 0;
        sensor_data.roll     = 0;
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        // check results
        REQUIRE(position_mbes.z == Catch::Approx(8.0));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(-2.0));
        CHECK(relative_position_mbes.easting == Catch::Approx(1.0));
        CHECK(position_mbes.northing == Catch::Approx(8));
        REQUIRE(position_mbes.easting == Catch::Approx(21));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(90.0));
        CHECK(position_mbes.pitch == Catch::Approx(0.0));
        CHECK(position_mbes.roll == Catch::Approx(0.0));
        CHECK(position_sbes.yaw == Catch::Approx(135));
        CHECK(position_sbes.pitch == Catch::Approx(5));
        CHECK(position_sbes.roll == Catch::Approx(10));
    }

    SECTION("SENSOR_VALUES XY coordinates")
    {
        datastructures::SensorDataLocal sensor_data;
        // scenario 1
        sensor_data.depth    = 5;
        sensor_data.heading  = 25;
        sensor_data.pitch    = 20;
        sensor_data.roll     = 10;
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        auto position_mbes          = scs.compute_target_position("mbes", sensor_data);
        auto position_sbes          = scs.compute_target_position("sbes", sensor_data);
        auto relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        auto relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        // check results
        REQUIRE(position_mbes.z == Catch::Approx(7.7605814142));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(1.262868183));
        CHECK(relative_position_mbes.easting == Catch::Approx(2.1873166684));
        CHECK(position_mbes.northing == Catch::Approx(11.262868183));
        CHECK(position_mbes.easting == Catch::Approx(22.1873166684));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(25.0));
        CHECK(position_mbes.pitch == Catch::Approx(20.0));
        CHECK(position_mbes.roll == Catch::Approx(10.0));
        CHECK(position_sbes.yaw == Catch::Approx(71.4260001287));
        CHECK(position_sbes.pitch == Catch::Approx(11.9252923155));
        CHECK(position_sbes.roll == Catch::Approx(31.4141895033));

        // scenario 2
        sensor_data.depth    = -5;
        sensor_data.heading  = -35;
        sensor_data.pitch    = -5;
        sensor_data.roll     = -15;
        sensor_data.northing = -23;
        sensor_data.easting  = -20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(-2.5417620175));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(2.1995298195));
        CHECK(relative_position_mbes.easting == Catch::Approx(1.7661071866));
        CHECK(position_mbes.northing == Catch::Approx(-20.8004701805));
        CHECK(position_mbes.easting == Catch::Approx(-18.2338928134));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(325.0));
        CHECK(position_mbes.pitch == Catch::Approx(-5.0));
        CHECK(position_mbes.roll == Catch::Approx(-15.0));
        CHECK(position_sbes.yaw == Catch::Approx(7.2216796191));
        CHECK(position_sbes.pitch == Catch::Approx(11.7764820146));
        CHECK(position_sbes.roll == Catch::Approx(-4.429576033));

        // scenario 3
        sensor_data.depth    = 3;
        sensor_data.heading  = 30;
        sensor_data.pitch    = -5;
        sensor_data.roll     = -15;
        sensor_data.northing = 100;
        sensor_data.easting  = -20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(5.4582379825));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(-0.671075227));
        CHECK(relative_position_mbes.easting == Catch::Approx(2.7398401525));
        CHECK(position_mbes.northing == Catch::Approx(99.328924773));
        CHECK(position_mbes.easting == Catch::Approx(-17.2601598475));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(30.0));
        CHECK(position_mbes.pitch == Catch::Approx(-5.0));
        CHECK(position_mbes.roll == Catch::Approx(-15.0));
        CHECK(position_sbes.yaw == Catch::Approx(72.2216796191));
        CHECK(position_sbes.pitch == Catch::Approx(11.7764820146));
        CHECK(position_sbes.roll == Catch::Approx(-4.429576033));

        // scenario 4
        sensor_data.depth    = -2000;
        sensor_data.heading  = -470;
        sensor_data.pitch    = -59;
        sensor_data.roll     = 1;
        sensor_data.northing = 23;
        sensor_data.easting  = -1000;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(-1997.5799764953));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(relative_position_mbes.northing == Catch::Approx(2.5433504005));
        CHECK(relative_position_mbes.easting == Catch::Approx(1.2941618821));
        CHECK(position_mbes.northing == Catch::Approx(25.5433504005));
        CHECK(position_mbes.easting == Catch::Approx(-998.7058381179));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        CHECK(position_mbes.yaw == Catch::Approx(250.0));
        CHECK(position_mbes.pitch == Catch::Approx(-59.0));
        CHECK(position_mbes.roll == Catch::Approx(1.0));
        CHECK(position_sbes.yaw == Catch::Approx(308.8301085148));
        CHECK(position_sbes.pitch == Catch::Approx(-34.4198234806));
        CHECK(position_sbes.roll == Catch::Approx(-36.6392731807));
    }

    SECTION("SENSOR_VALUES latitude and longitude")
    {
        datastructures::SensorDataLatLon sensor_data;

        // scenario 5 (latlon)
        sensor_data.depth     = 2000;
        sensor_data.heading   = 470;
        sensor_data.pitch     = -59;
        sensor_data.roll      = 1;
        sensor_data.latitude  = 54.123;
        sensor_data.longitude = -10.123;

        auto position_mbes          = scs.compute_target_position("mbes", sensor_data);
        auto position_sbes          = scs.compute_target_position("sbes", sensor_data);
        auto relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        auto relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(2002.4200235047));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(position_mbes.latitude == Catch::Approx(54.1229869952));
        CHECK(position_mbes.longitude == Catch::Approx(-10.123067173));

        CHECK(position_mbes.yaw == Catch::Approx(110.0));
        CHECK(position_mbes.pitch == Catch::Approx(-59.0));
        CHECK(position_mbes.roll == Catch::Approx(1.0));
        CHECK(position_sbes.yaw == Catch::Approx(168.8301085148));
        CHECK(position_sbes.pitch == Catch::Approx(-34.4198234806));
        CHECK(position_sbes.roll == Catch::Approx(-36.6392731807));

        // check if results with UTM are the same as with latlon
        datastructures::GeoLocationUTM position_mbes_utm =
            scs.compute_target_position("mbes", datastructures::SensorDataUTM(sensor_data));
        datastructures::GeoLocationUTM position_sbes_utm =
            scs.compute_target_position("sbes", datastructures::SensorDataUTM(sensor_data));
        CHECK(position_mbes_utm == datastructures::GeoLocationUTM(position_mbes));
        CHECK(position_sbes_utm == datastructures::GeoLocationUTM(position_sbes));

        // scenario 6 (latlon)
        sensor_data.depth     = 1000;
        sensor_data.heading   = 360;
        sensor_data.pitch     = 9;
        sensor_data.roll      = -1;
        sensor_data.latitude  = -74.123;
        sensor_data.longitude = 1.123;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::SensorData(
                sensor_data)); // convert to SensorData (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::SensorData(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(1002.7717041909f));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(position_mbes.latitude == Catch::Approx(-74.1229869952));
        CHECK(position_mbes.longitude == Catch::Approx(1.123067173));

        REQUIRE_THAT(position_mbes.yaw, Catch::Matchers::WithinAbs(0, 0.001f));
        REQUIRE_THAT(position_mbes.pitch, Catch::Matchers::WithinAbs(9.f, 0.001f));
        REQUIRE_THAT(position_mbes.roll, Catch::Matchers::WithinAbs(-1.f, 0.001f));
        REQUIRE_THAT(position_sbes.yaw, Catch::Matchers::WithinAbs(45.936f, 0.001f));
        REQUIRE_THAT(position_sbes.pitch, Catch::Matchers::WithinAbs(12.029f, 0.001f));
        REQUIRE_THAT(position_sbes.roll, Catch::Matchers::WithinAbs(15.775f, 0.001f));

        // check if results with UTM are the same as with latlon
        position_mbes_utm =
            scs.compute_target_position("mbes", datastructures::SensorDataUTM(sensor_data));
        position_sbes_utm =
            scs.compute_target_position("sbes", datastructures::SensorDataUTM(sensor_data));
        CHECK(position_mbes_utm == datastructures::GeoLocationUTM(position_mbes));
        CHECK(position_sbes_utm == datastructures::GeoLocationUTM(position_sbes));
    }
}