# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation import navtools
from themachinethatgoesping.navigation import datastructures

from pytest import approx
import numpy as np


# define class for grouping (test sections)
class Test_navigation_navtools:
    # define actual tests (must start with "test_"
    # test case 1
    def test_to_string_conversion_should_reproduce_precomputed_strings(self):
        assert navtools.latitude_to_string(123.45678, "degrees", 2) == "123.46°N"
        assert navtools.latitude_to_string(123.45678, "minutes", 2) == "123°27.41'N"
        assert navtools.latitude_to_string(123.45678, "seconds", 2) == "123°27'24.41\"N"
        assert (
            navtools.latitude_to_string(-123.45678, "seconds", 3) == "123°27'24.408\"S"
        )

        assert navtools.longitude_to_string(123.45678, "degrees", 2) == "123.46°E"
        assert navtools.longitude_to_string(123.45678, "minutes", 2) == "123°27.41'E"
        assert (
            navtools.longitude_to_string(123.45678, "seconds", 2) == "123°27'24.41\"E"
        )
        assert (
            navtools.longitude_to_string(-123.45678, "seconds", 3) == "123°27'24.408\"W"
        )

    def test_navtools_vectorized_calls_should_produce_same_results_as_single_calls(
        self,
    ):
        latitudes = [123.45678, -123.45678, 23.23, -46.45]
        longitudes = [123.45678, -123.45678, 23.23, -46.45]

        assert navtools.latitude_to_string(latitudes, "degrees", 4) == [
            navtools.latitude_to_string(lat, "degrees", 4) for lat in latitudes
        ]
        assert navtools.latitude_to_string(latitudes, "minutes", 3) == [
            navtools.latitude_to_string(lat, "minutes", 3) for lat in latitudes
        ]
        assert navtools.latitude_to_string(latitudes, "seconds", 2) == [
            navtools.latitude_to_string(lat, "seconds", 2) for lat in latitudes
        ]

        assert navtools.longitude_to_string(longitudes, "degrees", 4) == [
            navtools.longitude_to_string(lon, "degrees", 4) for lon in longitudes
        ]
        assert navtools.longitude_to_string(longitudes, "minutes", 3) == [
            navtools.longitude_to_string(lon, "minutes", 3) for lon in longitudes
        ]
        assert navtools.longitude_to_string(longitudes, "seconds", 2) == [
            navtools.longitude_to_string(lon, "seconds", 2) for lon in longitudes
        ]

    def test_utm_conversion_should_reproduce_precomputed_results(self):
        latitudes = [18.45678, 19.45678, 23.23, 23.45]
        longitudes = [-41.45678, -42.45678, -43.23, -46.45]

        # assert utm conversion is correct
        northing, easting, zone, north = navtools.latlon_to_utm(
            latitudes, longitudes, setzone=-1
        )
        assert northing == approx(
            [
                2044390.562292722,
                2153345.1828180407,
                2570084.6478656493,
                2594081.980875682,
            ]
        )
        assert easting == approx(
            [
                874309.0196121326,
                767003.4675299296,
                681103.4979780763,
                351888.06095795636,
            ]
        )
        assert zone == 23
        assert north

        # assert backward conversion is correct
        lat, lon = navtools.utm_to_latlon(northing, easting, zone, north)
        assert lat == approx(latitudes)
        assert lon == approx(longitudes)

    def test_latlon_distance_comutation(self):
        lat1 = 51.5074 # London
        lon1 = -0.1278
        lat2 = 48.8566 # Paris
        lon2 = 2.3522
        lat3 = 37.7749 # San Francisco
        lon3 = -122.4194
        lat4 = 34.0522 # Los Angeles
        lon4 = -118.2437

        expectedDistance1 = 343923.1200909893 # in meters
        expectedDistance2 = 559042.3365035714 # in meters
        expectedDistance3 = 8976175.5461306088 # in meters

        distance1 = navtools.compute_latlon_distance_m(lat1, lon1, lat2, lon2)
        distance2 = navtools.compute_latlon_distance_m(lat3, lon3, lat4, lon4)

        assert distance1 == approx(expectedDistance1)
        assert distance2 == approx(expectedDistance2)

        # test vectorized calls
        distances1 = navtools.compute_latlon_distances_m([lat1, lat2, lat3, lat4], [lon1, lon2, lon3, lon4])
        assert len(distances1) == 3
        assert type(distances1) == type(np.array([]))
        assert distances1 == approx([expectedDistance1, expectedDistance3, expectedDistance2])

        # test cumulative distance
        distances2 = navtools.cumulative_latlon_distances_m([lat1, lat2, lat3, lat4], [lon1, lon2, lon3, lon4])
        assert len(distances2) == 4
        assert type(distances2) == type(np.array([]))
        assert distances2 == approx([0,expectedDistance1, expectedDistance1+expectedDistance3, expectedDistance1+expectedDistance3+expectedDistance2])

    
        # Test case 4 test above with datastructures::GeolocationLatLon
        loc_latlon = [datastructures.GeolocationLatLon(datastructures.Geolocation(), lat, lon) for lat, lon in zip([lat1, lat2, lat3, lat4], [lon1, lon2, lon3, lon4])]
        sens_latlon = [datastructures.SensordataLatLon(datastructures.Sensordata(), lat, lon) for lat, lon in zip([lat1, lat2, lat3, lat4], [lon1, lon2, lon3, lon4])]
        pair_latlon = [(lat, lon) for lat, lon in zip([lat1, lat2, lat3, lat4], [lon1, lon2, lon3, lon4])]

        # individual distances
        assert navtools.compute_latlon_distance_m(loc_latlon[0], loc_latlon[1]) == approx(distance1)
        assert navtools.compute_latlon_distance_m(sens_latlon[0], sens_latlon[1]) == approx(distance1)
        assert navtools.compute_latlon_distance_m(pair_latlon[0], pair_latlon[1]) == approx(distance1)

        # vector distances
        distances_loc_latlon = navtools.compute_latlon_distances_m(loc_latlon)
        distances_sens_latlon = navtools.compute_latlon_distances_m(sens_latlon)
        distances_pair_latlon = navtools.compute_latlon_distances_m(pair_latlon)

        assert distances_loc_latlon == approx(distances1)
        assert distances_sens_latlon == approx(distances1)
        assert distances_pair_latlon == approx(distances1)

        # cumulative distances
        cumulative_latlon_distances_loc_latlon = navtools.cumulative_latlon_distances_m(loc_latlon)
        cumulative_latlon_distances_sens_latlon = navtools.cumulative_latlon_distances_m(sens_latlon)
        cumulative_latlon_distances_pair_latlon = navtools.cumulative_latlon_distances_m(pair_latlon)

        assert cumulative_latlon_distances_loc_latlon == approx(distances2)
        assert cumulative_latlon_distances_sens_latlon == approx(distances2)
        assert cumulative_latlon_distances_pair_latlon == approx(distances2)