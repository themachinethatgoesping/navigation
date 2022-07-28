# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

""" tests for the SensorData class
"""

# import time
# import pytest
import numpy as np

from themachinethatgoesping.navigation.navdata import SensorData

class TestNavigationSensorData:
    """class for grouping (test sections)"""

    def test_sensordata_should_support_common_functions(self):
        """test common, simple functions
        """
        data = SensorData(3, 4, 10, 11, 20, 30)
        print(data)

        # copy
        data2 = data.copy()
        assert data == data2
        data2.gps_z = 100
        assert data != data2

        # binary
        assert data == SensorData.from_binary(data.to_binary())

        # print
        data2.compass_heading = np.nan
        print(data2)
        assert "valid" in str(data)
        assert "invalid" in str(data2)
