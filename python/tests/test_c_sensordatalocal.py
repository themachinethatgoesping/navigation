# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import SensorDataLocal, SensorDataUTM

import time
from pytest import approx, raises


# define class for grouping (test sections)
class Test_navigation_SensorDataLocal:
    # define actual tests (must start with "test_"
    # test case 1
    def test_SensorDataLocal_should_support_common_functions(self):
        data = SensorDataLocal(5427745.995, 314082.699, 3, 4, 10, 11, 20, 30)
        print(data)

        # print
        assert len(str(data)) != 0

        # copy
        data2 = data.copy()
        assert data == data2
        data2.gps_northing = 100
        assert data != data2

        # binary
        assert data == SensorDataLocal.from_binary(data.to_binary())

    def test_SensorDataLocal_should_support_utm_conversions(self):
        data = SensorDataLocal(5427745.995, 314082.699, 3, 4, 10, 11, 20, 30)
        print(data)

        zone = 60
        northern_hemisphere = False

        # create a new SensorData object by explicit conversion
        data_utm = SensorDataUTM(
            data, gps_zone=zone, gps_northern_hemisphere=northern_hemisphere
        )

        # SensorDataLocal is implicitly convertible and therefore also comparable to SensorData
        assert data == data_utm

        # this does not work because local coordinates are not comparable to utm coordinates unless the zone and hemisphere are known
        with raises(TypeError):
            data_utm == data

        assert SensorDataLocal.from_sensordatautm(data_utm) == data
        assert data_utm == (
            SensorDataLocal.to_sensordatautm(
                data, gps_zone=zone, gps_northern_hemisphere=northern_hemisphere
            )
        )

        # check conversion with offsets
        offset_northing = 100
        offset_easting = -100
        data_utm2 = SensorDataUTM(
            data,
            gps_zone=zone,
            gps_northern_hemisphere=northern_hemisphere,
            offset_northing=offset_northing,
            offset_easting=offset_easting,
        )

        assert data_utm2 != data_utm
        assert data_utm2.gps_northing == approx(data_utm.gps_northing + offset_northing)
        assert data_utm2.gps_easting == approx(data_utm.gps_easting + offset_easting)

        data2 = SensorDataLocal.from_sensordatautm(data_utm2)
        assert data2 == data_utm2

        data3 = SensorDataLocal(
            data_utm2,
            offset_northing=offset_northing,
            offset_easting=offset_easting,
        )

        assert data3 == data
