# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0


import themachinethatgoesping.navigation.nmea_0183 as nmea


def nmea_common_tests(nmea_class, empty_sentence):
    nmea_empty = nmea.decode(empty_sentence)

    # empty_sentence
    assert nmea_empty.get_sentence() == empty_sentence
    assert nmea_empty.get_sentence_type() == nmea_class.get_sentence_type()
    assert nmea_empty.get_sentence_id() == nmea_class.get_sentence_id()
    assert nmea_empty.get_sender_id() == nmea_class.get_sender_id()

    # # copy
    nmea_copy = nmea_class.copy()
    assert nmea_copy == nmea_class
    assert nmea_copy != nmea_empty

    # binary
    a = nmea_class.to_binary()
    assert nmea_class == nmea_class.from_binary(a)

    # print
    # print(nmea_class)
    assert len(nmea_class.info_string()) != 0
