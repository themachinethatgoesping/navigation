// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::datastructures;

#define TESTTAG "[data]"

TEST_CASE("SensorDataUTM should support common functions", TESTTAG)
{
    // initialize data
    auto data = SensorDataUTM();

    data.gps_northing            = 5652759.000;
    data.gps_easting             = 549841.192;
    data.gps_zone                = 31;
    data.gps_northern_hemisphere = true;
    data.gps_z                   = 3;

    data.compass_heading = 10;
    data.heave_heave = 1;

    data.imu_yaw   = 10;
    data.imu_pitch = 20;
    data.imu_roll  = 30;

    // test copy
    REQUIRE(data == SensorDataUTM(data));

    // test binary
    REQUIRE(data == SensorDataUTM(data.from_binary(data.to_binary())));

    // test stream
    std::stringstream buffer;
    data.to_stream(buffer);
    REQUIRE(data == SensorDataUTM(data.from_stream(buffer)));

    // test print does not crash
    REQUIRE(data.info_string().size() != 0);
}

TEST_CASE("SensorDataUTM should support common utm/latlon conversions", TESTTAG)
{
    // initialize data
    auto data = SensorDataUTM();

    data.gps_northing            = 5652759.000;
    data.gps_easting             = 549841.192;
    data.gps_zone                = 31;
    data.gps_northern_hemisphere = true;
    data.gps_z                   = 3;

    data.compass_heading = 10;
    data.heave_heave = 1;
    
    data.imu_yaw   = 10;
    data.imu_pitch = 20;
    data.imu_roll  = 30;

    auto data_south                = SensorDataUTM(data);
    data_south.gps_northing            = 5427745.995;
    data_south.gps_easting             = 314082.699;
    data_south.gps_zone                = 60;
    data_south.gps_northern_hemisphere = false;

    // test utm/lat lon conversion
    SensorDataLatLon    data_latlon(data);
    SensorDataUTM data_utm(data_latlon);

    data_latlon.print(std::cerr);
    data.print(std::cerr);
    data_utm.print(std::cerr);
    SensorDataUTM::from_sensordata(data_latlon).print(std::cerr);

    // to_ and from_ functions should produce the same results as initialization
    REQUIRE(data_latlon == SensorDataUTM::to_sensordata(data));
    REQUIRE(data_utm == SensorDataUTM::from_sensordata(data_latlon));

    // to/from conversion should reproduce the original zone
    REQUIRE(data == data_utm);
    REQUIRE(data_latlon == SensorDataLatLon(data_utm));
    REQUIRE(data_south == SensorDataUTM(SensorDataLatLon(data_south)));
    REQUIRE(SensorDataLatLon(data_south) ==
            SensorDataLatLon(SensorDataUTM(SensorDataLatLon(data_south))));

    // test the same as above but using implicit conversion
    REQUIRE(data == data_latlon);
    REQUIRE(data_south == SensorDataLatLon(data_south));

    // test precomputed conversion (north)
    REQUIRE(data_latlon.gps_latitude == Approx(51.024224));
    REQUIRE(data_latlon.gps_longitude == Approx(3.710670));

    // test precomputed conversion (north)
    REQUIRE(SensorDataLatLon(data_south).gps_latitude == Approx(-41.280330));
    REQUIRE(SensorDataLatLon(data_south).gps_longitude == Approx(174.780011));

    // test info strings
    data_utm.compass_heading = NAN;
    data_utm.print(std::cerr);
    REQUIRE(data_utm.info_string().find("invalid") != std::string::npos);

    data_utm.compass_heading = 12;
    data_utm.print(std::cerr);
    REQUIRE(data_utm.info_string().find("valid") != std::string::npos);
}