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

TEST_CASE("SensordataLocal should support common functions", TESTTAG)
{
    // initialize data
    auto data = SensordataLocal();

    data.northing = 5652759.000;
    data.easting  = 549841.192;
    data.depth    = 3;

    data.heading = 10;
    data.heave   = 1;

    data.pitch = 20;
    data.roll  = 30;

    // test copy
    REQUIRE(data == SensordataLocal(data));

    // test binary
    REQUIRE(data == SensordataLocal(data.from_binary(data.to_binary())));

    // test stream
    std::stringstream buffer;
    data.to_stream(buffer);
    REQUIRE(data == SensordataLocal(data.from_stream(buffer)));

    // test print does not crash
    REQUIRE(data.info_string().size() != 0);
}

TEST_CASE("SensordataLocal should support common utm/local conversions", TESTTAG)
{
    // initialize data
    auto data = SensordataLocal();

    data.northing            = 5652759.000;
    data.easting             = 549841.192;
    data.depth               = 3;
    int  zone                = 31;
    bool northern_hemisphere = true;

    data.heading = 10;
    data.heave   = 1;

    data.pitch = 20;
    data.roll  = 30;

    // test utm/lat lon conversion
    SensordataUTM data_utm(data, zone, northern_hemisphere);

    data.print(std::cerr);
    data_utm.print(std::cerr);

    // test implicit conversion
    REQUIRE(data == data_utm); // note this only works in one direction!
}