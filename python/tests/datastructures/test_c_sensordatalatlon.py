# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import SensorDataLatLon, SensorData

import time
import pytest
import numpy as np


#define class for grouping (test sections)
class Test_navigation_SensorData:
    #define actual tests (must start with "test_"
    #test case 1
    def test_SensorDataLatLon_should_support_common_functions(self):
        data = SensorDataLatLon(1,2,3,4,10,11,20,30)
        data_base = SensorData(3,4,10,11,20,30)
        print(data)

        #compare to base
        assert data_base == SensorData(data)
        assert data == SensorDataLatLon(data_base,1,2)

        #copy
        data2 = data.copy()
        assert data == data2
        data2.gps_latitude = 100
        assert data != data2

        #binary
        assert data == SensorDataLatLon.from_binary(data.to_binary())

        #print
        data2.heading_source = np.nan
        print(data2)
        assert "valid" in str(data)
        assert "invalid" in str(data2)


