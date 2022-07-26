// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/navdata.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::navdata;

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
    GeoLocation    location_latlon(location);
    GeoLocationUTM location_utm(location_latlon);

    location_latlon.print(std::cerr);
    location.print(std::cerr);
    location_utm.print(std::cerr);
    GeoLocationUTM::from_geolocation(location_latlon).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(location_latlon == GeoLocationUTM::to_geolocation(location));
    REQUIRE(location_utm == GeoLocationUTM::from_geolocation(location_latlon));

    // to/from conversion should reproduce the original zone
    REQUIRE(location == location_utm);
    REQUIRE(location_latlon == GeoLocation(location_utm));
    REQUIRE(location_south == GeoLocationUTM(GeoLocation(location_south)));
    REQUIRE(GeoLocation(location_south) ==
            GeoLocation(GeoLocationUTM(GeoLocation(location_south))));

    // test the same as above but using implicit conversion
    REQUIRE(location == location_latlon);
    REQUIRE(location_south == GeoLocation(location_south));

    // test precomputed conversion (north)
    REQUIRE(location_latlon.latitude == Approx(51.024224));
    REQUIRE(location_latlon.longitude == Approx(3.710670));

    // test precomputed conversion (north)
    REQUIRE(GeoLocation(location_south).latitude == Approx(-41.280330));
    REQUIRE(GeoLocation(location_south).longitude == Approx(174.780011));

}