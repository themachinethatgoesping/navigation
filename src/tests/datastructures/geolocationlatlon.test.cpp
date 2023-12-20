// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::datastructures;

#define TESTTAG "[location]"

TEST_CASE("GeolocationLatLon should support common functions", TESTTAG)
{
    // initialize location
    auto location = GeolocationLatLon();

    location.latitude  = 1;
    location.longitude = 2;
    location.z         = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test copy
    REQUIRE(location == GeolocationLatLon(location));

    // test binary
    REQUIRE(location == GeolocationLatLon(location.from_binary(location.to_binary())));

    // test stream
    std::stringstream buffer;
    location.to_stream(buffer);
    REQUIRE(location == GeolocationLatLon(location.from_stream(buffer)));

    // test print does not crash
    REQUIRE(location.info_string().size() != 0);
}