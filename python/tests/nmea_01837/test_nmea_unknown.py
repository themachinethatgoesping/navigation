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


class TestNavigationNMEA_Unknown:
    """class for grouping (test sections)"""


    def test_nmea_Unknown_common_functions(self):
        """test common, simple functions"""
        sentence = "$SDABC,42.372,N,42.371,N"
        empty_sentence = "$SDABC,,,,,,,"

        # initialize
        Unknown = nmea.decode(sentence)
        Unknown_empty = nmea.decode(empty_sentence)
        print(Unknown_empty)

        # test empty_sentence
        assert Unknown_empty.get_sentence() == empty_sentence
        assert Unknown_empty.get_sentence_type() == "ABC"
        assert Unknown_empty.get_sentence_id() == "SDABC"
        assert Unknown_empty.get_sender_id() == "SD"
        assert Unknown_empty.get_field(0) == ""
        assert Unknown_empty.get_field(1) == ""
        assert Unknown_empty.get_field(2) == ""
        assert Unknown_empty.get_field(3) == ""
        assert Unknown_empty.get_field(13) == ""
        
        # test variables
        assert Unknown.get_sentence() == sentence
        assert Unknown.get_sentence_type() == "ABC"
        assert Unknown.get_sentence_id() == "SDABC"
        assert Unknown.get_sender_id() == "SD"
        assert Unknown.get_field(0) == "42.372"
        assert Unknown.get_field(1) == "N"
        assert Unknown.get_field(2) == "42.371"
        assert Unknown.get_field(3) == "N"
        assert Unknown.get_field(13) == ""

        # test recognized as Unknown
        assert "NMEA Datagram (not implemented)" in Unknown.info_string()

        # test common functions
        nmea_common_tests(Unknown, empty_sentence)


