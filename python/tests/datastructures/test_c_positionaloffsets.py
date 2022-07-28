# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import PositionalOffsets

import time
import pytest


#define class for grouping (test sections)
class Test_navigation_PositionalOffsets:
    #define actual tests (must start with "test_"
    #test case 1
    def test_PositionalOffsets_should_support_common_functions(self):
        offsets = PositionalOffsets(1,2,3,10,20,30)
        print(offsets)

        #print
        assert len(str(offsets)) != 0

        #copy
        offsets2 = offsets.copy()
        assert offsets == offsets2
        offsets2.x = 100
        assert offsets != offsets2

        #binary
        assert offsets == PositionalOffsets.from_binary(offsets.to_binary())


