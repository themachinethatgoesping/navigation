# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

""" tests for the SensorCoordinateSystem class
"""

# import time
from pytest import approx

# import numpy as np

import themachinethatgoesping.navigation as nav


class TestNavigationSensorCoordinateSystem:
    """class for grouping (test sections)"""

    def test_sensorcoordinatesystem_should_support_common_functions(self):
        """test common, simple functions"""
        data = nav.navdata.SensorDataLatLon(53, 10, 3, 4, 10, 11, 20, 30)

        # initialize
        scs = nav.SensorCoordinateSystem()

        # register target
        scs.add_target(
            "mbes", nav.navdata.PositionalOffsets(-12, 9, 3, 10, 11, 12)
        )

        # add offsets
        scs.set_compass_offsets(yaw=9)
        scs.set_depth_sensor_offsets(0, 0, 1)
        scs.set_position_system_offsets(1, 2, 3)
        scs.set_motion_sensor_offsets(10, -10, -30)

        # get target position
        position = scs.compute_target_position("mbes", data)
        position2 = nav.navdata.GeoLocationLatLon(
            52.99993263333143,
            10.000048544339503,
            13.006073137528947,
            17.60506545110071,
            29.188285228706675,
            80.77436580631132,
        )
        assert position.latitude == approx(position2.latitude)
        assert position.longitude == approx(position2.longitude)
        assert position.z == approx(position2.z)
        assert position.yaw == approx(position2.yaw)
        assert position.pitch == approx(position2.pitch)
        assert position.roll == approx(position2.roll)
        assert position == position2

        # copy
        scs2 = scs.copy()
        assert scs2 == scs
        scs.set_compass_offsets(yaw=12)
        assert scs2 != scs

        # binary
        assert scs == nav.SensorCoordinateSystem.from_binary(scs.to_binary())

        # print
        print(scs)
        assert len(scs.info_string()) != 0
