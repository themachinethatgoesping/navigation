# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

""" tests for the nmea-0183 decoding module
"""

# import time
from pytest import approx
import numpy as np

from .nmea_common_tests import nmea_common_tests

# import numpy as np

import themachinethatgoesping.navigation.nmea_0183 as nmea


class TestNavigationNMEA_GGA:
    """class for grouping (test sections)"""

    def test_nmea_gga_common_functions(self):
        """test common, simple functions"""
        sentence = "$GPGGA,112619.00,4410.8232,N,03035.6000,E,2,19,0.6,65.2,M,0.0,M,4.0,0525\x00"
        empty_sentence = "$GPGGA,,,,"

        # initialize
        gga = nmea.decode(sentence)
        gga_empty = nmea.decode(empty_sentence)
        print(gga)

        # # test empty_sentence
        assert gga_empty.get_sentence() == empty_sentence
        assert gga_empty.get_sentence_type() == "GGA"
        assert gga_empty.get_sentence_id() == "GPGGA"
        assert gga_empty.get_sender_id() == "GP"
        assert gga_empty.get_utc_time_string() == ""
        assert np.isnan(gga_empty.get_latitude())
        assert np.isnan(gga_empty.get_longitude())
        assert gga_empty.get_quality() == False
        assert gga_empty.get_quality_explained() == "invalid"
        assert gga_empty.get_number_of_satellites() == False
        assert np.isnan(gga_empty.get_horizontal_dilution_of_precision())
        assert np.isnan(gga_empty.get_altitude())
        assert np.isnan(gga_empty.get_geoidal_separation())
        assert np.isnan(gga_empty.get_age_of_differential_gps_data())
        assert gga_empty.get_differential_reference_station_id() == False

        # # test variables
        assert gga.get_sentence() == sentence
        assert gga.get_sentence_type() == "GGA"
        assert gga.get_sentence_id() == "GPGGA"
        assert gga.get_sender_id() == "GP"

        assert gga.get_utc_time_string() == "112619.00"
        assert gga.get_latitude() == approx(44.180386666666664)
        assert gga.get_longitude() == approx(30.593333333333334)
        assert gga.get_quality() == 2
        assert gga.get_quality_explained() == "DGPS fix"
        assert gga.get_number_of_satellites() == 19
        assert gga.get_horizontal_dilution_of_precision() == approx(0.6)
        assert gga.get_altitude() == approx(65.2)
        assert gga.get_geoidal_separation() == approx(0.0)
        assert gga.get_age_of_differential_gps_data() == approx(4.00)
        assert gga.get_differential_reference_station_id() == 525

        # test common functions
        nmea_common_tests(gga, empty_sentence)
