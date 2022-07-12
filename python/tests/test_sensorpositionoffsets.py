# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation import SensorPositionOffsets

import time
import pytest


#define class for grouping (test sections)
class Test_navigation_SensorPositionOffsets:
    #define actual tests (must start with "test_"
    #test case 1
    def test_SensorPositionOffsets_should_support_common_functions(self):
        offsets = SensorPositionOffsets(1,2,3,10,20,30)
        print(offsets)

        #print
        assert len(str(offsets)) != 0

        #copy
        offsets2 = offsets.copy()
        assert offsets == offsets2
        offsets2.x = 100
        assert offsets != offsets2

        #binary
        assert offsets == SensorPositionOffsets.from_binary(offsets.to_binary())


