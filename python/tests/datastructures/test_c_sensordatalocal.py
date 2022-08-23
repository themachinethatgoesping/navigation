# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import (
    SensorDataLocal,
    SensorDataUTM,
    SensorData,
)

from pytest import raises  # , approx


# define class for grouping (test sections)
class Test_navigation_SensorDataLocal:
    # define actual tests (must start with "test_"
    # test case 1
    def test_SensorDataLocal_should_support_common_functions(self):
        data = SensorDataLocal(5427745.995, 314082.699, 3, 4, 10, 20, 30)
        data_base = SensorData(3, 4, 10, 20, 30)
        print(data)

        # compare to base
        assert data_base == SensorData(data)
        assert data == SensorDataLocal(data_base, 5427745.995, 314082.699)

        # print
        assert len(str(data)) != 0

        # copy
        data2 = data.copy()
        assert data == data2
        data2.northing = 100
        assert data != data2

        # binary
        assert data == SensorDataLocal.from_binary(data.to_binary())

    def test_SensorDataLocal_should_support_utm_conversions(self):
        data = SensorDataLocal(5427745.995, 314082.699, 3, 4, 10, 20, 30)

        zone = 60
        northern_hemisphere = False

        # create a new SensorData object by explicit conversion
        data_utm = SensorDataUTM(
            data, utm_zone=zone, utm_northern_hemisphere=northern_hemisphere
        )

        # SensorDataLocal is implicitly convertible and therefore also comparable to SensorData
        print(data)
        print(data_utm)
        print(SensorDataLocal(data_utm))
        assert data == SensorDataLocal(data_utm)

        # this should work, but fails since data_utm is declared as a derived class from data_local
        with raises(TypeError):
            data == data_utm  # pylint: disable=pointless-statement

        # this does not work because local coordinates are not comparable to utm coordinates unless the zone and hemisphere are known
        with raises(TypeError):
            data_utm == data  # pylint: disable=pointless-statement
