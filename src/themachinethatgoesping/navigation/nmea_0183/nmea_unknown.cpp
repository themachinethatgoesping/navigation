// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_unknown.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_Unknown::NMEA_Unknown(NMEA_Base base, [[maybe_unused]] bool check)
    : NMEA_Base(std::move(base))
{
    // if (check) {
    // }
    parse_fields();
}

NMEA_Unknown NMEA_Unknown::from_stream(std::istream& is)
{
    return NMEA_Unknown(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_Unknown::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA Datagram (not implemented)",
                                              float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));
    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping