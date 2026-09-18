// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/* generated doc strings */
#include "navtools.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace navtools {

std::string epsg_from_utmups(int zone, bool northp)
{
    if (zone == GeographicLib::UTMUPS::UPS)
        return northp ? "EPSG:5041" : "EPSG:5042"; // WGS 84 / UPS North / South

    if (zone < 1 || zone > 60)
        throw std::out_of_range("invalid UTM zone: " + std::to_string(zone));

    return fmt::format("EPSG:{}", (northp ? 32600 : 32700) + zone);
}

/**
 * @brief Get the EPSG code (UTMUPS) for a given latitude and longitude.
 * This function determines the appropriate UTM/UPS zone and hemisphere for the given latitude and
 * longitude, and returns the corresponding EPSG code.
 *
 * @param lat latitude in decimal degrees
 * @param lon longitude in decimal degrees
 * @return std::string
 */
std::string epsg_from_latlon(double latitude, double longitude)
{
    using namespace GeographicLib;
    int    zone;
    bool   northp;
    double x, y;
    UTMUPS::Forward(latitude, longitude, zone, northp, x, y); // throws on invalid lat/lon
    return epsg_from_utmups(zone, northp);
}

/**
 * @brief Get the wgs84 epsg object
 *
 * @return std::string
 */
constexpr std::string epsg_wgs84()
{
    return "EPSG:4326"; // WGS 84
}

} // namespace navtools
} // namespace navigation
} // namespace themachinethatgoesping

template class themachinethatgoesping::tools::classhelper::Option<
    themachinethatgoesping::navigation::navtools::t_latlon_format>;