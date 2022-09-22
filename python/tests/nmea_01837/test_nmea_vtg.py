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


class TestNavigationNMEA_VTG:
    """class for grouping (test sections)"""

    def test_nmea_vtg_common_functions(self):
        """test common, simple functions"""
        sentence = "$GPVTG,38.0,T,,M,1.80,N,3.33,K,D "
        empty_sentence = "$GPVTG,,,,,,,"

        # initialize
        vtg = nmea.decode(sentence)
        vtg_empty = nmea.decode(empty_sentence)
        print(vtg_empty)

        # test empty_sentence
        assert vtg_empty.get_sentence() == empty_sentence
        assert vtg_empty.get_sentence_type() == "VTG"
        assert vtg_empty.get_sentence_id() == "GPVTG"
        assert vtg_empty.get_sender_id() == "GP"
        assert np.isnan(vtg_empty.get_course_over_ground_degrees_true())
        assert np.isnan(vtg_empty.get_course_over_ground_degrees_magnetic())
        assert np.isnan(vtg_empty.get_speed_over_ground_knots())
        assert np.isnan(vtg_empty.get_speed_over_ground_kmh())
        assert vtg_empty.get_mode() == "\x00"
        assert vtg_empty.get_mode_explained() == "Unknown"

        # test variables
        assert vtg.get_sentence() == sentence
        assert vtg.get_sentence_type() == "VTG"
        assert vtg.get_sentence_id() == "GPVTG"
        assert vtg.get_sender_id() == "GP"
        assert vtg.get_course_over_ground_degrees_true() == approx(38.0)
        assert np.isnan(vtg.get_course_over_ground_degrees_magnetic())
        assert vtg.get_speed_over_ground_knots() == approx(1.80)
        assert vtg.get_speed_over_ground_kmh() == approx(3.33)
        assert vtg.get_mode() == "D"
        assert vtg.get_mode_explained() == "Differential"

        # test common functions
        nmea_common_tests(vtg, empty_sentence)
