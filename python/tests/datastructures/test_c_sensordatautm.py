# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import SensorDataLatLon, SensorDataUTM, SensorData, SensorDataLocal

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
        data_base = SensorDataLocal(
            5427745.995, 
            314082.699, 
            3, 
            4,
            10,
            11, 
            20, 
            30)
        data_base_base = SensorData(
            3, 
            4,
            10,
            11, 
            20, 
            30)
        print(data)

        #compare to base
        assert data_base == SensorDataLocal(data)
        assert data_base_base == SensorData(data)
        assert data == SensorDataUTM(data_base,60,False)
        assert data == SensorDataUTM(data_base_base,5427745.995, 314082.699, 60,False)

        # print
        assert len(str(data)) != 0

        # copy
        data2 = data.copy()
        assert data == data2
        data2.northing = 100
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

        #create a new SensorDataLatLon object by explicit conversion
        data_latlon = SensorDataLatLon(data)

        #SensorDataUTM is implicitly convertible and therefore also comparable to SensorDataLatLon
        assert data == data
        assert data == data_latlon
        assert SensorDataUTM.from_sensordata(data_latlon) == data_latlon

        assert data_latlon.gps_latitude == approx(-41.280330)
        assert data_latlon.gps_longitude == approx(174.780011)

