// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_gst.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_GST::NMEA_GST(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "GST")
            throw std::runtime_error(
                fmt::format("NMEA_GST: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

NMEA_GST NMEA_GST::from_stream(std::istream& is)
{
    return NMEA_GST(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_GST::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA GST Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("GST attributes");
    printer.register_value("utc_time_string", get_utc_time_string(), "hhmmss.ss");
    printer.register_value("psuedorange_rms", get_psuedorange_rms(), "m");
    printer.register_value("semimajor_error", get_semimajor_error(), "m");
    printer.register_value("semiminor_error", get_semiminor_error(), "m");
    printer.register_value(
        "semimajor_error_orientation", get_semimajor_error_orientation(), "deg");
    printer.register_value("latitude_error_deviation", get_latitude_error_deviation(), "m");
    printer.register_value("longitude_error_deviation", get_longitude_error_deviation(), "m");
    printer.register_value("altitude_error_deviation", get_altitude_error_deviation(), "m");

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping