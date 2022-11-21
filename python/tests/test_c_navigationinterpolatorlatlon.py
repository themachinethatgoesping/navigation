# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

""" tests for the NavigationInterpolatorLatLon class
"""

# import time
from pytest import approx

# import numpy as np

import themachinethatgoesping.navigation as nav


class TestNavigationNavigationInterpolatorLatLon:
    """class for grouping (test sections)"""

    def test_navigationinterpolatorlatlon_should_support_common_functions(self):
        # initialize sensor configuration
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

        # initialize Interpolator
        navi = nav.NavigationInterpolatorLatLon(scs, "extrapolate")

        # change some offsets
        sc = navi.get_sensor_configuration()
        sc.set_position_source("sensor", 10, 0, 0)
        navi.set_sensor_configuration(sc)

        # add some data
        navi.set_data_position([1, 2, 3, 4], [10, 20, 10, 20], [-10, 1, 2, -4])
        navi.set_data_heave([0, 5], [0, 20])
        navi.set_data_heading([1, 2], [-20, 20])
        navi.set_data_attitude([2, 3], [10, 20], [-20, 1])

        # get target position
        pos = navi("mbes", 1.5)

        assert pos.latitude == approx(17.291495620156894)
        assert pos.longitude == approx(-3.1997763750783226)
        assert pos.z == approx(-1.44404485)
        assert pos.yaw == approx(1.28465417)
        assert pos.pitch == approx(26.16455736)
        assert pos.roll == approx(11.66764810)

        pos = navi("mbes", 0)

        assert pos.latitude == approx(-5.032492747459575)
        assert pos.longitude == approx(-24.087985792652038)
        assert pos.z == approx(-3.76324394)
        assert pos.yaw == approx(293.62666611)
        assert pos.pitch == approx(11.01290459)
        assert pos.roll == approx(-20.44328750)

        # copy
        navi2 = navi.copy()
        assert navi2 == navi
        sc = navi.get_sensor_configuration()
        sc.set_heading_source("sensor", yaw=12)
        navi.set_sensor_configuration(sc)
        assert navi2 != navi

        assert navi == nav.NavigationInterpolatorLatLon.from_binary(navi.to_binary())

        # print
        print(navi)
        assert len(navi.info_string()) != 0
