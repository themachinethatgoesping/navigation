# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import Geolocation

# define class for grouping (test sections)


class Test_navigation_Geolocation:
    # define actual tests (must start with "test_"
    # test case 1
    def test_Geolocation_should_support_common_functions(self):
        location = Geolocation(3, 10, 20, 30)
        print(location)

        # print
        assert len(str(location)) != 0

        # copy
        location2 = location.copy()
        assert location == location2
        location2.z = 100
        assert location != location2

        # binary
        assert location == Geolocation.from_binary(location.to_binary())
