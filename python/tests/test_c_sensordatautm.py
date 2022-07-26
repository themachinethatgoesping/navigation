# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.navdata import SensorData, SensorDataUTM

import time
from pytest import approx


# define class for grouping (test sections)
class Test_navigation_SensorDataUTM:
    # define actual tests (must start with "test_"
    # test case 1
    def test_SensorDataUTM_should_support_common_functions(self):
        data = SensorDataUTM(
            5427745.995, 
            314082.699, 
            60, 
            False, 
            3, 
            4,
            10,
            11, 
            20, 
            30)
        print(data)

        # print
        assert len(str(data)) != 0

        # copy
        data2 = data.copy()
        assert data == data2
        data2.gps_northing = 100
        assert data != data2

        # binary
        assert data == SensorDataUTM.from_binary(data.to_binary())

    
    def test_SensorDataUTM_should_support_latlon_conversions(self):
        data = SensorDataUTM(
            5427745.995, 
            314082.699, 
            60, 
            False, 
            3, 
            4,
            10,
            11, 
            20, 
            30)
        print(data)

        #create a new SensorData object by explicit conversion
        data_latlon = SensorData(data)

        #SensorDataUTM is implicitly convertible and therefore also comparable to SensorData
        assert data == data_latlon
        assert SensorDataUTM.from_sensordata(data_latlon) == data_latlon

        assert data_latlon.gps_latitude == approx(-41.280330)
        assert data_latlon.gps_longitude == approx(174.780011)
