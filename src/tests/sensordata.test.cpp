// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/sensordata.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[location]"

TEST_CASE("SensorData should support common functions", TESTTAG)
{
    // initialize location
    auto location = SensorData();

    location.gps_latitude  = 1;
    location.gps_longitude = 2;
    location.gps_z         = 3;

    location.compass_heading = NAN;
    location.heave_heave = 1;

    location.imu_yaw   = 10;
    location.imu_pitch = 20;
    location.imu_roll  = 30;

    // test copy
    REQUIRE(location == SensorData(location));

    // test binary
    REQUIRE(location == SensorData(location.from_binary(location.to_binary())));

    // test stream
    std::stringstream buffer;
    location.to_stream(buffer);
    REQUIRE(location == SensorData(location.from_stream(buffer)));

    // test print does not crash
    REQUIRE(location.info_string().size() != 0);

    location.print(std::cerr);
    REQUIRE(location.info_string().find("invalid") != std::string::npos);

    location.compass_heading = 12;
    location.print(std::cerr);
    REQUIRE(location.info_string().find("valid") != std::string::npos);
}