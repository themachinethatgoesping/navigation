// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_vlw.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_VLW::NMEA_VLW(NMEA_Base base, bool check)
    : NMEA_Base(std::move(base))
{
    if (check)
    {
        if (get_sentence_type() != "VLW")
            throw std::runtime_error(
                fmt::format("NMEA_VLW: wrong sentence type [{}]", get_sentence_type()));
    }
    parse_fields();
}

NMEA_VLW NMEA_VLW::from_stream(std::istream& is)
{
    return NMEA_VLW(NMEA_Base::from_stream(is), true);
}

tools::classhelper::ObjectPrinter NMEA_VLW::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("NMEA VLW Datagram", float_precision, superscript_exponents);

    printer.append(NMEA_Base::__printer__(float_precision, superscript_exponents));

    printer.register_section("VLW attributes");
    printer.register_value(
        "total_water_distance_nautical_miles", get_total_water_distance_nautical_miles(), "nm");
    printer.register_value(
        "trip_water_distance_nautical_miles", get_trip_water_distance_nautical_miles(), "nm");
    printer.register_value("total_ground_distance_nautical_miles",
                           get_total_ground_distance_nautical_miles(),
                           "nm");
    printer.register_value(
        "trip_ground_distance_nautical_miles", get_trip_ground_distance_nautical_miles(), "nm");

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping