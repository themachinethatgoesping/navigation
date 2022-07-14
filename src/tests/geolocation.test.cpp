// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/geolocation.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("GeoLocation should support common functions", TESTTAG)
{
    // initialize offsets
    auto offsets = GeoLocation();

    offsets.latitude  = 1;
    offsets.longitude = 2;
    offsets.z         = 3;

    offsets.yaw   = 10;
    offsets.pitch = 20;
    offsets.roll  = 30;

    // test copy
    REQUIRE(offsets == GeoLocation(offsets));

    // test binary
    REQUIRE(offsets == GeoLocation(offsets.from_binary(offsets.to_binary())));

    // test stream
    std::stringstream buffer;
    offsets.to_stream(buffer);
    REQUIRE(offsets == GeoLocation(offsets.from_stream(buffer)));

    // test print does not crash
    REQUIRE(offsets.info_string().size() != 0);
}