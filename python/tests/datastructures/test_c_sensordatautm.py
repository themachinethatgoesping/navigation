# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import (
    SensordataLatLon,
    SensordataUTM,
    Sensordata,
    SensordataLocal,
)

from pytest import approx


# define class for grouping (test sections)
class Test_navigation_SensordataUTM:
    # define actual tests (must start with "test_"
    # test case 1
    def test_SensordataUTM_should_support_common_functions(self):
        data = SensordataUTM(5427745.995, 314082.699, 60, False, 3, 4, 10, 20, 30)
        data_base = SensordataLocal(5427745.995, 314082.699, 3, 4, 10, 20, 30)
        data_base_base = Sensordata(3, 4, 10, 20, 30)
        print(data)

        # compare to base
        assert data_base == SensordataLocal(data)
        assert data_base_base == Sensordata(data)
        assert data == SensordataUTM(data_base, 60, False)
        assert data == SensordataUTM(data_base_base, 5427745.995, 314082.699, 60, False)

        # print
        assert len(str(data)) != 0

        # copy
        data2 = data.copy()
        assert data == data2
        data2.northing = 100
        assert data != data2

        # binary
        assert data == SensordataUTM.from_binary(data.to_binary())

    def test_SensordataUTM_should_support_latlon_conversions(self):
        data = SensordataUTM(5427745.995, 314082.699, 60, False, 3, 4, 10, 20, 30)
        print(data)

        # create a new SensordataLatLon object by explicit conversion
        data_latlon = SensordataLatLon(data)

        # SensordataUTM is explicitly convertible and therefore also comparable to SensordataLatLon
        assert data == data  # pylint: disable=comparison-with-itself
        assert data == SensordataUTM(data_latlon)
        assert SensordataUTM.from_sensordata(data_latlon) == SensordataUTM(data_latlon)

        assert data_latlon.latitude == approx(-41.280330)
        assert data_latlon.longitude == approx(174.780011)
