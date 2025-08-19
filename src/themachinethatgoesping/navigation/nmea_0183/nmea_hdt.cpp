// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_hdt.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_HDT::NMEA_HDT(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "HDT")
            throw std::runtime_error(
                fmt::format("NMEA_HDT: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

NMEA_HDT NMEA_HDT::from_stream(std::istream& is)
{
    return NMEA_HDT(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_HDT::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA HDT Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("HDT attributes");
    printer.register_value("heading_degrees_true", get_heading_degrees_true());

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping