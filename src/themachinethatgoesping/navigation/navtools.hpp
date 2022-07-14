// Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/**
 * @brief Some navigation helper functions that allow converting different lat/lon formats (decimal,
 * minute / decimal degrees etc) and utm coordinats to lat/lon decimal degrees and back
 *
 */

#include <fmt/core.h>
#include <magic_enum.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace navtools {

/**
 * @brief lat/lon format specificaionts
 *
 */
enum class t_latlon_format
{
    degrees = 0, ///< lat/lon will be converted to degrees.degrees°N/S E/W
    minutes = 1, ///< lat/lon will be converted to degrees°minutes.minutes'E/S E/W
    seconds = 2  ///< lat/lon will be converted to degrees°minutes'seconds.seconds''E/S E/W
};


inline std::string dms_to_string(double dms_value, t_latlon_format format, size_t precission, char sign)
{
    dms_value = std::abs(dms_value);

    switch (format)
    {
        case t_latlon_format::degrees:
            return fmt::format("{:.{}f}°{}", dms_value, precission, sign);
        case t_latlon_format::minutes: {
            int    degrees = dms_value;
            double minutes = (dms_value - double(degrees)) * 60;
            return fmt::format("{}°{:.{}f}'{}", degrees, minutes, precission, sign);
        }
        case t_latlon_format::seconds: {
            int    degrees = dms_value;
            double minutes = (dms_value - double(degrees)) * 60;
            double seconds = (minutes - double(int(minutes))) * 60;
            return fmt::format("{}°{}'{:.{}f}\"{}", degrees, int(minutes), seconds, precission, sign);
        }
        default:
            throw std::runtime_error("ERROR[latitude/longitude_to_string]: Unknown ENUM type!");
    }
}

/**
 * @brief convert a latitude value to a string
 * 
 * @param latitude value to be converted
 * @param precission number of digits behind the .
 * @param format latlon format (degrees°N/S, degrees°minutes'N/S or degrees°minutes'seconds''N/S)
 * @return converted latitude string
 */
inline std::string latitude_to_string(double latitude, t_latlon_format format = t_latlon_format::minutes, size_t precission = 6)
{
    char sign = 'N';
    if (latitude < 0)
        sign = 'S';

    return dms_to_string(latitude, format, precission, sign);
}


/**
 * @brief convert a latitude value to a string
 * 
 * @param latitude value to be converted
 * @param precission number of digits behind the .
 * @param format latlon format (degrees°N/S, degrees°minutes'N/S or degrees°minutes'seconds''N/S)
 * @return converted latitude string
 */
inline std::string longitude_to_string(double longitude, t_latlon_format format = t_latlon_format::minutes, size_t precission = 6)
{
    char sign = 'E';
    if (longitude < 0)
        sign = 'W';

    return dms_to_string(longitude, format, precission, sign);
}

}
}
}