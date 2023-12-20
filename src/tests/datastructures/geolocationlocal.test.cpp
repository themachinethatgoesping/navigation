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

TEST_CASE("GeolocationLocal should support common functions", TESTTAG)
{
    // initialize location
    auto location = GeolocationLocal();

    location.northing = 5652759.000;
    location.easting  = 549841.192;
    location.z        = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test copy
    REQUIRE(location == GeolocationLocal(location));

    // test binary
    REQUIRE(location == GeolocationLocal(location.from_binary(location.to_binary())));

    // test stream
    std::stringstream buffer;
    location.to_stream(buffer);
    REQUIRE(location == GeolocationLocal(location.from_stream(buffer)));

    // test print does not crash
    REQUIRE(location.info_string().size() != 0);
}

TEST_CASE("GeolocationLocal should support common utm/local conversions", TESTTAG)
{
    // initialize location
    auto location = GeolocationLocal();

    location.northing        = 5652759.000;
    location.easting         = 549841.192;
    location.z               = 3;
    int  zone                = 31;
    bool northern_hemisphere = true;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test utm/lat lon conversion
    GeolocationUTM location_utm(location, zone, northern_hemisphere);

    location.print(std::cerr);
    location_utm.print(std::cerr);
    GeolocationLocal(location_utm).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(location_utm == GeolocationUTM(location, zone, northern_hemisphere));
    REQUIRE(location == GeolocationLocal(location_utm));
}