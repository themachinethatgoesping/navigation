// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/datastructures.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::datastructures;

#define TESTTAG "[offsets]"

TEST_CASE("SensorPose should support common functions", TESTTAG)
{
    // initialize offsets
    auto offsets = SensorPose();

    offsets.name = "test";

    offsets.x = 1;
    offsets.y = 2;
    offsets.z = 3;

    offsets.set_yaw(10);
    offsets.set_pitch(20);
    offsets.set_roll(30);

    // test copy
    REQUIRE(offsets == SensorPose(offsets));

    // test binary
    REQUIRE(offsets == SensorPose(offsets.from_binary(offsets.to_binary())));

    // test stream
    std::stringstream buffer;
    offsets.to_stream(buffer);
    REQUIRE(offsets == SensorPose(offsets.from_stream(buffer)));

    // test print does not crash
    REQUIRE(offsets.info_string().size() != 0);
}