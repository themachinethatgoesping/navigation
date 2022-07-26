// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/navdata.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::navdata;

#define TESTTAG "[data]"

TEST_CASE("SensorDataLocal should support common functions", TESTTAG)
{
    // initialize data
    auto data = SensorDataLocal();

    data.gps_northing = 5652759.000;
    data.gps_easting  = 549841.192;
    data.gps_z        = 3;

    data.compass_heading = 10;
    data.heave_heave = 1;

    data.imu_yaw   = 10;
    data.imu_pitch = 20;
    data.imu_roll  = 30;

    // test copy
    REQUIRE(data == SensorDataLocal(data));

    // test binary
    REQUIRE(data == SensorDataLocal(data.from_binary(data.to_binary())));

    // test stream
    std::stringstream buffer;
    data.to_stream(buffer);
    REQUIRE(data == SensorDataLocal(data.from_stream(buffer)));

    // test print does not crash
    REQUIRE(data.info_string().size() != 0);
}

TEST_CASE("SensorDataLocal should support common utm/local conversions", TESTTAG)
{
    // initialize data
    auto data = SensorDataLocal();

    data.gps_northing        = 5652759.000;
    data.gps_easting         = 549841.192;
    data.gps_z               = 3;
    int  zone                = 31;
    bool northern_hemisphere = true;

    data.compass_heading = 10;
    data.heave_heave = 1;
    
    data.imu_yaw   = 10;
    data.imu_pitch = 20;
    data.imu_roll  = 30;

    // test utm/lat lon conversion
    SensorDataUTM data_utm(data, zone, northern_hemisphere);

    data.print(std::cerr);
    data_utm.print(std::cerr);

    // test implicit conversion
    REQUIRE(data == data_utm); // note this only works in one direction!
}