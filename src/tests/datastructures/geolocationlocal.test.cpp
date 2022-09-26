// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_all.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::datastructures;

#define TESTTAG "[location]"

TEST_CASE("GeoLocationLocal should support common functions", TESTTAG)
{
    // initialize location
    auto location = GeoLocationLocal();

    location.northing = 5652759.000;
    location.easting  = 549841.192;
    location.z        = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test copy
    REQUIRE(location == GeoLocationLocal(location));

    // test binary
    REQUIRE(location == GeoLocationLocal(location.from_binary(location.to_binary())));

    // test stream
    std::stringstream buffer;
    location.to_stream(buffer);
    REQUIRE(location == GeoLocationLocal(location.from_stream(buffer)));

    // test print does not crash
    REQUIRE(location.info_string().size() != 0);
}

TEST_CASE("GeoLocationLocal should support common utm/local conversions", TESTTAG)
{
    // initialize location
    auto location = GeoLocationLocal();

    location.northing        = 5652759.000;
    location.easting         = 549841.192;
    location.z               = 3;
    int  zone                = 31;
    bool northern_hemisphere = true;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test utm/lat lon conversion
    GeoLocationUTM location_utm(location, zone, northern_hemisphere);

    location.print(std::cerr);
    location_utm.print(std::cerr);
    GeoLocationLocal(location_utm).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(location_utm == GeoLocationUTM(location, zone, northern_hemisphere));
    REQUIRE(location == GeoLocationLocal(location_utm));
}