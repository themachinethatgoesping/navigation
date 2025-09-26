// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
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

#include <xtensor/containers/xadapt.hpp>
#include <xtensor/containers/xcontainer.hpp>

#include <themachinethatgoesping/tools/classhelper/option.hpp>

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

using o_latlon_format = tools::classhelper::Option<t_latlon_format>;

/**
 * @brief c++20 concept to check if a type has latitude and longitude members
 *
 * @tparam T
 */
template<typename T>
concept HasLatitudeLongitude = requires(T t) {
    { t.latitude } -> std::convertible_to<float>;
    { t.longitude } -> std::convertible_to<float>;
};

template<typename T>
concept PairOfFloats = requires(T t) {
    typename T::first_type;
    typename T::second_type;
    requires std::floating_point<typename T::first_type>;
    requires std::floating_point<typename T::second_type>;
};

template<typename T>
concept RandomAccessContainerOfFloats = requires(T t) {
    typename T::value_type;
    requires std::random_access_iterator<typename T::iterator>;
    requires std::floating_point<typename T::value_type>;
};

template<typename T>
concept RandomAccessContainerOfDoubles = requires(T t) {
    typename T::value_type;
    requires std::random_access_iterator<typename T::iterator>;
    requires std::convertible_to<typename T::value_type, double>;
};

template<typename T>
concept RandomAccessContainerOfInts = requires(T t) {
    typename T::value_type;
    requires std::random_access_iterator<typename T::iterator>;
    requires std::convertible_to<typename T::value_type, int>;
};

template<typename T>
concept RandomAccessContainerOfLatLonHolders = requires(T t) {
    typename T::value_type;
    requires std::random_access_iterator<typename T::iterator>;
    requires HasLatitudeLongitude<typename T::value_type> || PairOfFloats<typename T::value_type>;
};

