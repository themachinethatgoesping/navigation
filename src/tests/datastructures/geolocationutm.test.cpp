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

TEST_CASE("GeoLocationUTM should support common functions", TESTTAG)
{
    // initialize location
    auto location = GeoLocationUTM();

    location.northing            = 5652759.000;
    location.easting             = 549841.192;
    location.zone                = 31;
    location.northern_hemisphere = true;
    location.z                   = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    // test copy
    REQUIRE(location == GeoLocationUTM(location));

    // test binary
    REQUIRE(location == GeoLocationUTM(location.from_binary(location.to_binary())));

    // test stream
    std::stringstream buffer;
    location.to_stream(buffer);
    REQUIRE(location == GeoLocationUTM(location.from_stream(buffer)));

    // test print does not crash
    REQUIRE(location.info_string().size() != 0);
}

TEST_CASE("GeoLocationUTM should support common utm/latlon conversions", TESTTAG)
{
    // initialize location
    auto location = GeoLocationUTM();

    location.northing            = 5652759.000;
    location.easting             = 549841.192;
    location.zone                = 31;
    location.northern_hemisphere = true;
    location.z                   = 3;

    location.yaw   = 10;
    location.pitch = 20;
    location.roll  = 30;

    auto location_south                = GeoLocationUTM(location);
    location_south.northing            = 5427745.995;
    location_south.easting             = 314082.699;
    location_south.zone                = 60;
    location_south.northern_hemisphere = false;

    // test utm/lat lon conversion
    GeoLocationLatLon location_latlon(location);
    GeoLocationUTM    location_utm(location_latlon);

    location_latlon.print(std::cerr);
    location.print(std::cerr);
    location_utm.print(std::cerr);
    GeoLocationUTM::from_geolocation_latlon(location_latlon).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(location_latlon == GeoLocationUTM::to_geolocation_latlon(location));
    REQUIRE(location_utm == GeoLocationUTM::from_geolocation_latlon(location_latlon));

    // to/from conversion should reproduce the original zone
    REQUIRE(location == location_utm);
    REQUIRE(location_latlon == GeoLocationLatLon(location_utm));
    REQUIRE(location_south == GeoLocationUTM(GeoLocationLatLon(location_south)));
    REQUIRE(GeoLocationLatLon(location_south) ==
            GeoLocationLatLon(GeoLocationUTM(GeoLocationLatLon(location_south))));

    // test the same as above but using implicit conversion
    REQUIRE(location == location_latlon);
    REQUIRE(location_south == GeoLocationLatLon(location_south));

    // test precomputed conversion (north)
    REQUIRE(location_latlon.latitude == Catch::Approx(51.024224));
    REQUIRE(location_latlon.longitude == Catch::Approx(3.710670));

    // test precomputed conversion (north)
    REQUIRE(GeoLocationLatLon(location_south).latitude == Catch::Approx(-41.280330));
    REQUIRE(GeoLocationLatLon(location_south).longitude == Catch::Approx(174.780011));
}