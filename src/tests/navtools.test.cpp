// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navtools.hpp"

using namespace std;
using namespace themachinethatgoesping::navigation;
using Catch::Approx;

#define TESTTAG "[navtools]"

TEST_CASE("Test distance calculation", TESTTAG)
{
    // Test case 1: Distance between two points on the same latitude
    double lat1              = 51.5074; // London
    double lon1              = -0.1278;
    double lat2              = 48.8566; // Paris
    double lon2              = 2.3522;
    double expectedDistance1 = 343923.1200909893; // in meters
    double distance1         = navtools::compute_latlon_distance_m(lat1, lon1, lat2, lon2);
    REQUIRE(distance1 == Approx(expectedDistance1));

    // Test case 2: Distance between two points on different latitudes
    double lat3              = 37.7749; // San Francisco
    double lon3              = -122.4194;
    double lat4              = 34.0522; // Los Angeles
    double lon4              = -118.2437;
    double expectedDistance2 = 559042.3365035714; // in meters
    double distance2         = navtools::compute_latlon_distance_m(lat3, lon3, lat4, lon4);
    REQUIRE(distance2 == Approx(expectedDistance2));

    // Test case 3: compute distances
    double              expectedDistance3 = 8976175.5461306088; // in meters
    std::vector<double> latitudes         = { lat1, lat2, lat3, lat4 };
    std::vector<double> longitudes        = { lon1, lon2, lon3, lon4 };
    auto                distances = navtools::compute_latlon_distances_m(latitudes, longitudes);
    CHECK(distances.size() == 3);
    CHECK(distances[0] == Approx(expectedDistance1));
    CHECK(distances[1] == Approx(expectedDistance3));
    CHECK(distances[2] == Approx(expectedDistance2));

    // Test case 4: cumulative_latlon_distances_m
    auto cumulative_latlon_distances_m =
        navtools::cumulative_latlon_distances_m(latitudes, longitudes);
    CHECK(cumulative_latlon_distances_m.size() == 4);
    CHECK(cumulative_latlon_distances_m[0] == Approx(0));
    CHECK(cumulative_latlon_distances_m[1] == Approx(expectedDistance1));
    CHECK(cumulative_latlon_distances_m[2] == Approx(expectedDistance1 + expectedDistance3));
    CHECK(cumulative_latlon_distances_m[3] ==
          Approx(expectedDistance1 + expectedDistance3 + expectedDistance2));

    // Test case 4 test above with datastructures::GeolocationLatLon
    std::vector<datastructures::GeolocationLatLon> loc_latlon;
    std::vector<datastructures::SensordataLatLon>  sens_latlon;
    for (size_t i = 0; i < latitudes.size(); ++i)
    {
        loc_latlon.push_back({ {}, latitudes[i], longitudes[i] });
        sens_latlon.push_back({ {}, latitudes[i], longitudes[i] });
    }

    // individual distances
    CHECK(navtools::compute_latlon_distance_m(loc_latlon[0], loc_latlon[1]) == Approx(distance1));
    CHECK(navtools::compute_latlon_distance_m(sens_latlon[0], sens_latlon[1]) == Approx(distance1));

    // vector distances
    auto distances_loc_latlon  = navtools::compute_latlon_distances_m(loc_latlon);
    auto distances_sens_latlon = navtools::compute_latlon_distances_m(sens_latlon);

    CHECK(distances_loc_latlon.size() == distances.size());
    CHECK(distances_sens_latlon.size() == distances.size());

    for (size_t i = 0; i < distances_loc_latlon.size(); ++i)
        CHECK(distances_loc_latlon[i] == Approx(distances[i]));

    for (size_t i = 0; i < distances_sens_latlon.size(); ++i)
        CHECK(distances_sens_latlon[i] == Approx(distances[i]));

    // cumulative distances
    auto cumulative_latlon_distances_loc_latlon =
        navtools::cumulative_latlon_distances_m(loc_latlon);
    auto cumulative_latlon_distances_sens_latlon =
        navtools::cumulative_latlon_distances_m(sens_latlon);
    CHECK(cumulative_latlon_distances_loc_latlon.size() == cumulative_latlon_distances_m.size());
    CHECK(cumulative_latlon_distances_sens_latlon.size() == cumulative_latlon_distances_m.size());

    for (size_t i = 0; i < cumulative_latlon_distances_loc_latlon.size(); ++i)
        CHECK(cumulative_latlon_distances_loc_latlon[i] ==
              Approx(cumulative_latlon_distances_m[i]));

    for (size_t i = 0; i < cumulative_latlon_distances_sens_latlon.size(); ++i)
        CHECK(cumulative_latlon_distances_sens_latlon[i] ==
              Approx(cumulative_latlon_distances_m[i]));
}
