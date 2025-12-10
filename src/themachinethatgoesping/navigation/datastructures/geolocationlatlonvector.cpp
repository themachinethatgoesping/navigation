// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "geolocationlatlonvector.hpp"

#include <stdexcept>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
GeolocationLatLonVector::GeolocationLatLonVector(size_t capacity)
{
    _timestamps.reserve(capacity);
    _geolocations.reserve(capacity);
}

GeolocationLatLonVector::GeolocationLatLonVector(std::vector<double>            timestamps,
                                                 std::vector<GeolocationLatLon> geolocations)
    : _timestamps(std::move(timestamps))
    , _geolocations(std::move(geolocations))
{
    if (_timestamps.size() != _geolocations.size())
    {
        throw std::invalid_argument(
            "GeolocationLatLonVector: timestamps and geolocations must have the same size");
    }
}

// ----- modifiers -----
void GeolocationLatLonVector::reserve(size_t n)
{
    _timestamps.reserve(n);
    _geolocations.reserve(n);
}

void GeolocationLatLonVector::push_back(double timestamp, const GeolocationLatLon& geolocation)
{
    _timestamps.push_back(timestamp);
    _geolocations.push_back(geolocation);
}

void GeolocationLatLonVector::push_back(double timestamp, GeolocationLatLon&& geolocation)
{
    _timestamps.push_back(timestamp);
    _geolocations.push_back(std::move(geolocation));
}

// ----- component-wise access -----
std::vector<double> GeolocationLatLonVector::get_latitudes() const
{
    std::vector<double> result;
    result.reserve(_geolocations.size());
    for (const auto& geo : _geolocations)
    {
        result.push_back(geo.latitude);
    }
    return result;
}

std::vector<double> GeolocationLatLonVector::get_longitudes() const
{
    std::vector<double> result;
    result.reserve(_geolocations.size());
    for (const auto& geo : _geolocations)
    {
        result.push_back(geo.longitude);
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_z() const
{
    std::vector<float> result;
    result.reserve(_geolocations.size());
    for (const auto& geo : _geolocations)
    {
        result.push_back(geo.z);
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_yaw() const
{
    std::vector<float> result;
    result.reserve(_geolocations.size());
    for (const auto& geo : _geolocations)
    {
        result.push_back(geo.yaw);
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_pitch() const
{
    std::vector<float> result;
    result.reserve(_geolocations.size());
    for (const auto& geo : _geolocations)
    {
        result.push_back(geo.pitch);
    }
    return result;
}

std::vector<float> GeolocationLatLonVector::get_roll() const
{
    std::vector<float> result;
    result.reserve(_geolocations.size());
    for (const auto& geo : _geolocations)
    {
        result.push_back(geo.roll);
    }
    return result;
}

// ----- operators -----
bool GeolocationLatLonVector::operator==(const GeolocationLatLonVector& other) const
{
    return _timestamps == other._timestamps && _geolocations == other._geolocations;
}

// ----- file I/O -----
GeolocationLatLonVector GeolocationLatLonVector::from_stream(std::istream& is)
{
    GeolocationLatLonVector result;

    uint64_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));

    result._timestamps.resize(size);
    result._geolocations.resize(size);

    is.read(reinterpret_cast<char*>(result._timestamps.data()), size * sizeof(double));

    for (size_t i = 0; i < size; ++i)
    {
        result._geolocations[i] = GeolocationLatLon::from_stream(is);
    }

    return result;
}

void GeolocationLatLonVector::to_stream(std::ostream& os) const
{
    uint64_t size = _timestamps.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));

    os.write(reinterpret_cast<const char*>(_timestamps.data()), size * sizeof(double));

    for (const auto& geo : _geolocations)
    {
        geo.to_stream(os);
    }
}

// ----- printer -----
tools::classhelper::ObjectPrinter GeolocationLatLonVector::__printer__(
    unsigned int float_precision,
    bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "GeolocationLatLonVector", float_precision, superscript_exponents);

    printer.register_value("size", _geolocations.size());

    if (!_timestamps.empty())
    {
        printer.register_value("timestamp_min", _timestamps.front(), "s");
        printer.register_value("timestamp_max", _timestamps.back(), "s");
    }

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
