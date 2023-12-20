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

TEST_CASE("GeolocationUTM should support common functions", TESTTAG)
{
    // initialize location
    auto location = GeolocationUTM();

    location.northing                = 5652759.000;
    location.easting                 = 549841.192;
    location.utm_zone                = 31;
    location.northern_hemisphere = true;
    location.z                       = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test copy
    REQUIRE(location == GeolocationUTM(location));

    // test binary
    REQUIRE(location == GeolocationUTM(location.from_binary(location.to_binary())));

    // test stream
    std::stringstream buffer;
    location.to_stream(buffer);
    REQUIRE(location == GeolocationUTM(location.from_stream(buffer)));

    // test print does not crash
    REQUIRE(location.info_string().size() != 0);
}

TEST_CASE("GeolocationUTM should support common utm/latlon conversions", TESTTAG)
{
    // initialize location
    auto location = GeolocationUTM();

    location.northing                = 5652759.000;
    location.easting                 = 549841.192;
    location.utm_zone                = 31;
    location.northern_hemisphere = true;
    location.z                       = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    auto location_south                    = GeolocationUTM(location);
    location_south.northing                = 5427745.995;
    location_south.easting                 = 314082.699;
    location_south.utm_zone                = 60;
    location_south.northern_hemisphere = false;

    // test utm/lat lon conversion
    GeolocationLatLon location_latlon(location);
    GeolocationUTM    location_utm(location_latlon);

    location_latlon.print(std::cerr);
    location.print(std::cerr);
    location_utm.print(std::cerr);
    GeolocationUTM::from_geolocation_latlon(location_latlon).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(location_latlon == GeolocationUTM::to_geolocation_latlon(location));
    REQUIRE(location_utm == GeolocationUTM::from_geolocation_latlon(location_latlon));

    // to/from conversion should reproduce the original zone
    REQUIRE(location == location_utm);
    REQUIRE(location_latlon == GeolocationLatLon(location_utm));
    REQUIRE(location_south == GeolocationUTM(GeolocationLatLon(location_south)));
    REQUIRE(GeolocationLatLon(location_south) ==
            GeolocationLatLon(GeolocationUTM(GeolocationLatLon(location_south))));

    // test simple explicit conversion
    REQUIRE(location == GeolocationUTM(location_latlon));

    // test precomputed conversion (north)
    REQUIRE(location_latlon.latitude == Catch::Approx(51.024224));
    REQUIRE(location_latlon.longitude == Catch::Approx(3.710670));

    // test precomputed conversion (north)
    REQUIRE(GeolocationLatLon(location_south).latitude == Catch::Approx(-41.280330));
    REQUIRE(GeolocationLatLon(location_south).longitude == Catch::Approx(174.780011));
}