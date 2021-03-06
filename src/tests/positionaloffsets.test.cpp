// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/navdata.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation::navdata;

#define TESTTAG "[offsets]"

TEST_CASE("PositionalOffsets should support common functions", TESTTAG)
{
    // initialize offsets
    auto offsets = PositionalOffsets();

    offsets.x = 1;
    offsets.y = 2;
    offsets.z = 3;

    offsets.yaw   = 10;
    offsets.pitch = 20;
    offsets.roll  = 30;

    //test copy
    REQUIRE(offsets == PositionalOffsets(offsets));

    //test binary
    REQUIRE(offsets == PositionalOffsets(offsets.from_binary(offsets.to_binary())));

    //test stream
    std::stringstream buffer;
    offsets.to_stream(buffer);
    REQUIRE(offsets == PositionalOffsets(offsets.from_stream(buffer)));

    //test print does not crash
    REQUIRE(offsets.info_string().size() != 0);
}