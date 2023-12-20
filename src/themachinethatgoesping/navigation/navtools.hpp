// Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/navtools.doc.hpp"

/**
 * @brief Some navigation helper functions that allow converting different lat/lon formats (decimal,
 * minute / decimal degrees etc) and utm coordinates to lat/lon decimal degrees and back
 *
 */

#include <stdexcept>
#include <tuple>
#include <vector>

#include "GeographicLib/Geodesic.hpp"
#include <GeographicLib/UTMUPS.hpp>
#include <fmt/core.h>

#include <xtensor/xcontainer.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace navtools {

/**
 * @brief lat/lon format specifications
 *
 */
enum class t_latlon_format
{
    degrees = 0, ///< lat/lon will be converted to degrees.degrees°N/S E/W
    minutes = 1, ///< lat/lon will be converted to degrees°minutes.minutes'E/S E/W
    seconds = 2  ///< lat/lon will be converted to degrees°minutes'seconds.seconds''E/S E/W
};

/**
 * @brief c++20 concept to check if a type has latitude and longitude members
 *
 * @tparam T
 */
template<typename T>
concept HasLatitudeLongitude = requires(T t) {
    {
        t.latitude
    } -> std::convertible_to<float>;
    {
        t.longitude
    } -> std::convertible_to<float>;
};

template<typename T>
concept RandomAccessContainerOfLatLonHolders = requires(T t) {
    typename T::value_type;
    requires std::random_access_iterator<typename T::iterator>;
    requires HasLatitudeLongitude<typename T::value_type>;
};

template<typename T>
concept RandomAccessContainerOfFloats = requires(T t) {
    typename T::value_type;
    requires std::random_access_iterator<typename T::iterator>;
    requires std::floating_point<typename T::value_type>;
};

inline std::string dms_to_string(double          dms_value,
                                 t_latlon_format format,
                                 size_t          precision,
                                 char            sign)
{
    dms_value = std::abs(dms_value);

    switch (format)
    {
        case t_latlon_format::degrees:
            return fmt::format("{:.{}f}°{}", dms_value, precision, sign);
        case t_latlon_format::minutes: {
            int    degrees = int(dms_value);
            double minutes = (dms_value - double(degrees)) * 60;
            return fmt::format("{}°{:.{}f}'{}", degrees, minutes, precision, sign);
        }
        case t_latlon_format::seconds: {
            int    degrees = int(dms_value);
            double minutes = (dms_value - double(degrees)) * 60;
            double seconds = (minutes - double(int(minutes))) * 60;
            return fmt::format(
                "{}°{}'{:.{}f}\"{}", degrees, int(minutes), seconds, precision, sign);
        }
        default:
            throw std::runtime_error("ERROR[latitude/longitude_to_string]: Unknown ENUM type!");
    }
}

/**
 * @brief convert a latitude value to a string
 *
 * @param latitude value to be converted
 * @param precision number of digits behind the .
 * @param format latlon format (degrees°N/S, degrees°minutes'N/S or degrees°minutes'seconds''N/S)
 * @return converted latitude string
 */
inline std::string latitude_to_string(double          latitude,
                                      t_latlon_format format    = t_latlon_format::minutes,
                                      size_t          precision = 6)
{
    char sign = 'N';
    if (latitude < 0)
        sign = 'S';

    return dms_to_string(latitude, format, precision, sign);
}

/**
 * @brief convert a latitude value to a string
 *
 * @param latitude value to be converted
 * @param precision number of digits behind the .
 * @param format latlon format (degrees°N/S, degrees°minutes'N/S or degrees°minutes'seconds''N/S)
 * @return converted latitude string
 */
inline std::string longitude_to_string(double          longitude,
                                       t_latlon_format format    = t_latlon_format::minutes,
                                       size_t          precision = 6)
{
    char sign = 'E';
    if (longitude < 0)
        sign = 'W';

    return dms_to_string(longitude, format, precision, sign);
}

/**
 * @brief Convert utm coordinates to latitude longitude using Geographic lib
 *
 * @param northing northing in meters
 * @param easting easting in meters
 * @param zone utm zone number (1-60)
 * @param northern_hemisphere if true, northern hemisphere, else southern hemisphere
 * @return (list of latitude, list of longitudes)
 */
inline std::pair<std::vector<double>, std::vector<double>> utm_to_latlon(
    const std::vector<double>& northing,
    const std::vector<double>& easting,
    int                        zone,
    bool                       northern_hemisphere)
{
    // check if vector sizes are the same
    if (easting.size() != northing.size())
        throw std::runtime_error(
            "ERROR[utm_to_latlon]: easting and northing vector sizes are not the same!");

    // initialize output vectors
    std::vector<double> lat, lon;
    lat.resize(northing.size());
    lon.resize(northing.size());

    // loop through data and convert using GeographicLib
    for (size_t i = 0; i < easting.size(); i++)
    {
        GeographicLib::UTMUPS::Reverse(
            zone, northern_hemisphere, easting[i], northing[i], lat[i], lon[i]);
    }

    return std::make_pair(lat, lon);
}

