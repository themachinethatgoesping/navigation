// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
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
    datastructures::SensorPose targetOffsets("mbes", 1, 2, 3, 0, 0, 0);
    scs.add_target("mbes", targetOffsets);
    scs.set_position_source("gps", 10, 20, 30);
    scs.set_heading_source("compass", 12);
    scs.set_attitude_source("mru", 1, -2, 3);
    scs.set_depth_source("gps", 4, 5, -6);

    scs.set_waterline_offset(-0.5);

    // copy constructor
    SensorConfiguration scs2(scs);

    // eq operator
    REQUIRE(scs == scs2);
    scs.add_target("sbes", targetOffsets);
    REQUIRE(scs != scs2);
    scs2.add_target("sbes", targetOffsets);
    REQUIRE(scs == scs2);
    scs.set_position_source_motion_compensated(true);
    REQUIRE(scs != scs2);
    scs2.set_position_source_motion_compensated(true);
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
    CHECK(scs.binary_hash() == scs3.binary_hash()); // hash should not change after serialization
}

TEST_CASE("sensorconfiguration compute_target_pose should match its definition", TESTTAG)
{
    using themachinethatgoesping::tools::rotationfunctions::Rotation;

    SensorConfiguration scs;
    scs.add_target("mbes",
                   datastructures::SensorPose("mbes", 1.f, 2.f, 3.f, 10.f, 20.f, 30.f));
    scs.set_heading_source("compass", 5.f);
    scs.set_attitude_source("mru", 1.f, -2.f, 3.f);
    scs.set_depth_source("dsource", 4.f, 5.f, -6.f);
    scs.set_waterline_offset(-0.5f);

    datastructures::Sensordata sd(7.f, 0.5f, 42.f, 4.f, -3.f); // depth, heave, heading, pitch, roll
    const float                ref_heading = 42.f;

    const auto& target = scs.get_target("mbes");

    // vessel orientation expressed relative to the reference heading (residual yaw kept because the
    // reference heading is the raw heading, not the offset-corrected one)
    const Rotation<float> vessel_rel = scs.get_vessel_rotation(sd, ref_heading);

    const auto pose = scs.compute_target_pose("mbes", sd, ref_heading);

    // orientation: reference-relative vessel rotation times the installation
    REQUIRE(pose.rotation == vessel_rel * target.rotation);

    // position: the body-frame lever arm rotated into the surface frame by the SAME rotation
    const auto lever = vessel_rel.rotate(target.x, target.y, target.z);
    CHECK(pose.x == Catch::Approx(lever[0]));
    CHECK(pose.y == Catch::Approx(lever[1]));

    // z is heading-independent and equals the geolocation depth
    CHECK(pose.z == Catch::Approx(scs.compute_target_position("mbes", sd).z));
}

TEST_CASE("sensorconfiguration compute_position_system_offset should match its definition", TESTTAG)
{
    using themachinethatgoesping::tools::rotationfunctions::Rotation;

    SensorConfiguration scs;
    scs.set_heading_source("compass", 5.f);
    scs.set_attitude_source("mru", 1.f, -2.f, 3.f);
    scs.set_position_source("gps", -7.f, 0.8f, -5.f);
    scs.set_waterline_offset(-2.f);

    datastructures::Sensordata sd(0.f, 0.f, 42.f, 4.f, -3.f); // depth, heave, heading, pitch, roll
    const float                ref_heading = 42.f;

    const auto& ps         = scs.get_position_source();
    const auto  vessel_rel = scs.get_vessel_rotation(sd, ref_heading);

    // antenna at its true height: full position-source lever arm rotated into the surface frame
    const auto off = scs.compute_position_system_offset(sd, ref_heading);
    const auto ref = vessel_rel.rotate(ps.x, ps.y, ps.z);
    CHECK(off[0] == Catch::Approx(ref[0]));
    CHECK(off[1] == Catch::Approx(ref[1]));
    CHECK(off[2] == Catch::Approx(ref[2]));

    // at_waterline: antenna height replaced by the waterline offset (projected onto the surface)
    const auto off_wl = scs.compute_position_system_offset(sd, ref_heading, true);
    const auto ref_wl = vessel_rel.rotate(ps.x, ps.y, scs.get_waterline_offset());
    CHECK(off_wl[0] == Catch::Approx(ref_wl[0]));
    CHECK(off_wl[1] == Catch::Approx(ref_wl[1]));
    CHECK(off_wl[2] == Catch::Approx(ref_wl[2]));

    // motion compensated: the reported position already coincides with the vessel reference point,
    // so the offset is zero (regardless of at_waterline)
    scs.set_position_source_motion_compensated(true);
    const auto off_mc = scs.compute_position_system_offset(sd, ref_heading);
    CHECK(off_mc[0] == 0.f);
    CHECK(off_mc[1] == 0.f);
    CHECK(off_mc[2] == 0.f);
}

