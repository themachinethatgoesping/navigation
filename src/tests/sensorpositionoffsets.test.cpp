// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/sensorpositionoffsets.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("SensorPositionOffsets should support common functions", TESTTAG)
{
    // initialize offsets
    auto offsets = SensorPositionOffsets();

    offsets.x = 1;
    offsets.y = 2;
    offsets.z = 3;

    offsets.yaw   = 10;
    offsets.pitch = 20;
    offsets.roll  = 30;

    //test copy
    REQUIRE(offsets == SensorPositionOffsets(offsets));

    //test binary
    REQUIRE(offsets == SensorPositionOffsets(offsets.from_binary(offsets.to_binary())));

    //test stream
    std::stringstream buffer;
    offsets.to_stream(buffer);
    REQUIRE(offsets == SensorPositionOffsets(offsets.from_stream(buffer)));

    //test print does not crash
    REQUIRE(offsets.info_string().size() != 0);
}