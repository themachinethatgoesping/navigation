// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <filesystem>

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
    double distance1         = navtools::compute_distance(lat1, lon1, lat2, lon2);
    REQUIRE(distance1 == Approx(expectedDistance1));

    // Test case 2: Distance between two points on different latitudes
    double lat3              = 37.7749; // San Francisco
    double lon3              = -122.4194;
    double lat4              = 34.0522; // Los Angeles
    double lon4              = -118.2437;
    double expectedDistance2 = 559042.3365035714; // in meters
    double distance2         = navtools::compute_distance(lat3, lon3, lat4, lon4);
    REQUIRE(distance2 == Approx(expectedDistance2));

    // Test case 3: compute distances
    double              expectedDistance3 = 8976175.5461306088;  // in meters
    std::vector<double> latitudes         = { lat1, lat2, lat3, lat4 };
    std::vector<double> longitudes        = { lon1, lon2, lon3, lon4 };
    auto                distances         = navtools::compute_distances(latitudes, longitudes);
    CHECK(distances.size() == 3);
    CHECK(distances[0] == Approx(expectedDistance1));
    CHECK(distances[1] == Approx(expectedDistance3));
    CHECK(distances[2] == Approx(expectedDistance2));

    // Test case 4: cumulative_distances
    auto   cumulative_distances = navtools::cumulative_distances(latitudes, longitudes);
    CHECK(cumulative_distances.size() == 4);
    CHECK(cumulative_distances[0] == Approx(0));
    CHECK(cumulative_distances[1] == Approx(expectedDistance1));
    CHECK(cumulative_distances[2] == Approx(expectedDistance1 + expectedDistance3));
    CHECK(cumulative_distances[3] ==
          Approx(expectedDistance1 + expectedDistance3 + expectedDistance2));
}
