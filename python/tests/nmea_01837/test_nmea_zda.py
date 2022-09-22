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


class TestNavigationNMEA_ZDA:
    """class for grouping (test sections)"""

    def test_nmea_zda_common_functions(self):
        """test common, simple functions"""
        sentence = "$GPZDA,112619.00,14,12,2017,00,00"
        empty_sentence = "$GPZDA,,,,,,"

        # initialize
        zda = nmea.decode(sentence)

        # test empty_sentence
        zda_empty = nmea.decode(empty_sentence)
        assert zda_empty.get_sentence() == empty_sentence
        assert zda_empty.get_sentence_type() == "ZDA"
        assert zda_empty.get_sentence_id() == "GPZDA"
        assert zda_empty.get_sender_id() == "GP"
        assert zda_empty.get_day() == 0
        assert zda_empty.get_month() == 0
        assert zda_empty.get_year() == 0
        assert zda_empty.get_utc_time_string() == ""
        assert zda_empty.get_local_zone_minutes() == 0
        assert zda_empty.get_local_zone_hours() == 0

        assert np.isnan(zda_empty.to_timestamp())
        assert zda_empty.to_date_string() == "NaN_time_string"

        # test variables
        assert zda.get_sentence() == sentence
        assert zda.get_sentence_type() == "ZDA"
        assert zda.get_sentence_id() == "GPZDA"
        assert zda.get_sender_id() == "GP"
        assert zda.get_day() == 14
        assert zda.get_month() == 12
        assert zda.get_year() == 2017
        assert zda.get_utc_time_string() == "112619.00"
        assert zda.get_local_zone_minutes() == 0
        assert zda.get_local_zone_hours() == 0

        # test conversions
        assert zda.to_timestamp() == approx(1513250779.0)
        assert zda.to_date_string() == "+0000__14-12-2017__11:26:19.00"

        # test common functions
        nmea_common_tests(zda, empty_sentence)
