// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <filesystem>

#include "../themachinethatgoesping/navigation/sensorcoordinatesystem.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::navigation;

#define TESTTAG "[offsets]"

TEST_CASE("sensorcoordinatesystem should support common functions", TESTTAG)
{
    // initialize offsets
    auto scs = SensorCoordinateSystem();

}