// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_vhw.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_VHW::NMEA_VHW(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "VHW")
            throw std::runtime_error(
                fmt::format("NMEA_VHW: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

NMEA_VHW NMEA_VHW::from_stream(std::istream& is)
{
    return NMEA_VHW(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_VHW::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA VHW Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("VHW attributes");
    printer.register_value(
        "vessel_heading_true", get_vessel_heading_true(), "°, true");
    printer.register_value(
        "vessel_heading_magnetic", get_vessel_heading_magnetic(), "°, magnetic");
    printer.register_value("speed_over_water_knots", get_speed_over_water_knots(), "knots");
    printer.register_value("speed_over_water_kmh", get_speed_over_water_kmh(), "km/h");

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping