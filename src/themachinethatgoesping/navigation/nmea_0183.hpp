// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <variant>

#include <themachinethatgoesping/tools/helper.hpp>

#include "nmea_0183/nmea_base.hpp"
#include "nmea_0183/nmea_gga.hpp"
#include "nmea_0183/nmea_gll.hpp"
#include "nmea_0183/nmea_hdt.hpp"
#include "nmea_0183/nmea_rmc.hpp"
#include "nmea_0183/nmea_unknown.hpp"
#include "nmea_0183/nmea_vhw.hpp"
#include "nmea_0183/nmea_vlw.hpp"
#include "nmea_0183/nmea_vtg.hpp"
#include "nmea_0183/nmea_zda.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

enum class t_NMEA_0183 : int32_t
{
    t_NMEA_Unknown,
    t_NMEA_ZDA,
    t_NMEA_VLW,
    t_NMEA_VTG,
    t_NMEA_VHW,
    t_NMEA_RMC,
    t_NMEA_HDT,
    t_NMEA_GLL,
    t_NMEA_GGA
};

using NMEA_0183_type = std::variant<NMEA_Unknown,
                                    NMEA_ZDA,
                                    NMEA_VLW,
                                    NMEA_VTG,
                                    NMEA_VHW,
                                    NMEA_RMC,
                                    NMEA_HDT,
                                    NMEA_GLL,
                                    NMEA_GGA>;

inline NMEA_0183_type decode(NMEA_Base nmea_sentence)
{
    auto sentence_type = nmea_sentence.get_sentence_type();

    if (sentence_type == "ZDA")
        return std::move(NMEA_ZDA(std::move(nmea_sentence)));
    if (sentence_type == "VLW")
        return std::move(NMEA_VLW(std::move(nmea_sentence)));
    if (sentence_type == "VTG")
        return std::move(NMEA_VTG(std::move(nmea_sentence)));
    if (sentence_type == "VHW")
        return std::move(NMEA_VHW(std::move(nmea_sentence)));
    if (sentence_type == "RMC")
        return std::move(NMEA_RMC(std::move(nmea_sentence)));
    if (sentence_type == "HDT")
        return std::move(NMEA_HDT(std::move(nmea_sentence)));
    if (sentence_type == "GLL")
        return std::move(NMEA_GLL(std::move(nmea_sentence)));
    if (sentence_type == "GGA")
        return std::move(NMEA_GGA(std::move(nmea_sentence)));
    return NMEA_Unknown(std::move(std::move(nmea_sentence)));
}

inline NMEA_0183_type decode(std::string nmea_sentence)
{
    return decode(NMEA_Base(std::move(nmea_sentence)));
}

inline NMEA_0183_type from_stream(std::istream& is, size_t length)
{
    return decode(std::move(NMEA_Base::from_stream(is, length)));
}

} // of nmea_0183::
} // of navigation::
} // of themachinethatgoesping::
