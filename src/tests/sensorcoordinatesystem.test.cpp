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
    SensorCoordinateSystem scs;

    // copy constructor
    SensorCoordinateSystem scs2(scs);
}


TEST_CASE("sensorcoordinatesystem should reproduce precomputed rotations", TESTTAG)
{
    // initialize offsets
    SensorCoordinateSystem scs;
    PositionalOffsets targetOffsets(1,2,3,0,0,0);

    scs.set_targetOffsets("MBES",targetOffsets);

    // double x= 1;
    // double y= 2;
    // double depth= 3;
    // double heave= 4;
    // double heading = 45;
    // double yaw = 90;
    // double pitch = 0;
    // double roll = 0;

    SECTION("NO_SENSOR_VALUES")
    {
    REQUIRE(scs.get_targetDepth("MBES") == 3 );
    //REQUIRE(scs.get_targetXY("MBES") == Approx(std::make_tuple<double,double>(1,1) ));
    }
}