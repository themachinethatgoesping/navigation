// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/sensorconfiguration_presets.doc.hpp"

#include <cctype>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>

#include <fmt/core.h>

#include "datastructures.hpp"

namespace themachinethatgoesping {
namespace navigation {

/**
 * @brief Hardcoded transmit/receive subarray phase-center offsets for known echosounder models.
 *
 * Offsets in the transducer frame (x forward, y starboard, z down, metres).
 * Source: Kongsberg EM datagram formats 850-160692/V, appendices A–D.
 * Transmit subarrays: "0" = port, "1" = centre, "2" = starboard (or just "0" for single-array).
 * Receive phase centre: "RX".
 * Returns an empty map for unknown models.
 *
 * @param model_name echosounder model (case-insensitive, optional leading "EM" ignored)
 */
inline std::pair<std::map<std::string, datastructures::SensorPose, std::less<>>,
                 std::map<std::string, datastructures::SensorPose, std::less<>>>
get_model_subarray_offsets(std::string_view model_name)
{
    // normalize: lowercase, drop spaces/_/-, strip leading "em"
    std::string m;
    m.reserve(model_name.size());
    for (char c : model_name)
    {
        if (c == ' ' || c == '_' || c == '-')
            continue;
        m.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    if (m.rfind("em", 0) == 0)
        m.erase(0, 2);

    std::map<std::string, datastructures::SensorPose, std::less<>> tx_offsets;
    std::map<std::string, datastructures::SensorPose, std::less<>> rx_offsets;

    if (m.rfind("2040p", 0) == 0) // EM2040P (portable single head, appendix C)
    {
        tx_offsets["tx_port"] =  datastructures::SensorPose("tx-port", 0.002f, -0.1042f, -0.0149f, 0.f, 0.f, 0.f);
        tx_offsets["tx_center"] =  datastructures::SensorPose("tx-centre", 0.002f, 0.f, -0.006f, 0.f, 0.f, 0.f);
        tx_offsets["tx_starboard"] =  datastructures::SensorPose("tx-starboard", 0.002f, 0.1042f, -0.0149f, 0.f, 0.f, 0.f);
        rx_offsets["rx_center"] = datastructures::SensorPose("rx", 0.204f, 0.f, -0.0315f, 0.f, 0.f, 0.f);
    }
    else if (m.rfind("2040m", 0) == 0) // EM2040M (modular, appendix D)
    {
        tx_offsets["tx_port"] = datastructures::SensorPose("tx-port", 0.f, -0.1042f, -0.0454f, 0.f, 0.f, 0.f);
        tx_offsets["tx_center"] = datastructures::SensorPose("tx-centre", 0.f, 0.f, -0.006f, 0.f, 0.f, 0.f);
        tx_offsets["tx_starboard"] = datastructures::SensorPose("tx-starboard", 0.f, 0.1042f, -0.0454f, 0.f, 0.f, 0.f);
        rx_offsets["rx_center"] = datastructures::SensorPose("rx", 0.202f, 0.f, -0.0619f, 0.f, 0.f, 0.f);
    }
    else if (m.rfind("2040c", 0) == 0) // EM2040C (compact single head, appendix B; single tx array)
    {
        tx_offsets["tx_center"]  = datastructures::SensorPose("tx", 0.0038f, 0.040f, -0.006f, 0.f, 0.f, 0.f);
        rx_offsets["rx_center"] = datastructures::SensorPose("rx", -0.0455f, 0.f, -0.006f, 0.f, 0.f, 0.f);
    }
    else if (m.rfind("2040", 0) == 0) // EM2040 (appendix A)
    {
        tx_offsets["tx_port"]  = datastructures::SensorPose("tx-port", 0.f, -0.0554f, -0.012f, 0.f, 0.f, 0.f);
        tx_offsets["tx_center"]  = datastructures::SensorPose("tx-centre", 0.f, 0.01315f, -0.006f, 0.f, 0.f, 0.f);
        tx_offsets["tx_starboard"]  = datastructures::SensorPose("tx-starboard", 0.f, 0.0554f, -0.012f, 0.f, 0.f, 0.f);
        rx_offsets["rx_center"] = datastructures::SensorPose("rx", 0.011f, 0.f, -0.006f, 0.f, 0.f, 0.f);
    }
    else if (m.rfind("2042", 0) == 0) // EM2042 (QPS dm-0423; not in EM appendices)
    {
        tx_offsets["tx_port"]  = datastructures::SensorPose("tx-port", 0.f, -0.04887f, -0.01156f, 0.f, 0.f, 0.f);
        tx_offsets["tx_center"]  = datastructures::SensorPose("tx-centre", 0.f, 0.0065f, -0.0056f, 0.f, 0.f, 0.f);
        tx_offsets["tx_starboard"]  = datastructures::SensorPose("tx-starboard", 0.f, 0.04887f, -0.01156f, 0.f, 0.f, 0.f);
        rx_offsets["rx_center"] = datastructures::SensorPose("rx", 0.01f, 0.f, -0.006f, 0.f, 0.f, 0.f);
    }

    return std::make_pair(tx_offsets, rx_offsets);
}


} // namespace navigation
} // namespace themachinethatgoesping
