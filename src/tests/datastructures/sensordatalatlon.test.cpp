// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::datastructures;

#define TESTTAG "[data]"

TEST_CASE("SensorDataLatLon should support common functions", TESTTAG)
{
    // initialize data
    auto data = SensorDataLatLon();

    data.latitude  = 1;
    data.longitude = 2;
    data.depth     = 3;

    data.heading = 10;
    data.heave   = 1;

    data.pitch = 20;
    data.roll  = 30;

    // test copy
    REQUIRE(data == SensorDataLatLon(data));

    // test binary
    REQUIRE(data == SensorDataLatLon(data.from_binary(data.to_binary())));

    // test stream
    std::stringstream buffer;
    data.to_stream(buffer);
    REQUIRE(data == SensorDataLatLon(data.from_stream(buffer)));

    // test print does not crash
    REQUIRE(data.info_string().size() != 0);

    data.heading = 12;
    data.print(std::cerr);
    REQUIRE(data.info_string().find("heading") != std::string::npos);
}