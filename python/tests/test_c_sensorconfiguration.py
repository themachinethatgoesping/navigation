# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

""" tests for the SensorConfiguration class
"""

# import time
from pytest import approx

# import numpy as np

import themachinethatgoesping.navigation as nav


class TestNavigationSensorConfiguration:
    """class for grouping (test sections)"""

    def test_sensorconfiguration_should_support_common_functions(self):
        """test common, simple functions"""
        data = nav.datastructures.SensordataLatLon(53, 10, 3, 4, 10, 20, 30)

        # initialize
        scs = nav.SensorConfiguration()

        # register target
        scs.add_target(
            "mbes", nav.datastructures.SensorPose("mbes", -12, 9, 3, 10, 11, 12)
        )

        # add offsets
        scs.set_heading_source("sensor", yaw=9)
        scs.set_depth_source("sensor", 0, 0, 1)
        scs.set_position_source("sensor", 1, 2, 3)
        scs.set_attitude_source("sensor", 10, -10, -30)
        scs.set_waterline_offset(0.5)

        # get target position
        position = scs.compute_target_position("mbes", data)
        position2 = nav.datastructures.GeolocationLatLon(
            52.99993263333143,
            10.000048544339503,
            12.50607681274414,
            17.60506545110071,
            29.188285228706675,
            80.77436580631132,
        )
        assert position.latitude == approx(position2.latitude)
        assert position.longitude == approx(position2.longitude)
        assert position.z == approx(position2.z)
        assert position.yaw == approx(position2.yaw)
        assert position.pitch == approx(position2.pitch)
        assert position.roll == approx(position2.roll)
        assert position == position2

        # copy
        scs2 = scs.copy()
        assert scs2 == scs
        scs.set_heading_source("sensor", yaw=12)
        assert scs2 != scs

        # binary
        assert scs == nav.SensorConfiguration.from_binary(scs.to_binary())

        # print
        print(scs)
        assert len(scs.info_string()) != 0

        # more
        assert set(scs.get_target_ids()) == set(["mbes", "0"])

        # remove target
        assert set(scs.get_target_ids()) == set(["mbes", "0"])
        assert scs.without_targets().get_target_ids() == ["0"]

        scs.remove_target("mbes")
        assert scs.get_target_ids() == ["0"]

    def test_sensorconfiguration_transducer_channel_registration(self):
        """test transducer channel registration helpers"""
        scs = nav.SensorConfiguration()
        scs.add_target("TX1", nav.datastructures.SensorPose("TX1", 0, 0, 0, 0, 0, 0))
        scs.add_target("RX1", nav.datastructures.SensorPose("RX1", 0, 0, 0, 0, 0, 0))
        scs.add_target("TRX1", nav.datastructures.SensorPose("TRX1", 0, 0, 0, 0, 0, 0))

        assert not scs.has_transducer_channel("ch1")

        # signature: channel_id, tx_id, rx_id, trx_id, tx_default_sub, rx_default_sub, trx_default_sub
        scs.register_transducer_channel("ch1", "TX1", "RX1", "TRX1", "txsub1", "rxsub1", "trxsub1")
        assert scs.has_transducer_channel("ch1")
        assert scs.get_transducer_transmit_id("ch1") == ("TX1", "txsub1")
        assert scs.get_transducer_receive_id("ch1") == ("RX1", "rxsub1")
        assert scs.get_transducer_transmit_receive_id("ch1") == ("TRX1", "trxsub1")

        # the default subarrays default to "" (new optional arguments)
        scs.register_transducer_channel("ch1", "TX2", "RX2", "TRX2")
        assert scs.get_transducer_transmit_id("ch1") == ("TX2", "")
        assert scs.get_transducer_receive_id("ch1") == ("RX2", "")
        assert scs.get_transducer_transmit_receive_id("ch1") == ("TRX2", "")

        scs2 = nav.SensorConfiguration.from_binary(scs.to_binary())
        assert scs2 == scs
        assert scs2.has_transducer_channel("ch1")
        assert scs2.get_transducer_transmit_id("ch1") == ("TX2", "")
        assert scs2.get_transducer_receive_id("ch1") == ("RX2", "")
        assert scs2.get_transducer_transmit_receive_id("ch1") == ("TRX2", "")

        scs.unregister_transducer_channel("ch1")
        assert not scs.has_transducer_channel("ch1")

        scs.register_transducer_channel("chA", "TXA", "RXA", "TRXA", "txsubA", "rxsubA", "trxsubA")
        scs.register_transducer_channel("chB", "TXB", "RXB", "TRXB", "txsubB", "rxsubB", "trxsubB")
        scs.unregister_all_transducer_channels()
        assert not scs.has_transducer_channel("chA")
        assert not scs.has_transducer_channel("chB")

    def test_sensorconfiguration_transmit_sectors_and_targets(self):
        """test per-transmit-sector subarrays and the get_transducer_*_target helpers"""
        scs = nav.SensorConfiguration()
        scs.add_target("TX", nav.datastructures.SensorPose("TX", 1, 0, 0, 0, 0, 0))
        scs.add_target("RX", nav.datastructures.SensorPose("RX", 0, 2, 0, 0, 0, 0))
        scs.add_target("TRX", nav.datastructures.SensorPose("TRX", 0, 0, 3, 0, 0, 0))
        scs.add_target_subarray("TX", "tx_center", nav.datastructures.SensorPose("tx_center", 0, 0, 0.1, 0, 0, 0))
        scs.add_target_subarray("TX", "s0", nav.datastructures.SensorPose("s0", 0, 0, 0.2, 0, 0, 0))
        scs.add_target_subarray("TX", "s1", nav.datastructures.SensorPose("s1", 0, 0, 0.5, 0, 0, 0))

        scs.register_transducer_channel(
            "ch", "TX", "RX", "TRX", "tx_center", "", "", tx_sector_subarrays=["s0", "s1"]
        )

        # no sector -> default subarray; sector -> the registered sector subarray
        assert scs.get_transducer_transmit_id("ch") == ("TX", "tx_center")
        assert scs.get_transducer_transmit_id("ch", 0) == ("TX", "s0")
        assert scs.get_transducer_transmit_id("ch", 1) == ("TX", "s1")

        # the *_target helpers resolve the registered targets (target combined with its subarray)
        assert scs.get_transducer_transmit_target("ch") == scs.get_target("TX", "tx_center")
        assert scs.get_transducer_transmit_target("ch", 1) == scs.get_target("TX", "s1")
        assert scs.get_transducer_receive_target("ch") == scs.get_target("RX")
        assert scs.get_transducer_transmit_receive_target("ch") == scs.get_target("TRX")

        # sectors survive the binary roundtrip
        scs2 = nav.SensorConfiguration.from_binary(scs.to_binary())
        assert scs2 == scs
        assert scs2.get_transducer_transmit_id("ch", 1) == ("TX", "s1")


