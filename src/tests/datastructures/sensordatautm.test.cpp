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

#define TESTTAG "[data]"

TEST_CASE("SensordataUTM should support common functions", TESTTAG)
{
    // initialize data
    auto data = SensordataUTM();

    data.northing                = 5652759.000;
    data.easting                 = 549841.192;
    data.utm_zone                = 31;
    data.northern_hemisphere = true;
    data.depth                   = 3;

    data.heading = 10;
    data.heave   = 1;

    data.pitch = 20;
    data.roll  = 30;

    // test copy
    REQUIRE(data == SensordataUTM(data));

    // test binary
    REQUIRE(data == SensordataUTM(data.from_binary(data.to_binary())));

    // test stream
    std::stringstream buffer;
    data.to_stream(buffer);
    REQUIRE(data == SensordataUTM(data.from_stream(buffer)));

    // test print does not crash
    REQUIRE(data.info_string().size() != 0);
}

TEST_CASE("SensordataUTM should support common utm/latlon conversions", TESTTAG)
{
    // initialize data
    auto data = SensordataUTM();

    data.northing                = 5652759.000;
    data.easting                 = 549841.192;
    data.utm_zone                = 31;
    data.northern_hemisphere = true;
    data.depth                   = 3;

    data.heading = 10;
    data.heave   = 1;

    data.pitch = 20;
    data.roll  = 30;

    auto data_south                    = SensordataUTM(data);
    data_south.northing                = 5427745.995;
    data_south.easting                 = 314082.699;
    data_south.utm_zone                = 60;
    data_south.northern_hemisphere = false;

    // test utm/lat lon conversion
    SensordataLatLon data_latlon(data);
    SensordataUTM    data_utm(data_latlon);

    data_latlon.print(std::cerr);
    data.print(std::cerr);
    data_utm.print(std::cerr);
    SensordataUTM::from_sensordata(data_latlon).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(data_latlon == SensordataUTM::to_sensordata(data));
    REQUIRE(data_utm == SensordataUTM::from_sensordata(data_latlon));

    // to/from conversion should reproduce the original zone
    REQUIRE(data == data_utm);
    REQUIRE(data_latlon == SensordataLatLon(data_utm));
    REQUIRE(data_south == SensordataUTM(SensordataLatLon(data_south)));
    REQUIRE(SensordataLatLon(data_south) ==
            SensordataLatLon(SensordataUTM(SensordataLatLon(data_south))));

    // test simple explicit conversion
    REQUIRE(data == SensordataUTM(data_latlon));

    // test precomputed conversion (north)
    REQUIRE(data_latlon.latitude == Catch::Approx(51.024224));
    REQUIRE(data_latlon.longitude == Catch::Approx(3.710670));

    // test precomputed conversion (north)
    REQUIRE(SensordataLatLon(data_south).latitude == Catch::Approx(-41.280330));
    REQUIRE(SensordataLatLon(data_south).longitude == Catch::Approx(174.780011));

    // test info strings
    data_utm.heading = 12;
    data_utm.print(std::cerr);
    REQUIRE(data_utm.info_string().find("heading") != std::string::npos);
}