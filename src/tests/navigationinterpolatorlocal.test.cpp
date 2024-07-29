// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolatorlocal.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("NavigationInterpolatorLocal should support common functions", TESTTAG)
{
    // setup sensor configuration
    SensorConfiguration sensor_configuration;
    sensor_configuration.set_depth_source("gps", 0, 0, 1);
    sensor_configuration.set_attitude_source("gps", 1, -2, 3);
    sensor_configuration.set_position_source("gps", 10, -10, 5);

    datastructures::PositionalOffsets targetOffsets("mbes", 1, 2, 3, 0, 0, 0);
    sensor_configuration.add_target("mbes", targetOffsets);

    // // initialize coordinate system with one target
    NavigationInterpolatorLocal navint(sensor_configuration);

    REQUIRE(navint.valid() == false); // no position data was added yet

    navint.set_data_depth({ 0, 1, 2, 3 }, { 10, -10, -11, 9 });
    navint.set_data_heave({ 0, 1, 2, 3 }, { -1, -2, 3, 4 });
    navint.set_data_heading({ 0.5, 6 }, { 10, 20 });
    navint.set_data_attitude({ 0, 1, 2, 3 }, { 1, -1, -2, 3 }, { 2, -3, -4, 2 });
    navint.set_data_position({ 0, 1, 2, 3 }, { 10, -10, -11, 9 }, { 1, -1, -2, 3 });

    // copy constructor
    NavigationInterpolatorLocal navint2(navint);

    REQUIRE(navint.valid()); // position data was added
    REQUIRE(navint2.valid()); // position data was added

    // eq operator
    REQUIRE(navint == navint2);
    navint.add_target("sbes", targetOffsets);
    REQUIRE(navint != navint2);
    navint2.add_target("sbes", targetOffsets);
    REQUIRE(navint == navint2);
    auto sc = navint.get_sensor_configuration();
    sc.set_position_source("gps", 11, 20, 30);
    navint.set_sensor_configuration(sc);
    REQUIRE(navint != navint2);

    // string conversion
    std::stringstream ss;
    navint.print(ss);
    REQUIRE(navint.info_string().size() > 0);

    // serialization
    auto buffer  = navint.to_binary();
    auto navint3 = NavigationInterpolatorLocal::from_binary(buffer);
    REQUIRE(navint == navint3);

    // compute a target position
    datastructures::GeolocationLocal expected_position(
        -16.9132381, -23.5388528, -6.6602486, 11.0909091, 0.7822953, -6.1140918);

    auto target_position_mbes = navint.compute_target_position("mbes", 1.1);
    auto target_position_sbes = navint.compute_target_position("sbes", 1.1);

    INFO(expected_position.info_string(7));
    INFO(target_position_mbes.info_string(7));
    INFO(target_position_sbes.info_string(7));

    REQUIRE(target_position_mbes == expected_position);
    REQUIRE(target_position_sbes == expected_position);
}

TEST_CASE("navigationinterpolatorlocal merging operations", TESTTAG)
{

    // setup sensor configuration
    SensorConfiguration sensor_configuration;
    sensor_configuration.set_depth_source("gps", 0, 0, 1);
    sensor_configuration.set_attitude_source("gps", 1, -2, 3);
    sensor_configuration.set_position_source("gps", 10, -10, 5);

    datastructures::PositionalOffsets targetOffsets("mbes", 1, 2, 3, 0, 0, 0);
    sensor_configuration.add_target("mbes", targetOffsets);

    // // initialize coordinate system with one target
    NavigationInterpolatorLocal navint(sensor_configuration);

    navint.set_data_depth({ 0, 1, 2, 3 }, { 10, -10, -11, 9 });
    navint.set_data_heave({ 0, 1, 2, 3 }, { -1, -2, 3, 4 });
    navint.set_data_heading({ 0.5, 6 }, { 10, 20 });
    navint.set_data_attitude({ 0, 1, 2, 3 }, { 1, -1, -2, 3 }, { 2, -3, -4, 2 });
    navint.set_data_position({ 0, 1, 2, 3 }, { 10, -10, -11, 9 }, { 1, -1, -2, 3 });

    SECTION("Merge interpolators")
    {
        auto naving2 = navint;

        // cannot merge with itselve, due to duplicate timestamps
        REQUIRE_THROWS_AS(navint.merge(naving2), std::domain_error);

        // merge with empty interpolator
        auto navint3 = navint;
        navint3.merge(NavigationInterpolatorLocal(sensor_configuration));
        REQUIRE(navint == navint3);

        // test merging
        naving2.set_data_depth({ -1, 1.5, 4 }, { 1, 2, 3 });
        naving2.set_data_heave({ -1, 1.5, 4 }, { 1, 2, 3 });
        naving2.set_data_heading({ -1, 1.5, 4 }, { 1, 2, 3 });
        naving2.set_data_attitude({ 0.5, 2.2, 3.2 }, { -1, -2, 3 }, { -3, -4, 2 });
        naving2.set_data_position({ 1.5, 1.6, 2.9 }, { -10, -11, 9 }, { -1, -2, 3 });

        navint3 = navint;
        navint3.merge(naving2);

        REQUIRE(navint3.interpolator_depth().get_data_X() ==
                vector<double>({ -1, 0, 1, 1.5, 2, 3, 4 }));
        REQUIRE(navint3.interpolator_depth().get_data_Y() ==
                vector<float>({ 1, 10, -10, 2, -11, 9, 3 }));
        REQUIRE(navint3.interpolator_heave().get_data_X() ==
                vector<double>({ -1, 0, 1, 1.5, 2, 3, 4 }));
        REQUIRE(navint3.interpolator_heave().get_data_Y() ==
                vector<double>({ 1, -1, -2, 2, 3, 4, 3 }));

        REQUIRE(navint3.interpolator_heading().get_data_X() ==
                vector<double>({ -1, 0.5, 1.5, 4, 6 }));
        REQUIRE(navint3.interpolator_attitude().get_data_X() ==
                vector<double>({ 0, 0.5, 1, 2, 2.2, 3, 3.2 }));

        REQUIRE(navint3.interpolator_easting().get_data_X() ==
                vector<double>({ 0, 1, 1.5, 1.6, 2, 2.9, 3 }));
        REQUIRE(navint3.interpolator_easting().get_data_Y() ==
                vector<double>({ 1, -1, -1, -2, -2, 3, 3 }));
        REQUIRE(navint3.interpolator_northing().get_data_X() ==
                vector<double>({ 0, 1, 1.5, 1.6, 2, 2.9, 3 }));
        REQUIRE(navint3.interpolator_northing().get_data_Y() ==
                vector<double>({ 10, -10, -10, -11, -11, 9, 9 }));

        // test merging with different sensor configuration (should fail)
        navint3 = navint;
        auto sc = navint3.get_sensor_configuration();
        sc.set_attitude_source("imu", 1, -2, 3);
        navint3.set_sensor_configuration(sc);

        REQUIRE_THROWS_AS(navint3.merge(naving2), std::runtime_error);
    }
}