/**
 * @brief Convert utm coordinates to latitude longitude using Geographic lib
 *
 * @param northing northing in meters
 * @param easting easting in meters
 * @param zone utm zone number (1-60)
 * @param northern_hemisphere if true, northern hemisphere, else southern hemisphere
 * @return (list of latitude, list of longitudes)
 */
inline std::pair<std::vector<double>, std::vector<double>> utm_to_latlon(
    const std::vector<double>& northing,
    const std::vector<double>& easting,
    const std::vector<int>&    zone,
    const std::vector<bool>&   northern_hemisphere)
{
    // check if vector sizes are the same
    if (easting.size() != northing.size() && easting.size() != zone.size() &&
        easting.size() != northern_hemisphere.size())
        throw std::runtime_error("ERROR[utm_to_latlon]: easting, northing, zone and "
                                 "northern_hemisphere vector sizes are not the same!");

    // initialize output vectors
    std::vector<double> lat, lon;
    lat.resize(northing.size());
    lon.resize(northing.size());

    // loop through data and convert using GeographicLib
    for (size_t i = 0; i < easting.size(); i++)
    {
        GeographicLib::UTMUPS::Reverse(
            zone[i], northern_hemisphere[i], easting[i], northing[i], lat[i], lon[i]);
    }

    return std::make_pair(lat, lon);
}

/**
 * @brief Convert latitudes and longitudes to utm coordinates using GeographicLib
 *
 * @param lat list of latitudes
 * @param lon list of longitudes
 * @param setzone utm output zone number (1-60), default (-1) determines zone using mean latitude
 * and longitude
 * @return std::tuple<std::vector<double>, std::vector<double>, int, bool>
 */
inline std::tuple<std::vector<double>, std::vector<double>, int, bool>
latlon_to_utm(const std::vector<double>& lat, const std::vector<double>& lon, int setzone = -1)
{
    // check if vector sizes are the same
    if (lat.size() != lon.size())
        throw std::runtime_error(
            "ERROR[latlon_to_utm]: lat and lon vector sizes are not the same!");

    // determine setzone using mean of latitudes and longitudes
    if (setzone == -1)
    {
        double mean_lat = 0;
        double mean_lon = 0;
        for (size_t i = 0; i < lat.size(); i++)
        {
            mean_lat += lat[i];
            mean_lon += lon[i];
        }
        mean_lat /= double(lat.size());
        mean_lon /= double(lat.size());
        setzone = GeographicLib::UTMUPS::StandardZone(mean_lat, mean_lon);
    }

    // initialize output data
    std::vector<double> northing, easting;
    northing.resize(lat.size());
    easting.resize(lat.size());
    int  zone;
    bool northern_hemisphere;

    // loop through data and convert using GeographicLib
    for (size_t i = 0; i < lat.size(); i++)
    {
        GeographicLib::UTMUPS::Forward(
            lat[i], lon[i], zone, northern_hemisphere, easting[i], northing[i], setzone);
    }
    return std::make_tuple(northing, easting, zone, northern_hemisphere);
}

/**
 * @brief Calculate the distance between two points on the Earth's surface using geographiclib
 *
 * @tparam T_float floating-point type for latitude and longitude values
 * @param lat1 latitude of the first point
 * @param lon1 longitude of the first point
 * @param lat2 latitude of the second point
 * @param lon2 longitude of the second point
 * @return distance between the two points in meters
 */
template<std::floating_point T_float>
T_float compute_latlon_distance_m(T_float lat1, T_float lon1, T_float lat2, T_float lon2)
{
    GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                 GeographicLib::Constants::WGS84_f());
    T_float                 s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12;
}

/**
 * @brief Calculate the distances between consecutive points in the given latitude and longitude
 * vectors in meters
 *
 * @tparam T_float floating-point type for latitude and longitude values
 * @param latitudes vector of latitudes
 * @param longitudes vector of longitudes
 * @return vector of distances between consecutive points
 */
template<RandomAccessContainerOfFloats T_float_container>
T_float_container compute_latlon_distances_m(const T_float_container& latitudes,
                                             T_float_container&       longitudes)
{
    if (latitudes.size() != longitudes.size())
        throw std::runtime_error(
            "ERROR[distance]: latitudes and longitudes vector sizes are not the same!");

    if (latitudes.size() < 2)
        throw std::runtime_error(
            "ERROR[distance]: latitudes and longitudes vector sizes are too small!");

    T_float_container distances;

    // if the container is an xtensor container, we need to resize it using a tuple
    // else we assume it is a std::vector
    if constexpr (std::is_base_of<xt::xcontainer<T_float_container>, T_float_container>::value)
        distances = T_float_container::from_shape({ int64_t(latitudes.size() - 1) });
    else
        distances.resize(latitudes.size() - 1);

    GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                 GeographicLib::Constants::WGS84_f());

    for (size_t i = 0; i < latitudes.size() - 1; i++)
    {
        geod.Inverse(
            latitudes[i], longitudes[i], latitudes[i + 1], longitudes[i + 1], distances[i]);
    }

    return distances;
}

