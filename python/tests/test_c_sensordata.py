# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import SensorData

import time
import pytest
import numpy as np


#define class for grouping (test sections)
class Test_navigation_SensorData:
    #define actual tests (must start with "test_"
    #test case 1
    def test_SensorData_should_support_common_functions(self):
        data = SensorData(1,2,3,4,10,11,20,30)
        print(data)

        #copy
        data2 = data.copy()
        assert data == data2
        data2.gps_latitude = 100
        assert data != data2

        #binary
        assert data == SensorData.from_binary(data.to_binary())

        #print
        data2.compass_heading = np.nan
        print(data2)
        assert "valid" in str(data)
        assert "invalid" in str(data2)