TEST_CASE("sensorconfiguration get_target combines subarray offsets statically", TESTTAG)
{
    using themachinethatgoesping::tools::rotationfunctions::Rotation;

    SensorConfiguration scs;
    scs.add_target("mbes", datastructures::SensorPose("mbes", 1.f, 2.f, 3.f, 10.f, 20.f, 30.f));
    scs.add_target_subarray("mbes", "s",
                            datastructures::SensorPose("s", 0.1f, -0.2f, 0.3f, 0.f, 0.f, 0.f));

    const auto& target = scs.get_target("mbes");
    const auto  sub    = scs.get_target_subarray("mbes", "s");

    // combined pose (vessel-static frame): target position + target.rotation * subarray offset
    const auto combined = scs.get_target("mbes", "s");
    const auto off      = target.rotation.rotate(sub.x, sub.y, sub.z);
    CHECK(combined.x == Catch::Approx(target.x + off[0]));
    CHECK(combined.y == Catch::Approx(target.y + off[1]));
    CHECK(combined.z == Catch::Approx(target.z + off[2]));

    // "" subarray returns the plain target; a custom pose overrides the registered id
    CHECK(scs.get_target("mbes", "").x == Catch::Approx(target.x));
    const auto custom =
        scs.get_target("mbes", "s", datastructures::SensorPose("c", 0.f, 0.f, 1.f, 0.f, 0.f, 0.f));
    const auto coff = target.rotation.rotate(0.f, 0.f, 1.f);
    CHECK(custom.x == Catch::Approx(target.x + coff[0]));
    CHECK(custom.z == Catch::Approx(target.z + coff[2]));

    // compute_target_pose with a subarray == the pose of the combined static target
    datastructures::Sensordata sd(0.f, 0.f, 30.f, 4.f, -3.f);
    const float                ref        = 12.f;
    const auto                 pose_sub   = scs.compute_target_pose("mbes", sd, ref, "s");
    const Rotation<float>      vessel_rel = scs.get_vessel_rotation(sd, ref);
    const auto                 lever = vessel_rel.rotate(combined.x, combined.y, combined.z);
    CHECK(pose_sub.x == Catch::Approx(lever[0]));
    CHECK(pose_sub.y == Catch::Approx(lever[1]));
    CHECK(pose_sub.rotation == vessel_rel * combined.rotation);
}

TEST_CASE("sensorconfiguration should reproduce precomputed rotations when settings sensor offsets",
          TESTTAG)
{
    // initialize offsets
    datastructures::SensorPose targetOffsets("gps", 1, 2, 3, 0, 0, 0);

    SECTION("test depth sensor offsets")
    {
        SensorConfiguration scs;
        scs.add_target("mbes", targetOffsets);
        scs.set_depth_source("gps", 0, 0, 10);

        REQUIRE(scs.compute_target_position("mbes", datastructures::SensordataLocal()).z == -7);
    }

    SECTION("test imu sensor offsets")
    {
        SensorConfiguration scs;
        scs.add_target("mbes", targetOffsets);

        datastructures::SensordataLocal sensor_data;
        sensor_data.set_heading(90);
        sensor_data.set_roll(0);
        sensor_data.set_pitch(20);

        // imu yaw offset should not influence the resulting yaw because that is influenced only by
        // the heading but imu yaw offset of 90° should swap pitch and roll
        scs.set_attitude_source("gps", 90, 0, 0);
        auto position = scs.compute_target_position("mbes", sensor_data);

        REQUIRE_THAT(position.yaw(), Catch::Matchers::WithinAbs(90.f, 0.001f));
        REQUIRE_THAT(position.pitch(), Catch::Matchers::WithinAbs(0.f, 0.001f));
        REQUIRE_THAT(position.roll(), Catch::Matchers::WithinAbs(-20.f, 0.001f));

        sensor_data.set_roll(10);
        sensor_data.set_pitch(0);

        position = scs.compute_target_position("mbes", sensor_data);
        REQUIRE_THAT(position.yaw(), Catch::Matchers::WithinAbs(90.f, 0.001f));
        REQUIRE_THAT(position.pitch(), Catch::Matchers::WithinAbs(10.f, 0.001f));
        REQUIRE_THAT(position.roll(), Catch::Matchers::WithinAbs(0.f, 0.001f));

        scs.set_attitude_source("gps", 0, 1, 2);
        position = scs.compute_target_position("mbes", sensor_data);
        REQUIRE_THAT(position.yaw(), Catch::Matchers::WithinAbs(90.f, 0.001f));
        REQUIRE_THAT(position.pitch(), Catch::Matchers::WithinAbs(-0.9902670948f, 0.001f));
        REQUIRE_THAT(position.roll(), Catch::Matchers::WithinAbs(8.001202844f, 0.001f));
    }
}

