# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
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


class TestNavigationNMEA_VLW:
    """class for grouping (test sections)"""

    def test_nmea_vlw_common_functions(self):
        """test common, simple functions"""
        sentence = "$SDVLW,42.372,N,42.371,N"
        empty_sentence = "$SDVLW,,,,,,,"

        # initialize
        vlw = nmea.decode(sentence)
        vlw_empty = nmea.decode(empty_sentence)
        print(vlw_empty)

        # test empty_sentence
        assert vlw_empty.get_sentence() == empty_sentence
        assert vlw_empty.get_sentence_type() == "VLW"
        assert vlw_empty.get_sentence_id() == "SDVLW"
        assert vlw_empty.get_sender_id() == "SD"
        assert np.isnan(vlw_empty.get_total_water_distance_nautical_miles())
        assert np.isnan(vlw_empty.get_trip_water_distance_nautical_miles())
        assert np.isnan(vlw_empty.get_total_ground_distance_nautical_miles())
        assert np.isnan(vlw_empty.get_trip_ground_distance_nautical_miles())

        # test variables
        assert vlw.get_sentence() == sentence
        assert vlw.get_sentence_type() == "VLW"
        assert vlw.get_sentence_id() == "SDVLW"
        assert vlw.get_sender_id() == "SD"
        assert vlw.get_total_water_distance_nautical_miles() == approx(42.372)
        assert vlw.get_trip_water_distance_nautical_miles() == approx(42.371)
        assert np.isnan(vlw_empty.get_total_ground_distance_nautical_miles())
        assert np.isnan(vlw_empty.get_trip_ground_distance_nautical_miles())

        # test common functions
        nmea_common_tests(vlw, empty_sentence)
