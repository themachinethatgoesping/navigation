// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::datastructures;

#define TESTTAG "[data]"

TEST_CASE("SensorData should support common functions", TESTTAG)
{
    // initialize data
    auto data = SensorData();

    data.gps_latitude  = 1;
    data.gps_longitude = 2;
    data.gps_z         = 3;

    data.compass_heading = 10;
    data.heave_heave = 1;

    data.imu_yaw   = 10;
    data.imu_pitch = 20;
    data.imu_roll  = 30;

    // test copy
    REQUIRE(data == SensorData(data));

    // test binary
    REQUIRE(data == SensorData(data.from_binary(data.to_binary())));

    // test stream
    std::stringstream buffer;
    data.to_stream(buffer);
    REQUIRE(data == SensorData(data.from_stream(buffer)));

    // test print does not crash
    REQUIRE(data.info_string().size() != 0);

    data.print(std::cerr);
    data.compass_heading = NAN;
    REQUIRE(data.info_string().find("invalid") != std::string::npos);

    data.compass_heading = 12;
    data.print(std::cerr);
    REQUIRE(data.info_string().find("valid") != std::string::npos);
}