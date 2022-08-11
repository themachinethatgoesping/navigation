// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolatorlatlon.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("NavigationInterpolatorLatLon should support common functions", TESTTAG)
{
    // setup sensor configuration
    SensorConfiguration sensor_configuration;
    sensor_configuration.set_offsets_depth_source(0, 0, 1);
    sensor_configuration.set_offsets_attitude_source(1, -2, 3);
    sensor_configuration.set_offsets_position_source(10, -10, 5);

    datastructures::PositionalOffsets targetOffsets(1, 2, 3, 0, 0, 0);
    sensor_configuration.add_target("mbes", targetOffsets);

    // // initialize coordinate system with one target
    NavigationInterpolatorLatLon navint(sensor_configuration);

    navint.set_data_depth({ 0, 1, 2, 3 }, { 10, -10, -11, 9 });
    navint.set_data_heave({ 0, 1, 2, 3 }, { -1, -2, 3, 4 });
    navint.set_data_heading({ 0.5, 6 }, { 10, 20 });
    navint.set_data_attitude({ 0, 1, 2, 3 }, { 1, -1, -2, 3 }, { 2, -3, -4, 2 });
    navint.set_data_position({ 0, 1, 2, 3 }, { 10, -10, -11, 9 }, { 1, -1, -2, 3 });

    // copy constructor
    NavigationInterpolatorLatLon navint2(navint);

    // eq operator
    REQUIRE(navint == navint2);
    navint.add_target("sbes", targetOffsets);
    REQUIRE(navint != navint2);
    navint2.add_target("sbes", targetOffsets);
    REQUIRE(navint == navint2);
    navint.sensor_configuration().set_offsets_position_source(11, 20, 30);
    REQUIRE(navint != navint2);

    // string conversion
    std::stringstream ss;
    navint.print(ss);
    REQUIRE(navint.info_string().size() > 0);

    // serialization
    auto buffer  = navint.to_binary();
    auto navint3 = NavigationInterpolatorLatLon::from_binary(buffer);
    REQUIRE(navint == navint3);

    // compute a target position
    datastructures::GeoLocationLatLon expected_position(
        //-10.7631, -1.16473, -7.3232973266, 11.0909090909, 0.7830655476, -6.1148918992);
        -10.7631, -1.16473, -7.3232528, 11.0909091, 0.7822953, -6.11409181148918992);
    auto target_position_mbes = navint.compute_target_position("mbes", 1.1);
    auto target_position_sbes = navint.compute_target_position("sbes", 1.1);

    expected_position.print(std::cerr, 7);
    target_position_mbes.print(std::cerr, 7);
    target_position_sbes.print(std::cerr, 7);
    std::cerr << target_position_mbes.latitude << std::endl;
    std::cerr << target_position_mbes.longitude << std::endl;

    REQUIRE(target_position_mbes == expected_position);
    REQUIRE(target_position_sbes == expected_position);
}