inline std::string dms_to_string(double          dms_value,
                                 o_latlon_format format,
                                 size_t          precision,
                                 char            sign)
{
    dms_value = std::abs(dms_value);

    switch (format.value)
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
                                      o_latlon_format format    = t_latlon_format::minutes,
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
                                       o_latlon_format format    = t_latlon_format::minutes,
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
template<RandomAccessContainerOfDoubles T_container>
inline std::pair<T_container, T_container> utm_to_latlon(const T_container& northing,
                                                         const T_container& easting,
                                                         int                zone,
                                                         bool               northern_hemisphere,
                                                         int                mp_cores = 1)
{
    // check if vector sizes are the same
    if (easting.size() != northing.size())
        throw std::runtime_error(
            "ERROR[utm_to_latlon]: easting and northing vector sizes are not the same!");

    // initialize output vectors
    T_container lat, lon;
    // Check if container is xtensor and handle resize accordingly
    if constexpr (std::is_base_of<xt::xcontainer<T_container>, T_container>::value)
    {
        lat = T_container::from_shape({ static_cast<size_t>(northing.size()) });
        lon = T_container::from_shape({ static_cast<size_t>(northing.size()) });
    }
    else
    {
        lat.resize(northing.size());
        lon.resize(northing.size());
    }

    // loop through data and convert using GeographicLib
#pragma omp parallel for num_threads(mp_cores)
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
template<RandomAccessContainerOfDoubles T_container_double,
         RandomAccessContainerOfInts    T_container_int>
inline std::pair<T_container_double, T_container_double> utm_to_latlon(
    const T_container_double& northing,
    const T_container_double& easting,
    const T_container_int&    zone,
    const T_container_int&    northern_hemisphere,
    int                       mp_cores = 1)
{
    // check if vector sizes are the same
    if (easting.size() != northing.size() && easting.size() != zone.size() &&
        easting.size() != northern_hemisphere.size())
        throw std::runtime_error("ERROR[utm_to_latlon]: easting, northing, zone and "
                                 "northern_hemisphere vector sizes are not the same!");

    // initialize output vectors
    T_container_double lat, lon;
    // Check if container is xtensor and handle resize accordingly
    if constexpr (std::is_base_of<xt::xcontainer<T_container_double>, T_container_double>::value)
    {
        lat = T_container_double::from_shape({ static_cast<size_t>(northing.size()) });
        lon = T_container_double::from_shape({ static_cast<size_t>(northing.size()) });
    }
    else
    {
        lat.resize(northing.size());
        lon.resize(northing.size());
    }

// loop through data and convert using GeographicLib
#pragma omp parallel for num_threads(mp_cores)
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
template<RandomAccessContainerOfDoubles T_container_double>
inline std::tuple<T_container_double, T_container_double, int, bool> latlon_to_utm(
    const T_container_double& lat,
    const T_container_double& lon,
    int                       setzone  = -1,
    int                       mp_cores = 1)
{
    // check if vector sizes are the same
    if (lat.size() != lon.size())
        throw std::runtime_error(
            "ERROR[latlon_to_utm]: lat and lon vector sizes are not the same!");

    // determine setzone using mean of latitudes and longitudes
    if (setzone == -1)
    {
        double mean_lat, mean_lon;
        if constexpr (std::is_base_of<xt::xcontainer<T_container_double>,
                                      T_container_double>::value)
        {
            mean_lat = xt::mean(lat)();
            mean_lon = xt::mean(lon)();
        }
        else
        {
            auto lat_xt = xt::adapt(lat.data(), xt::no_ownership());
            auto lon_xt = xt::adapt(lon.data(), xt::no_ownership());
            mean_lat    = xt::mean(lat_xt)();
            mean_lon    = xt::mean(lon_xt)();
        }
        setzone = GeographicLib::UTMUPS::StandardZone(mean_lat, mean_lon);
    }

    // initialize output data
    T_container_double northing, easting;
    // Check if container is xtensor and handle resize accordingly
    if constexpr (std::is_base_of<xt::xcontainer<T_container_double>, T_container_double>::value)
    {
        northing = T_container_double::from_shape({ static_cast<size_t>(lat.size()) });
        easting  = T_container_double::from_shape({ static_cast<size_t>(lat.size()) });
    }
    else
    {
        northing.resize(lat.size());
        northing.resize(lat.size());
    }

    int  zone;
    bool northern_hemisphere;

// loop through data and convert using GeographicLib
#pragma omp parallel for num_threads(mp_cores)
    for (size_t i = 0; i < lat.size(); i++)
    {
        GeographicLib::UTMUPS::Forward(
            lat[i], lon[i], zone, northern_hemisphere, easting[i], northing[i], setzone);
    }
    return std::make_tuple(northing, easting, zone, northern_hemisphere);
}

/**
 * @brief Compute the distance in meters between two latitude-longitude coordinates using the WGS84
 * ellipsoid.
 *
 * @tparam T_float Floating-point type for latitude and longitude values.
 * @param lat1 Latitude of the first coordinate.
 * @param lon1 Longitude of the first coordinate.
 * @param lat2 Latitude of the second coordinate.
 * @param lon2 Longitude of the second coordinate.
 * @return Distance between the two coordinates in meters.
 */
template<std::floating_point T_float>
double compute_latlon_distance_m(T_float lat1, T_float lon1, T_float lat2, T_float lon2)
{
    GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                 GeographicLib::Constants::WGS84_f());
    double                  s12;
    geod.Inverse(lat1, lon1, lat2, lon2, s12);
    return s12;
}

/**
 * @brief Compute the distance in meters between two latitude-longitude coordinates using the WGS84
 * ellipsoid.
 *
 * @tparam T_latlon_holder Type that holds latitude and longitude values.
 * @param geolocation_latlon_1 First latitude-longitude coordinate.
 * @param geolocation_latlon_2 Second latitude-longitude coordinate.
 * @return Distance between the two coordinates in meters.
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
 * @brief Compute the distance in meters between two latitude-longitude coordinates using the WGS84
 * ellipsoid.
 *
 * @tparam T_latlon_holder Type that holds latitude and longitude values as a pair of floats.
 * @param geolocation_latlon_1 First latitude-longitude coordinate.
 * @param geolocation_latlon_2 Second latitude-longitude coordinate.
 * @return Distance between the two coordinates in meters.
 */
template<PairOfFloats T_latlon_holder>
inline auto compute_latlon_distance_m(const T_latlon_holder& geolocation_latlon_1,
                                      const T_latlon_holder& geolocation_latlon_2)
{
    return compute_latlon_distance_m(geolocation_latlon_1.first,
                                     geolocation_latlon_1.second,
                                     geolocation_latlon_2.first,
                                     geolocation_latlon_2.second);
}

/**
 * @brief Compute the distances in meters between consecutive latitude-longitude coordinates using
 * the WGS84 ellipsoid.
 *
 * @tparam T_return_container Type of container to store the distances.
 * @tparam T_float_container Type of container that holds latitude and longitude values as floats.
 * @param latitudes Vector of latitude values.
 * @param longitudes Vector of longitude values.
 * @return Vector of distances between consecutive coordinates in meters.
 */
template<RandomAccessContainerOfDoubles T_return_container,
         RandomAccessContainerOfFloats  T_float_container>
T_return_container compute_latlon_distances_m(const T_float_container& latitudes,
                                              const T_float_container& longitudes)
{
    if (latitudes.size() != longitudes.size())
        throw std::runtime_error(
            "ERROR[distance]: latitudes and longitudes vector sizes are not the same!");

    if (latitudes.size() < 2)
        throw std::runtime_error(
            "ERROR[distance]: latitudes and longitudes vector sizes are too small! (<2)");

    T_return_container distances;

    // if the container is an xtensor container, we need to resize it using a tuple
    // else we assume it is a std::vector
    if constexpr (std::is_base_of<xt::xcontainer<T_return_container>, T_return_container>::value)
        distances = T_return_container::from_shape({ static_cast<size_t>(latitudes.size() - 1) });
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
 * @brief Compute the distances in meters between consecutive latitude-longitude coordinates using
 * the WGS84 ellipsoid.
 *
 * @tparam T_return_container Type of container to store the distances.
 * @tparam T_container Type of container that holds latitude and longitude values as a latlon holder
 * type.
 * @param geo_locations_latlon Vector of latitude-longitude coordinates.
 * @return Vector of distances between consecutive coordinates in meters.
 */
template<RandomAccessContainerOfDoubles       T_return_container,
         RandomAccessContainerOfLatLonHolders T_container>
T_return_container compute_latlon_distances_m(const T_container& geo_locations_latlon)
{
    if (geo_locations_latlon.size() < 2)
        throw std::runtime_error(
            "ERROR[distance]: geo_locations_latlon vector size is too small! (<2)");

    T_return_container distances;

    // if the container is an xtensor container, we need to resize it using a tuple
    // else we assume it is a std::vector
    if constexpr (std::is_base_of<xt::xcontainer<T_return_container>, T_return_container>::value)
        distances = T_return_container::from_shape({ static_cast<size_t>(geo_locations_latlon.size() - 1) });
    else
        distances.resize(geo_locations_latlon.size() - 1);

    GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                 GeographicLib::Constants::WGS84_f());

    for (size_t i = 0; i < geo_locations_latlon.size() - 1; i++)
    {
        const auto& loc0 = geo_locations_latlon[i];
        const auto& loc1 = geo_locations_latlon[i + 1];

        if constexpr (PairOfFloats<typename T_container::value_type>)
        {
            geod.Inverse(loc0.first, loc0.second, loc1.first, loc1.second, distances[i]);
        }
        else // if constexpr (HasLatitudeLongitude<typename T_container::value_type>)
        {
            geod.Inverse(
                loc0.latitude, loc0.longitude, loc1.latitude, loc1.longitude, distances[i]);
        }
    }

    return distances;
}

/**
 * @brief Compute the cumulative distances in meters between consecutive latitude-longitude
 * coordinates using the WGS84 ellipsoid.
 *
 * @tparam T_return_container Type of container to store the distances.
 * @tparam T_float_container Type of container that holds latitude and longitude values as floats.
 * @param latitudes Vector of latitude values.
 * @param longitudes Vector of longitude values.
 * @return Vector of cumulative distances between consecutive coordinates in meters.
 */
template<RandomAccessContainerOfDoubles T_return_container,
         RandomAccessContainerOfFloats  T_float_container>
T_return_container cumulative_latlon_distances_m(const T_float_container& latitudes,
                                                 const T_float_container& longitudes)
{
    if (latitudes.size() != longitudes.size())
        throw std::runtime_error(
            "ERROR[distance]: latitudes and longitudes vector sizes are not the same!");

    if (latitudes.size() < 2)
        throw std::runtime_error(
            "ERROR[distance]: latitudes and longitudes vector sizes are too small! (<2)");

    T_return_container distances;

    // if the container is an xtensor container, we need to resize it using a tuple
    // else we assume it is a std::vector
    if constexpr (std::is_base_of<xt::xcontainer<T_return_container>, T_return_container>::value)
        distances = T_return_container::from_shape({ static_cast<size_t>(latitudes.size()) });
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
 * @brief Compute the cumulative distances in meters between consecutive latitude-longitude
 * coordinates using the WGS84 ellipsoid.
 *
 * @tparam T_return_container Type of container to store the distances.
 * @tparam T_container Type of container that holds latitude and longitude values as a latlon holder
 * type.
 * @param geo_locations_latlon Vector of latitude-longitude coordinates.
 * @return Vector of cumulative distances between consecutive coordinates in meters.
 */
template<RandomAccessContainerOfDoubles       T_return_container,
         RandomAccessContainerOfLatLonHolders T_container>
T_return_container cumulative_latlon_distances_m(const T_container& geo_locations_latlon)
{
    if (geo_locations_latlon.size() < 2)
        throw std::runtime_error(
            "ERROR[distance]: geo_locations_latlon vector size is too small! (<2)");

    T_return_container distances;

    // if the container is an xtensor container, we need to resize it using a tuple
    // else we assume it is a std::vector
    if constexpr (std::is_base_of<xt::xcontainer<T_return_container>, T_return_container>::value)
        distances = T_return_container::from_shape({ static_cast<size_t>(geo_locations_latlon.size()) });
    else
        distances.resize(geo_locations_latlon.size());

    GeographicLib::Geodesic geod(GeographicLib::Constants::WGS84_a(),
                                 GeographicLib::Constants::WGS84_f());

    distances[0] = 0;
    for (size_t i = 1; i < geo_locations_latlon.size(); i++)
    {
        const auto& loc0 = geo_locations_latlon[i - 1];
        const auto& loc1 = geo_locations_latlon[i];

        if constexpr (PairOfFloats<typename T_container::value_type>)
        {
            geod.Inverse(loc0.first, loc0.second, loc1.first, loc1.second, distances[i]);
        }
        else // if constexpr (HasLatitudeLongitude<typename T_container::value_type>)
        {
            geod.Inverse(
                loc0.latitude, loc0.longitude, loc1.latitude, loc1.longitude, distances[i]);
        }

        distances[i] += distances[i - 1];
    }

    return distances;
}

} // namespace navtools
} // namespace navigation
} // namespace themachinethatgoesping

extern template class themachinethatgoesping::tools::classhelper::Option<
    themachinethatgoesping::navigation::navtools::t_latlon_format>;