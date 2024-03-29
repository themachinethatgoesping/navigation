# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.datastructures import (
    GeolocationLocal,
    GeolocationUTM,
    # GeolocationLatLon,
)

from pytest import raises  # , approx


# define class for grouping (test sections)
class Test_navigation_GeolocationLocal:
    # define actual tests (must start with "test_"
    # test case 1
    def test_GeolocationLocal_should_support_common_functions(self):
        location = GeolocationLocal(5427745.995, 314082.699, 3, 10, 20, 30)
        print(location)

        # print
        assert len(str(location)) != 0

        # copy
        location2 = location.copy()
        assert location == location2
        location2.northing = 100
        assert location != location2

        # binary
        assert location == GeolocationLocal.from_binary(location.to_binary())

    def test_GeolocationLocal_should_support_utm_conversions(self):
        location = GeolocationLocal(5427745.995, 314082.699, 3, 10, 20, 30)
        print(location)

        utm_zone = 60
        northern_hemisphere = False

        # create a new Geolocation object by explicit conversion
        location_utm = GeolocationUTM(
            location, utm_zone=utm_zone, northern_hemisphere=northern_hemisphere
        )

        # GeolocationLocal is implicitly convertible and therefore also comparable to Geolocation UTM
        assert location == GeolocationLocal(location_utm)

        # this does not work because local coordinates are not comparable to utm coordinates unless the zone and hemisphere are known
        with raises(TypeError):
            location_utm == location  # pylint: disable=pointless-statement

        assert GeolocationLocal(location_utm) == location
        assert location_utm == (
            GeolocationUTM(
                location,
                utm_zone=utm_zone,
                northern_hemisphere=northern_hemisphere,
            )
        )
