# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

import themachinethatgoesping.navigation as nav

import time
from pytest import approx, raises


# define class for grouping (test sections)
class Test_navigation_GeoLocationLocal:
    # define actual tests (must start with "test_"
    # test case 1
    def test_GeoLocationLocal_should_support_common_functions(self):
        location = nav.GeoLocationLocal(5427745.995, 314082.699, 3, 10, 20, 30)
        print(location)

        # print
        assert len(str(location)) != 0

        # copy
        location2 = location.copy()
        assert location == location2
        location2.northing = 100
        assert location != location2

        # binary
        assert location == nav.GeoLocationLocal.from_binary(location.to_binary())

    def test_GeoLocationLocal_should_support_utm_conversions(self):
        location = nav.GeoLocationLocal(5427745.995, 314082.699, 3, 10, 20, 30)
        print(location)

        zone = 60
        northern_hemisphere = False

        # create a new GeoLocation object by explicit conversion
        location_utm = nav.GeoLocationUTM(
            location, zone=zone, northern_hemisphere=northern_hemisphere
        )

        # GeoLocationLocal is implicitly convertible and therefore also comparable to GeoLocation
        assert location == location_utm

        # this does not work because local coordinates are not comparable to utm coordinates unless the zone and hemisphere are known
        with raises(TypeError):
            location_utm == location

        assert nav.GeoLocationLocal.from_geolocationutm(location_utm) == location
        assert location_utm == (
            nav.GeoLocationLocal.to_geolocationutm(
                location, zone=zone, northern_hemisphere=northern_hemisphere
            )
        )

        # check conversion with offsets
        offset_northing = 100
        offset_easting = -100
        location_utm2 = nav.GeoLocationUTM(
            location,
            zone=zone,
            northern_hemisphere=northern_hemisphere,
            offset_northing=offset_northing,
            offset_easting=offset_easting,
        )

        assert location_utm2 != location_utm
        assert location_utm2.northing == approx(location_utm.northing + offset_northing)
        assert location_utm2.easting == approx(location_utm.easting + offset_easting)

        location2 = nav.GeoLocationLocal.from_geolocationutm(location_utm2)
        assert location2 == location_utm2

        location3 = nav.GeoLocationLocal(
            location_utm2,
            offset_northing=offset_northing,
            offset_easting=offset_easting,
        )

        assert location3 == location
