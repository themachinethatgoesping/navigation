# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import SensorPose

# import pytest

# define class for grouping (test sections)


class Test_navigation_SensorPose:
    # define actual tests (must start with "test_"
    # test case 1
    def test_SensorPose_should_support_common_functions(self):
        offsets = SensorPose("sensor", 1, 2, 3, 10, 20, 30)
        print(offsets)

        # print
        assert len(str(offsets)) != 0

        # copy
        offsets2 = offsets.copy()
        assert offsets == offsets2
        offsets2.x = 100
        assert offsets != offsets2

        # binary
        assert offsets == SensorPose.from_binary(offsets.to_binary())
