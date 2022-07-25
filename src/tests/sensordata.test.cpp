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

    location.latitude  = 1;
    location.longitude = 2;
    location.z         = 3;

    location.heading = NAN;
    location.heave = 1;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

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

    location.heading = 12;
    location.print(std::cerr);
    REQUIRE(location.info_string().find("valid") != std::string::npos);
}