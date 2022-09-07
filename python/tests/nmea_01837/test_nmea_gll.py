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


class TestNavigationNMEA_GLL:
    """class for grouping (test sections)"""

    def test_nmea_gll_common_functions(self):
        """test common, simple functions"""
        sentence = "$GPGLL,5124.0599767,N,00248.6755605,E,120921.00,A,D"
        empty_sentence = "$GPGLL,,,,"

        # initialize
        gll = nmea.decode(sentence)
        gll_empty = nmea.decode(empty_sentence)
        print(gll)

        # # test empty_sentence
        assert gll_empty.get_sentence() == empty_sentence
        assert gll_empty.get_sentence_type() == "GLL"
        assert gll_empty.get_sentence_id() == "GPGLL"
        assert gll_empty.get_sender_id() == "GP"
        assert np.isnan(gll_empty.get_latitude())
        assert np.isnan(gll_empty.get_longitude())
        assert gll_empty.get_utc_time_string() == ""
        assert gll_empty.get_status() == False
        assert gll_empty.get_mode() == "\x00"
        assert gll_empty.get_mode_explained() == "Unknown"

        # # test variables
        assert gll.get_sentence() == sentence
        assert gll.get_sentence_type() == "GLL"
        assert gll.get_sentence_id() == "GPGLL"
        assert gll.get_sender_id() == "GP"
        assert gll.get_latitude() == approx(51 + 24.0599767 / 60.0)
        assert gll.get_longitude() == approx(2 + 48.6755605 / 60.0)
        assert gll.get_utc_time_string() == "120921.00"
        assert gll.get_status() == True
        assert gll.get_mode() == "D"
        assert gll.get_mode_explained() == "Differential"

        # test common functions
        nmea_common_tests(gll, empty_sentence)
