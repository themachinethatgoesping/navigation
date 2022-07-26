# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation.navdata import GeoLocationUTM, GeoLocationLatLon

import time
from pytest import approx


# define class for grouping (test sections)
class Test_navigation_GeoLocationUTM:
    # define actual tests (must start with "test_"
    # test case 1
    def test_GeoLocationUTM_should_support_common_functions(self):
        location = GeoLocationUTM(
            5427745.995, 
            314082.699, 
            60, 
            False, 
            3, 
            10, 
            20, 
            30)
        print(location)

        # print
        assert len(str(location)) != 0

        # copy
        location2 = location.copy()
        assert location == location2
        location2.northing = 100
        assert location != location2

        # binary
        assert location == GeoLocationUTM.from_binary(location.to_binary())

    
    def test_GeoLocationUTM_should_support_latlon_conversions(self):
        location = GeoLocationUTM(
            5427745.995, 
            314082.699, 
            60, 
            False, 
            3, 
            10, 
            20, 
            30)
        print(location)

        #create a new GeoLocationLatLon object by explicit conversion
        location_latlon = GeoLocationLatLon(location)

        #GeoLocationUTM is implicitly convertible and therefore also comparable to GeoLocationLatLon
        assert location == location_latlon
        assert GeoLocationUTM(location_latlon) == location_latlon

        assert location_latlon.latitude == approx(-41.280330)
        assert location_latlon.longitude == approx(174.780011)
