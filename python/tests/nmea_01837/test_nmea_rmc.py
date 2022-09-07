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


class TestNavigationNMEA_RMC:
    """class for grouping (test sections)"""

    def test_nmea_rmc_common_functions(self):
        """test common, simple functions"""
        sentence = "$GPRMC,120921.23,A,5124.0599767,N,00248.6755605,E,0.263,154.5,170322,0.0,E,D\x00\x00\x00\x00"
        empty_sentence = "$GPRMC,,,,"

        # initialize
        rmc = nmea.decode(sentence)
        rmc_empty = nmea.decode(empty_sentence)
        print(rmc_empty)

        # test empty_sentence
        assert rmc_empty.get_sentence() == empty_sentence
        assert rmc_empty.get_sentence_type() == "RMC"
        assert rmc_empty.get_sentence_id() == "GPRMC"
        assert rmc_empty.get_sender_id() == "GP"
        assert rmc_empty.get_utc_time_string() == ""
        assert rmc_empty.get_status() == False
        assert np.isnan(rmc_empty.get_latitude())
        assert np.isnan(rmc_empty.get_longitude())
        assert np.isnan(rmc_empty.get_speed_over_ground_knots())
        assert np.isnan(rmc_empty.get_course_over_ground_degrees_true())
        assert rmc_empty.get_utc_date_string() == ""
        assert np.isnan(rmc_empty.get_magnetic_variation())
        assert rmc_empty.get_mode() == "\x00"
        assert rmc_empty.get_mode_explained() == "Unknown"

        assert np.isnan(rmc_empty.to_timestamp())
        assert rmc_empty.to_date_string() == "NaN_time_string"

        # test variables
        assert rmc.get_sentence() == sentence
        assert rmc.get_sentence_type() == "RMC"
        assert rmc.get_sentence_id() == "GPRMC"
        assert rmc.get_sender_id() == "GP"
        assert rmc.get_utc_time_string() == "120921.23"
        assert rmc.get_status() == True
        assert rmc.get_latitude() == approx(51.40099961166667)
        assert rmc.get_longitude() == approx(2.8112593416666667)
        assert rmc.get_speed_over_ground_knots() == approx(0.263)
        assert rmc.get_course_over_ground_degrees_true() == approx(154.50)
        assert rmc.get_utc_date_string() == "170322"
        assert rmc.get_magnetic_variation() == approx(0.0)
        assert rmc.get_mode() == "E"
        assert rmc.get_mode_explained() == "Estimated"

        # test conversions        
        assert rmc.to_timestamp() == approx(1647518961.23)
        assert rmc.to_date_string() == "+0000__17-03-2022__12:09:21.23"

        # test common functions
        nmea_common_tests(rmc, empty_sentence)
