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


class TestNavigationNMEA_HDT:
    """class for grouping (test sections)"""

    def test_nmea_hdt_common_functions(self):
        """test common, simple functions"""
        sentence = "$INHDT,54.96,T"
        empty_sentence = "$INHDT,,,,"

        # initialize
        hdt = nmea.decode(sentence)
        hdt_empty = nmea.decode(empty_sentence)
        print(hdt)

        # # test empty_sentence
        assert hdt_empty.get_sentence() == empty_sentence
        assert hdt_empty.get_sentence_type() == "HDT"
        assert hdt_empty.get_sentence_id() == "INHDT"
        assert hdt_empty.get_sender_id() == "IN"
        assert np.isnan(hdt_empty.get_heading_degrees_true())

        # # test variables
        assert hdt.get_sentence() == sentence
        assert hdt.get_sentence_type() == "HDT"
        assert hdt.get_sentence_id() == "INHDT"
        assert hdt.get_sender_id() == "IN"
        assert hdt.get_heading_degrees_true() == approx(54.96)

        # test common functions
        nmea_common_tests(hdt, empty_sentence)
