# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation import navtools

import time
import pytest


# define class for grouping (test sections)
class Test_navigation_navtools:
    # define actual tests (must start with "test_"
    # test case 1
    def test_navtools_should_reproduce_precomputed_strings(self):
        assert navtools.latitude_to_string(123.45678, "degrees", 2) == "123.46°N"
        assert navtools.latitude_to_string(123.45678, "minutes", 2) == "123°27.41'N"
        assert navtools.latitude_to_string(123.45678, "seconds", 2) == "123°27'24.41\"N"
        assert (
            navtools.latitude_to_string(-123.45678, "seconds", 3) == "123°27'24.408\"S"
        )

        assert navtools.longitude_to_string(123.45678, "degrees", 2) == "123.46°E"
        assert navtools.longitude_to_string(123.45678, "minutes", 2) == "123°27.41'E"
        assert navtools.longitude_to_string(123.45678, "seconds", 2) == "123°27'24.41\"E"
        assert (
            navtools.longitude_to_string(-123.45678, "seconds", 3) == "123°27'24.408\"W"
        )