TEST_CASE("sensorconfiguration merging operations", TESTTAG)
{
    // initialize offsets
    SensorConfiguration               scs;
    datastructures::SensorPose targetOffsets1("sensor1", 1, 2, 3, 0, 0, 0);
    datastructures::SensorPose targetOffsets2("sensor2", 1, 2, 3, 45, 5, 10);

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
    datastructures::SensorPose targetOffsets1("sensor1", 1, 2, 3, 0, 0, 0);
    datastructures::SensorPose targetOffsets2("sensor2", 1, 2, 3, 45, 5, 10);

    scs.add_target("mbes", targetOffsets1);
    scs.add_target("sbes", targetOffsets2);

    SECTION("NO_SENSOR_VALUES")
    {
        auto position_mbes = scs.compute_target_position("mbes", datastructures::SensordataLocal());
        auto position_sbes = scs.compute_target_position("sbes", datastructures::SensordataLocal());

        datastructures::GeolocationLocal expected_result_mbes(1, 2, 3, 0, 0, 0);
        datastructures::GeolocationLocal expected_result_sbes(1, 2, 3, 45, 5, 10);

        REQUIRE(position_mbes == expected_result_mbes);
        REQUIRE(position_sbes == expected_result_sbes);

        REQUIRE(scs.get_target("mbes") == targetOffsets1);
        REQUIRE(scs.get_target("sbes") == targetOffsets2);
    }

    SECTION("SENSOR_VALUES no roll/pitch")
    {
        // initialize sensor data
        datastructures::SensordataLocal sensor_data;
        sensor_data.depth    = 5;
        sensor_data.set_heading(0);
        sensor_data.set_pitch(0);
        sensor_data.set_roll(0);
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        auto position_mbes          = scs.compute_target_position("mbes", sensor_data);
        auto position_sbes          = scs.compute_target_position("sbes", sensor_data);
        auto relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        auto relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

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

        CHECK(position_mbes.yaw() == Catch::Approx(0.0));
        CHECK(position_mbes.pitch() == Catch::Approx(0.0));
        CHECK(position_mbes.roll() == Catch::Approx(0.0));
        CHECK(position_sbes.yaw() == Catch::Approx(45));
        CHECK(position_sbes.pitch() == Catch::Approx(5));
        REQUIRE(position_sbes.roll() == Catch::Approx(10));

        // scenario 0.2
        // initialize sensor data
        sensor_data.depth    = 5;
        sensor_data.set_heading(180);
        sensor_data.set_pitch(0);
        sensor_data.set_roll(0);
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

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

        REQUIRE_THAT(position_mbes.yaw(), Catch::Matchers::WithinAbs(180.f, 0.001f));
        REQUIRE_THAT(position_mbes.pitch(), Catch::Matchers::WithinAbs(0.f, 0.001f));
        REQUIRE_THAT(position_mbes.roll(), Catch::Matchers::WithinAbs(0.f, 0.001f));
        REQUIRE_THAT(position_sbes.yaw(), Catch::Matchers::WithinAbs(225.f, 0.001f));
        REQUIRE_THAT(position_sbes.pitch(), Catch::Matchers::WithinAbs(5.f, 0.001f));
        REQUIRE_THAT(position_sbes.roll(), Catch::Matchers::WithinAbs(10.f, 0.001f));

        // scenario 0.3
        // initialize sensor data
        sensor_data.depth    = 5;
        sensor_data.set_heading(90);
        sensor_data.set_pitch(0);
        sensor_data.set_roll(0);
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

        // check results
        REQUIRE_THAT(position_mbes.z, Catch::Matchers::WithinAbs(8.f, 0.001f));
        REQUIRE(position_mbes.z == position_sbes.z);

        REQUIRE_THAT(relative_position_mbes.northing, Catch::Matchers::WithinAbs(-2.f, 0.001f));
        REQUIRE_THAT(relative_position_mbes.easting, Catch::Matchers::WithinAbs(1.f, 0.001f));
        REQUIRE_THAT(position_mbes.northing, Catch::Matchers::WithinAbs(8.f, 0.001f));
        REQUIRE_THAT(position_mbes.easting, Catch::Matchers::WithinAbs(21.f, 0.001f));

        REQUIRE(relative_position_mbes.northing == relative_position_sbes.northing);
        REQUIRE(relative_position_mbes.easting == relative_position_sbes.easting);
        REQUIRE(position_mbes.northing == position_sbes.northing);
        REQUIRE(position_mbes.easting == position_sbes.easting);

        REQUIRE_THAT(position_mbes.yaw(), Catch::Matchers::WithinAbs(90.f, 0.001f));
        REQUIRE_THAT(position_mbes.pitch(), Catch::Matchers::WithinAbs(0.f, 0.001f));
        REQUIRE_THAT(position_mbes.roll(), Catch::Matchers::WithinAbs(0.f, 0.001f));
        REQUIRE_THAT(position_sbes.yaw(), Catch::Matchers::WithinAbs(135.f, 0.001f));
        REQUIRE_THAT(position_sbes.pitch(), Catch::Matchers::WithinAbs(5.f, 0.001f));
        REQUIRE_THAT(position_sbes.roll(), Catch::Matchers::WithinAbs(10.f, 0.001f));
    }

    SECTION("SENSOR_VALUES XY coordinates")
    {
        datastructures::SensordataLocal sensor_data;
        // scenario 1
        sensor_data.depth    = 5;
        sensor_data.set_heading(25);
        sensor_data.set_pitch(20);
        sensor_data.set_roll(10);
        sensor_data.northing = 10;
        sensor_data.easting  = 20;

        // compute sensor positions
        auto position_mbes          = scs.compute_target_position("mbes", sensor_data);
        auto position_sbes          = scs.compute_target_position("sbes", sensor_data);
        auto relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        auto relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

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

        CHECK(position_mbes.yaw() == Catch::Approx(25.0));
        CHECK(position_mbes.pitch() == Catch::Approx(20.0));
        CHECK(position_mbes.roll() == Catch::Approx(10.0));
        CHECK(position_sbes.yaw() == Catch::Approx(71.4260001287));
        CHECK(position_sbes.pitch() == Catch::Approx(11.9252923155));
        CHECK(position_sbes.roll() == Catch::Approx(31.4141895033));

        // scenario 2
        sensor_data.depth    = -5;
        sensor_data.set_heading(-35);
        sensor_data.set_pitch(-5);
        sensor_data.set_roll(-15);
        sensor_data.northing = -23;
        sensor_data.easting  = -20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

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

        CHECK(position_mbes.yaw() == Catch::Approx(325.0));
        CHECK(position_mbes.pitch() == Catch::Approx(-5.0));
        CHECK(position_mbes.roll() == Catch::Approx(-15.0));
        CHECK(position_sbes.yaw() == Catch::Approx(7.2216796191));
        CHECK(position_sbes.pitch() == Catch::Approx(11.7764820146));
        CHECK(position_sbes.roll() == Catch::Approx(-4.429576033));

        // scenario 3
        sensor_data.depth    = 3;
        sensor_data.set_heading(30);
        sensor_data.set_pitch(-5);
        sensor_data.set_roll(-15);
        sensor_data.northing = 100;
        sensor_data.easting  = -20;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

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

        CHECK(position_mbes.yaw() == Catch::Approx(30.0));
        CHECK(position_mbes.pitch() == Catch::Approx(-5.0));
        CHECK(position_mbes.roll() == Catch::Approx(-15.0));
        CHECK(position_sbes.yaw() == Catch::Approx(72.2216796191));
        CHECK(position_sbes.pitch() == Catch::Approx(11.7764820146));
        CHECK(position_sbes.roll() == Catch::Approx(-4.429576033));

        // scenario 4
        sensor_data.depth    = -2000;
        sensor_data.set_heading(-470);
        sensor_data.set_pitch(-59);
        sensor_data.set_roll(1);
        sensor_data.northing = 23;
        sensor_data.easting  = -1000;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

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

        CHECK(position_mbes.yaw() == Catch::Approx(250.0));
        CHECK(position_mbes.pitch() == Catch::Approx(-59.0));
        CHECK(position_mbes.roll() == Catch::Approx(1.0).margin(1e-3));
        CHECK(position_sbes.yaw() == Catch::Approx(308.8301085148));
        CHECK(position_sbes.pitch() == Catch::Approx(-34.4198234806));
        CHECK(position_sbes.roll() == Catch::Approx(-36.6392731807));
    }

    SECTION("SENSOR_VALUES latitude and longitude")
    {
        datastructures::SensordataLatLon sensor_data;

        // scenario 5 (latlon)
        sensor_data.depth     = 2000;
        sensor_data.set_heading(470);
        sensor_data.set_pitch(-59);
        sensor_data.set_roll(1);
        sensor_data.latitude  = 54.123;
        sensor_data.longitude = -10.123;

        auto position_mbes          = scs.compute_target_position("mbes", sensor_data);
        auto position_sbes          = scs.compute_target_position("sbes", sensor_data);
        auto relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        auto relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(2002.4200235047));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(position_mbes.latitude == Catch::Approx(54.1229869952));
        CHECK(position_mbes.longitude == Catch::Approx(-10.123067173));

        CHECK(position_mbes.yaw() == Catch::Approx(110.0));
        CHECK(position_mbes.pitch() == Catch::Approx(-59.0));
        CHECK(position_mbes.roll() == Catch::Approx(1.0));
        CHECK(position_sbes.yaw() == Catch::Approx(168.8301085148));
        CHECK(position_sbes.pitch() == Catch::Approx(-34.4198234806));
        CHECK(position_sbes.roll() == Catch::Approx(-36.6392731807));

        // check if results with UTM are the same as with latlon
        datastructures::GeolocationUTM position_mbes_utm =
            scs.compute_target_position("mbes", datastructures::SensordataUTM(sensor_data));
        datastructures::GeolocationUTM position_sbes_utm =
            scs.compute_target_position("sbes", datastructures::SensordataUTM(sensor_data));
        CHECK(position_mbes_utm == datastructures::GeolocationUTM(position_mbes));
        CHECK(position_sbes_utm == datastructures::GeolocationUTM(position_sbes));

        // scenario 6 (latlon)
        sensor_data.depth     = 1000;
        sensor_data.set_heading(360);
        sensor_data.set_pitch(9);
        sensor_data.set_roll(-1);
        sensor_data.latitude  = -74.123;
        sensor_data.longitude = 1.123;

        // compute sensor positions
        position_mbes          = scs.compute_target_position("mbes", sensor_data);
        position_sbes          = scs.compute_target_position("sbes", sensor_data);
        relative_position_mbes = scs.compute_target_position(
            "mbes",
            datastructures::Sensordata(
                sensor_data)); // convert to Sensordata (without xy coordinates)
        relative_position_sbes =
            scs.compute_target_position("sbes", datastructures::Sensordata(sensor_data));

        CHECK(position_mbes.z == Catch::Approx(1002.7717041909f));
        REQUIRE(position_mbes.z == position_sbes.z);

        CHECK(position_mbes.latitude == Catch::Approx(-74.1229869952));
        CHECK(position_mbes.longitude == Catch::Approx(1.123067173));

        REQUIRE_THAT(position_mbes.yaw(), Catch::Matchers::WithinAbs(0, 0.001f));
        REQUIRE_THAT(position_mbes.pitch(), Catch::Matchers::WithinAbs(9.f, 0.001f));
        REQUIRE_THAT(position_mbes.roll(), Catch::Matchers::WithinAbs(-1.f, 0.001f));
        REQUIRE_THAT(position_sbes.yaw(), Catch::Matchers::WithinAbs(45.936f, 0.001f));
        REQUIRE_THAT(position_sbes.pitch(), Catch::Matchers::WithinAbs(12.029f, 0.001f));
        REQUIRE_THAT(position_sbes.roll(), Catch::Matchers::WithinAbs(15.775f, 0.001f));

        // check if results with UTM are the same as with latlon
        position_mbes_utm =
            scs.compute_target_position("mbes", datastructures::SensordataUTM(sensor_data));
        position_sbes_utm =
            scs.compute_target_position("sbes", datastructures::SensordataUTM(sensor_data));
        CHECK(position_mbes_utm == datastructures::GeolocationUTM(position_mbes));
        CHECK(position_sbes_utm == datastructures::GeolocationUTM(position_sbes));
    }
}