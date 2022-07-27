// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/sensorcoordinatesystem.hpp"
#include "../themachinethatgoesping/navigation/navdata.hpp"

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
    SensorCoordinateSystem            scs;
    navdata::PositionalOffsets targetOffsets1(1, 2, 3, 0, 0, 0);
    navdata::PositionalOffsets targetOffsets2(1, 2, 3, 45, 5, 10);

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
        REQUIRE(std::get<0>(scs.get_targetYPR("MBES")) == Approx(0));
        REQUIRE(std::get<1>(scs.get_targetYPR("MBES")) == Approx(0));
        REQUIRE(std::get<2>(scs.get_targetYPR("MBES")) == Approx(0));

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
        REQUIRE(std::get<0>(scs.get_targetYPR("SBES")) == Approx(45));
        REQUIRE(std::get<1>(scs.get_targetYPR("SBES")) == Approx(5));
        REQUIRE(std::get<2>(scs.get_targetYPR("SBES")) == Approx(10));
    }

    SECTION("SENSOR_VALUES")
    {

        navdata::SensorDataLocal sensor_data;
        // scenario 0.1
        sensor_data.gps_z = 5;
        sensor_data.compass_heading = 0;
        sensor_data.imu_yaw = 40; //ignored because compass_heading is valid
        sensor_data.imu_pitch = 0;
        sensor_data.imu_roll = 0;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemXY(10, 20);

        REQUIRE(scs.get_targetDepth("MBES") == Approx(8.0));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(1.0));
        REQUIRE(scs.get_targetXY("MBES", false).second == Approx(2.0));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        //CHECK(scs.get_targetXY("MBES", true).first == Approx(-9));
        //CHECK(scs.get_targetXY("MBES", true).second == Approx(-18));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(11));
        REQUIRE(scs.get_targetXY("MBES", true).second == Approx(22));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.2360679775));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(63.4349488229));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("SBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(45));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(5));
        REQUIRE(std::get<2>(scs.get_targetYPR("SBES")) == Approx(10));

        // scenario 0.2
        sensor_data.gps_z = 5;
        sensor_data.compass_heading = 180;
        sensor_data.imu_yaw = 40; //ignored because compass_heading is valid
        sensor_data.imu_pitch = 0;
        sensor_data.imu_roll = 0;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemXY(10, 20);

        REQUIRE(scs.get_targetDepth("MBES") == Approx(8.0));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(-1.0));
        REQUIRE(scs.get_targetXY("MBES", false).second == Approx(-2.0));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        //CHECK(scs.get_targetXY("MBES", true).first == Approx(-9));
        //CHECK(scs.get_targetXY("MBES", true).second == Approx(-18));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(9));
        REQUIRE(scs.get_targetXY("MBES", true).second == Approx(18));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.2360679775));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(63.4349488229 + 180));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("SBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(180.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(225));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(5));
        REQUIRE(std::get<2>(scs.get_targetYPR("SBES")) == Approx(10));

        // scenario 0.3
        sensor_data.gps_z = 5;
        sensor_data.compass_heading = 90;
        sensor_data.imu_yaw = 40; //ignored because compass_heading is valid
        sensor_data.imu_pitch = 0;
        sensor_data.imu_roll = 0;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemXY(10, 20);

        REQUIRE(scs.get_targetDepth("MBES") == Approx(8.0));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(-2.0));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(1.0));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        //CHECK(scs.get_targetXY("MBES", true).first == Approx(-9));
        //CHECK(scs.get_targetXY("MBES", true).second == Approx(-18));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(8));
        REQUIRE(scs.get_targetXY("MBES", true).second == Approx(21));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.2360679775));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(63.4349488229 + 90));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("SBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(90.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(135));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(5));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(10));

        // scenario 1
        sensor_data.gps_z = 5;
        sensor_data.compass_heading = 25;
        sensor_data.imu_yaw = 40;
        sensor_data.imu_pitch = 20;
        sensor_data.imu_roll = 10;
        scs.set_sensor_data(sensor_data);

        scs.set_positionSystemXY(10, 20);
        REQUIRE(scs.get_targetDepth("MBES") == Approx(7.7605814142));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(1.262868183));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(2.1873166684));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(11.262868183));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(22.1873166684));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.5257058925));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(59.9996008822));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("MBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("SBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(25.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(20.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(10.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(71.4260001287));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(11.9252923155));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(31.4141895033));

        // scenario 2
        sensor_data.gps_z = -5;
        sensor_data.compass_heading = -35;
        sensor_data.imu_yaw = 40;
        sensor_data.imu_pitch = -5;
        sensor_data.imu_roll = -15;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemXY(-23, -20);
        CHECK(scs.get_targetDepth("MBES") == Approx(-2.5417620175));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(2.1995298195));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(1.7661071866));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(-20.8004701805));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(-18.2338928134));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8208271875));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(38.7626389216));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(325.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(-5.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(-15.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(7.2216796191));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(11.7764820146));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(-4.429576033));

        // scenario 3
        sensor_data.gps_z = 3;
        sensor_data.compass_heading = NAN;
        sensor_data.imu_yaw = 30;
        sensor_data.imu_pitch = -5;
        sensor_data.imu_roll = -15;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemXY(100, -20);
        CHECK(scs.get_targetDepth("MBES") == Approx(5.4582379825));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(-0.671075227));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(2.7398401525));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(99.328924773));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(-17.2601598475));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8208271875));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(103.7626389216));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(30.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(-5.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(-15.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(72.2216796191));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(11.7764820146));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(-4.429576033));

        // scenario 4
        sensor_data.gps_z = -2000;
        sensor_data.compass_heading = -470;
        sensor_data.imu_yaw = 40;
        sensor_data.imu_pitch = -59;
        sensor_data.imu_roll = 1;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemXY(23, -1000);
        CHECK(scs.get_targetDepth("MBES") == Approx(-1997.5799764953));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetXY("MBES", false).first == Approx(2.5433504005));
        CHECK(scs.get_targetXY("MBES", false).second == Approx(1.2941618821));
        REQUIRE(scs.get_targetXY("MBES", false) == scs.get_targetXY("SBES", false));
        CHECK(scs.get_targetXY("MBES", true).first == Approx(25.5433504005));
        CHECK(scs.get_targetXY("MBES", true).second == Approx(-998.7058381179));
        REQUIRE(scs.get_targetXY("MBES", true) == scs.get_targetXY("SBES", true));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8536794208));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(26.9688745148));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(250.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(-59.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(1.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(308.8301085148));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(-34.4198234806));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(-36.6392731807));

        // scenario 5 (latlon)
        sensor_data.gps_z = 2000;
        sensor_data.compass_heading = 470;
        sensor_data.imu_yaw = 40;
        sensor_data.imu_pitch = -59;
        sensor_data.imu_roll = 1;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemLatLon(54.123, -10.123);
        CHECK(scs.get_targetDepth("MBES") == Approx(2002.4200235047));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetLatLon("MBES").first == Approx(54.1229899697));
        CHECK(scs.get_targetLatLon("MBES").second == Approx(-10.1230401671));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.8536794208));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(246.9688745148));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(110.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(-59.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(1.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(168.8301085148));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(-34.4198234806));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(-36.6392731807));

        // scenario 6 (latlon)
        sensor_data.gps_z = 1000;
        sensor_data.compass_heading = 360;
        sensor_data.imu_yaw = 40;
        sensor_data.imu_pitch = 9;
        sensor_data.imu_roll = -1;
        scs.set_sensor_data(sensor_data);
        scs.set_positionSystemLatLon(-74.123, 1.123);
        CHECK(scs.get_targetDepth("MBES") == Approx(1002.7717041909));
        REQUIRE(scs.get_targetDepth("MBES") == scs.get_targetDepth("SBES"));

        CHECK(scs.get_targetLatLon("MBES").first == Approx(-74.1229869952));
        CHECK(scs.get_targetLatLon("MBES").second == Approx(1.123067173));

        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).first == Approx(2.513494754));
        CHECK(scs.get_targetPosSysDistanceAndAzimuth("MBES", false).second ==
              Approx(54.7274278634));
        REQUIRE(scs.get_targetPosSysDistanceAndAzimuth("SBES", false) ==
                scs.get_targetPosSysDistanceAndAzimuth("MBES", false));

        CHECK(std::get<0>(scs.get_targetYPR("MBES")) == Approx(0.0));
        CHECK(std::get<1>(scs.get_targetYPR("MBES")) == Approx(9.0));
        CHECK(std::get<2>(scs.get_targetYPR("MBES")) == Approx(-1.0));
        CHECK(std::get<0>(scs.get_targetYPR("SBES")) == Approx(45.9361957025));
        CHECK(std::get<1>(scs.get_targetYPR("SBES")) == Approx(12.0290113349));
        CHECK(std::get<2>(scs.get_targetYPR("SBES")) == Approx(15.7758445678));
    }
}