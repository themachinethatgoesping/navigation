# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

""" tests for the SensorConfiguration class
"""

# import time
from pytest import approx

# import numpy as np

import themachinethatgoesping.navigation as nav


class TestNavigationSensorConfiguration:
    """class for grouping (test sections)"""

    def test_sensorconfiguration_should_support_common_functions(self):
        """test common, simple functions"""
        data = nav.datastructures.SensordataLatLon(53, 10, 3, 4, 10, 20, 30)

        # initialize
        scs = nav.SensorConfiguration()

        # register target
        scs.add_target(
            "mbes", nav.datastructures.PositionalOffsets("mbes", -12, 9, 3, 10, 11, 12)
        )

        # add offsets
        scs.set_heading_source("sensor", yaw=9)
        scs.set_depth_source("sensor", 0, 0, 1)
        scs.set_position_source("sensor", 1, 2, 3)
        scs.set_attitude_source("sensor", 10, -10, -30)
        scs.set_waterline_offset(0.5)

        # get target position
        position = scs.compute_target_position("mbes", data)
        position2 = nav.datastructures.GeolocationLatLon(
            52.99993263333143,
            10.000048544339503,
            12.50607681274414,
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
        scs.set_heading_source("sensor", yaw=12)
        assert scs2 != scs

        # binary
        assert scs == nav.SensorConfiguration.from_binary(scs.to_binary())

        # print
        print(scs)
        assert len(scs.info_string()) != 0

        # more
        assert set(scs.get_target_ids()) == set(["mbes", "0"])

        # remove target
        assert set(scs.get_target_ids()) == set(["mbes", "0"])
        assert scs.without_targets().get_target_ids() == ["0"]

        scs.remove_target("mbes")
        assert scs.get_target_ids() == ["0"]
