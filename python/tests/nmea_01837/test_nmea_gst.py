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


class TestNavigationNMEA_GST:
    """class for grouping (test sections)"""

    def test_nmea_GST_common_functions(self):
        """test common, simple functions"""
        sentence = "$GPGST,120921.00,0.74,0.58,0.41,349.5610,0.57,0.41,0.98"
        empty_sentence = "$GPGST,,,,"

        # initialize
        gst = nmea.decode(sentence)
        gst_empty = nmea.decode(empty_sentence)
        print(gst)

        # # test empty_sentence
        assert gst_empty.get_sentence() == empty_sentence
        assert gst_empty.get_sentence_type() == "GST"
        assert gst_empty.get_sentence_id() == "GPGST"
        assert gst_empty.get_sender_id() == "GP"
        assert gst_empty.get_utc_time_string() == ""
        assert np.isnan(gst_empty.get_psuedorange_rms())
        assert np.isnan(gst_empty.get_semimajor_error())
        assert np.isnan(gst_empty.get_semiminor_error())
        assert np.isnan(gst_empty.get_semimajor_error_orientation())
        assert np.isnan(gst_empty.get_latitude_error_deviation())
        assert np.isnan(gst_empty.get_longitude_error_deviation())
        assert np.isnan(gst_empty.get_altitude_error_deviation())

        # # test variables
        assert gst.get_sentence() == sentence
        assert gst.get_sentence_type() == "GST"
        assert gst.get_sentence_id() == "GPGST"
        assert gst.get_sender_id() == "GP"

        assert gst.get_utc_time_string() == "120921.00"
        assert gst.get_psuedorange_rms() == approx(0.74)
        assert gst.get_semimajor_error() == approx(0.58)
        assert gst.get_semiminor_error() == approx(0.41)
        assert gst.get_semimajor_error_orientation() == approx(349.5610)
        assert gst.get_latitude_error_deviation() == approx(0.57)
        assert gst.get_longitude_error_deviation() == approx(0.41)
        assert gst.get_altitude_error_deviation() == approx(0.98)

        # test common functions
        nmea_common_tests(gst, empty_sentence)
