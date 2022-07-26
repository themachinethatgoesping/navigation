# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.navdata import GeoLocationLocal, GeoLocationUTM, GeoLocationLatLon

import time
from pytest import approx, raises


# define class for grouping (test sections)
class Test_navigation_GeoLocationLocal:
    # define actual tests (must start with "test_"
    # test case 1
    def test_GeoLocationLocal_should_support_common_functions(self):
        location = GeoLocationLocal(5427745.995, 314082.699, 3, 10, 20, 30)
        print(location)

        # print
        assert len(str(location)) != 0

        # copy
        location2 = location.copy()
        assert location == location2
        location2.northing = 100
        assert location != location2

        # binary
        assert location == GeoLocationLocal.from_binary(location.to_binary())

    def test_GeoLocationLocal_should_support_utm_conversions(self):
        location = GeoLocationLocal(5427745.995, 314082.699, 3, 10, 20, 30)
        print(location)

        zone = 60
        northern_hemisphere = False

        # create a new GeoLocation object by explicit conversion
        location_utm = GeoLocationUTM(
            location, zone=zone, northern_hemisphere=northern_hemisphere
        )

        # GeoLocationLocal is implicitly convertible and therefore also comparable to GeoLocation UTM
        assert location == GeoLocationLocal(location_utm)

        # this does not work because local coordinates are not comparable to utm coordinates unless the zone and hemisphere are known
        with raises(TypeError):
            location_utm == location

        assert GeoLocationLocal(location_utm) == location
        assert location_utm == (
            GeoLocationUTM(
                location, zone=zone, northern_hemisphere=northern_hemisphere
            )
        )

