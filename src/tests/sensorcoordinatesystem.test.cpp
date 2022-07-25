// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/sensorcoordinatesystem.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("sensorcoordinatesystem should support common functions", TESTTAG)
{
    // initialize offsets
    SensorCoordinateSystem scs;

    // copy constructor
    SensorCoordinateSystem scs2(scs);
}

TEST_CASE("sensorcoordinatesystem should reproduce precomputed rotations", TESTTAG)
{
    // initialize offsets
    SensorCoordinateSystem scs;
    PositionalOffsets      targetOffsets1(1, 2, 3, 0, 0, 0);
    PositionalOffsets      targetOffsets2(1, 2, 3, 45, 5, 10);

    scs.set_targetOffsets("MBES", targetOffsets1);
    scs.set_targetOffsets("SBES", targetOffsets2);
    // double x= 1;
    // double y= 2;
    // double depth= 3;
    // double heave= 4;
    // double heading = 45;
    // double yaw = 90;
    // double pitch = 0;
    // double roll = 0;

    SECTION("NO_SENSOR_VALUES")
    {
        REQUIRE(scs.get_targetDepth("MBES") == 3);
        REQUIRE(scs.get_targetXY("MBES", false).first == 1);
        REQUIRE(scs.get_targetXY("MBES", false).second == 2);
        REQUIRE(scs.get_targetXY("MBES", true).first == 1);
        REQUIRE(scs.get_targetXY("MBES", true).second == 2);
        REQUIRE(scs.get_targetOffsets("MBES") == targetOffsets1);
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first ==
                Approx(2.2360679775));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
                Approx(63.4349488229));
        REQUIRE(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(0));
        REQUIRE(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(0));
        REQUIRE(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(0));

        REQUIRE(scs.get_targetDepth("SBES") == 3);
        REQUIRE(scs.get_targetXY("SBES", false).first == 1);
        REQUIRE(scs.get_targetXY("SBES", false).second == 2);
        REQUIRE(scs.get_targetXY("SBES", true).first == 1);
        REQUIRE(scs.get_targetXY("SBES", true).second == 2);
        REQUIRE(scs.get_targetOffsets("SBES") == targetOffsets2);
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false).first ==
                Approx(2.2360679775));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false).second ==
                Approx(63.4349488229));
        REQUIRE(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(45));
        REQUIRE(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(5));
        REQUIRE(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(10));
    }

    SECTION("SENSOR_VALUES")
    {
        // scenario 1
        scs.set_depthSensorDepth(5);
        scs.set_compassHeading(25);
        scs.set_motionSensorYPR(40, 20, 10, false);
        scs.set_positionSystemXY(10, 20);
        REQUIRE(scs.get_targetDepth("MBES") == Approx(7.7605814142));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(1.262868183));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(2.1873166684));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(-8.737131817));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(-17.8126833316));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.5257058925));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(59.9996008822));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false) ==
              scs.get_targetPosSysDistanceAndAzimuth("SBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(25.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(20.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(10.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(71.4260001287));
        CHECK(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(11.9252923155));
        CHECK(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(31.4141895033));

        // scenario 2
        scs.set_depthSensorDepth(-5);
        scs.set_compassHeading(-35);
        scs.set_motionSensorYPR(40, -5, -15, false);
        scs.set_positionSystemXY(-23, -20);
        CHECK(scs.get_targetDepth("MBES") == Approx(-2.5417620175));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(2.1995298195));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(1.7661071866));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(25.1995298195));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(21.7661071866));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8208271875));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(38.7626389216));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false)==
              scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(325.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(-5.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(-15.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(7.2216796191));
        CHECK(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(11.7764820146));
        CHECK(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(-4.429576033));

        // scenario 3
        scs.set_depthSensorDepth(3);
        scs.set_compassHeading(120);
        scs.set_motionSensorYPR(30, -5, -15, true);
        scs.set_positionSystemXY(100, -20);
        CHECK(scs.get_targetDepth("MBES") == Approx(5.4582379825));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(-0.671075227));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(2.7398401525));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(-100.671075227));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(22.7398401525));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8208271875));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(103.7626389216));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false)==
              scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(30.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(-5.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(-15.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(72.2216796191));
        CHECK(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(11.7764820146));
        CHECK(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(-4.429576033));

        // scenario 4
        scs.set_depthSensorDepth(-2000);
        scs.set_compassHeading(-470);
        scs.set_motionSensorYPR(40, -59, 1, false);
        scs.set_positionSystemXY(23, -1000);
        CHECK(scs.get_targetDepth("MBES") == Approx(-1997.5799764953));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(2.5433504005));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(1.2941618821));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(-20.4566495995));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(1001.2941618821));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8536794208));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(26.9688745148));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false)==
              scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(250.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(-59.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(1.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(308.8301085148));
        CHECK(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(-34.4198234806));
        CHECK(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(-36.6392731807));

        // scenario 5 (latlon)
        scs.set_depthSensorDepth(2000);
        scs.set_compassHeading(470);
        scs.set_motionSensorYPR(40, -59, 1, false);
        scs.set_positionSystemLatLon(54.123, -10.123);
        CHECK(scs.get_targetDepth("MBES") == Approx(2002.4200235047));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetLatLon("MBES").first == Approx(54.1229899697));
        CHECK(scs.get_targetLatLon("MBES").second == Approx(-10.1230401671));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8536794208));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(246.9688745148));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false)==
              scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(110.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(-59.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(1.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(168.8301085148));
        CHECK(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(-34.4198234806));
        CHECK(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(-36.6392731807));

        // scenario 6 (latlon)
        scs.set_depthSensorDepth(1000);
        scs.set_compassHeading(360);
        scs.set_motionSensorYPR(40, 9, -1, false);
        scs.set_positionSystemLatLon(-74.123, 1.123);
        CHECK(scs.get_targetDepth("MBES") == Approx(1002.7717041909));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetLatLon("MBES").first == Approx(-74.1229869952));
        CHECK(scs.get_targetLatLon("MBES").second == Approx(1.123067173));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.513494754));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(54.7274278634));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false)==
              scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES", false)) == Approx(0.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES", false)) == Approx(9.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES", false)) == Approx(-1.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES", false)) == Approx(45.9361957025));
        CHECK(std::get<1>(scs.get_targetYPR("SBES", false)) == Approx(12.0290113349));
        CHECK(std::get<2>(scs.get_targetYPR("SBES", false)) == Approx(15.7758445678));
    }
}