/**
 * @brief Calculate the cumulative distances between consecutive points in the given latitude and
 * longitude vectors in meters
 *
 * @tparam T_float floating-point type for latitude and longitude values
 * @param latitudes vector of latitudes
 * @param longitudes vector of longitudes
 * @return vector of cumulative distances
 */
template<RandomAccessContainerOfFloats T_float_container>
T_float_container cumulative_latlon_distances_m(const T_float_container& latitudes,
                                                const T_float_container& longitudes)
{
    if (latitudes.size() != longitudes.size())
        throw std::runtime_error("ERROR[cumulative_latlon_distances_m]: latitudes and longitudes "
                                 "vector sizes are not the same!");

    if (latitudes.size() < 2)
        throw std::runtime_error("ERROR[cumulative_latlon_distances_m]: latitudes and longitudes "
                                 "vector sizes are too small!");

    T_float_container distances;
    // if the container is an xtensor container, we need to resize it using a tuple
    // else we assume it is a std::vector
    if constexpr (std::is_base_of<xt::xcontainer<T_float_container>, T_float_container>::value)
        distances = T_float_container::from_shape({ int64_t(latitudes.size()) });
    else
        distances.resize(latitudes.size());

    GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                 GeographicLib::Constants::WGS84_f());

    distances[0] = 0;
    for (size_t i = 1; i < latitudes.size(); i++)
    {
        geod.Inverse(
            latitudes[i - 1], longitudes[i - 1], latitudes[i], longitudes[i], distances[i]);

        distances[i] += distances[i - 1];
    }

    return distances;
}

/**
 * @brief Compute the 2D distance between two points using latitude and longitude values in meters
 *
 * @tparam T_latlon_holder type of the latitude and longitude holder
 * @param geolocation_latlon_1 first latitude and longitude holder
 * @param geolocation_latlon_2 second latitude and longitude holder
 * @return distance between the two points in meters
 */
template<HasLatitudeLongitude T_latlon_holder>
inline auto compute_latlon_distance_m(const T_latlon_holder& geolocation_latlon_1,
                                      const T_latlon_holder& geolocation_latlon_2)
{
    return compute_latlon_distance_m(geolocation_latlon_1.latitude,
                                     geolocation_latlon_1.longitude,
                                     geolocation_latlon_2.latitude,
                                     geolocation_latlon_2.longitude);
}

/**
 * @brief Compute the 2D distances between consecutive points in the given latitude and longitude
 * holder container in meters
 *
 * @tparam T_latlon_holder_container type of the latitude and longitude holder container
 * @param geolocations_latlon container of latitude and longitude holders
 * @return vector of distances between consecutive points
 */
template<RandomAccessContainerOfLatLonHolders T_latlon_holder_container>
inline auto compute_latlon_distances_m(const T_latlon_holder_container& geolocations_latlon)
{
    std::vector<decltype(T_latlon_holder_container::value_type::latitude)>  latitudes;
    std::vector<decltype(T_latlon_holder_container::value_type::longitude)> longitudes;

    latitudes.reserve(geolocations_latlon.size());
    longitudes.reserve(geolocations_latlon.size());

    std::transform(geolocations_latlon.begin(),
                   geolocations_latlon.end(),
                   std::back_inserter(latitudes),
                   [](const auto& latlon_holder) { return latlon_holder.latitude; });

    std::transform(geolocations_latlon.begin(),
                   geolocations_latlon.end(),
                   std::back_inserter(longitudes),
                   [](const auto& latlon_holder) { return latlon_holder.longitude; });

    return compute_latlon_distances_m(latitudes, longitudes);
}

/**
 * @brief Compute the cumulative distances between consecutive points in the given latitude and
 * longitude holder container
 *
 * @tparam T_latlon_holder_container type of the latitude and longitude holder container
 * @param geolocations_latlon container of latitude and longitude holders
 * @return vector of cumulative distances
 */
template<RandomAccessContainerOfLatLonHolders T_latlon_holder_container>
inline auto cumulative_latlon_distances_m(const T_latlon_holder_container& geolocations_latlon)
{
    std::vector<decltype(T_latlon_holder_container::value_type::latitude)>  latitudes;
    std::vector<decltype(T_latlon_holder_container::value_type::longitude)> longitudes;

    latitudes.reserve(geolocations_latlon.size());
    longitudes.reserve(geolocations_latlon.size());

    std::transform(geolocations_latlon.begin(),
                   geolocations_latlon.end(),
                   std::back_inserter(latitudes),
                   [](const auto& latlon_holder) { return latlon_holder.latitude; });

    std::transform(geolocations_latlon.begin(),
                   geolocations_latlon.end(),
                   std::back_inserter(longitudes),
                   [](const auto& latlon_holder) { return latlon_holder.longitude; });

    return cumulative_latlon_distances_m(latitudes, longitudes);
}

} // namespace navtools
} // namespace navigation
} // namespace themachinethatgoesping
