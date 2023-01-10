# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.navigation import navtools

from pytest import approx


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
