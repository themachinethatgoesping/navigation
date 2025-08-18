// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatautm.hpp"

#include <GeographicLib/UTMUPS.hpp>

#include "sensordatalatlon.hpp"

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
SensordataUTM::SensordataUTM(Sensordata data,
                            double     northing,
                            double     easting,
                            int        utm_zone,
                            bool       northern_hemisphere)
    : SensordataLocal(std::move(data), northing, easting)
    , utm_zone(utm_zone)
    , northern_hemisphere(northern_hemisphere)
{
}

SensordataUTM::SensordataUTM(SensordataLocal data_local, int utm_zone, bool northern_hemisphere)
    : SensordataLocal(std::move(data_local))
    , utm_zone(utm_zone)
    , northern_hemisphere(northern_hemisphere)
{
}

SensordataUTM::SensordataUTM(const SensordataLatLon& data, int setzone)
    : SensordataUTM(from_sensordata(data, setzone))
{
}

SensordataUTM::SensordataUTM(double northing,
                            double easting,
                            int    utm_zone,
                            bool   northern_hemisphere,
                            float  depth,
                            float  heave,
                            float  heading,
                            float  pitch,
                            float  roll)
    : SensordataLocal(northing, easting, depth, heave, heading, pitch, roll)
    , utm_zone(utm_zone)
    , northern_hemisphere(northern_hemisphere)
{
}

// ----- operators -----
bool SensordataUTM::operator!=(const SensordataUTM& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool SensordataUTM::operator==(const SensordataUTM& rhs) const
{
    if (SensordataLocal::operator==(rhs))
        if (utm_zone == rhs.utm_zone)
            if (northern_hemisphere == rhs.northern_hemisphere)
                return true;

    return false;
}

// ----- static conversion functions -----
SensordataLatLon SensordataUTM::to_sensordata(const SensordataUTM& data_utm)
{
    SensordataLatLon data(
        0, 0, data_utm.depth, data_utm.heave, data_utm.heading, data_utm.pitch, data_utm.roll);

    GeographicLib::UTMUPS::Reverse(data_utm.utm_zone,
                                   data_utm.northern_hemisphere,
                                   data_utm.easting,
                                   data_utm.northing,
                                   data.latitude,
                                   data.longitude);

    return data;
}

SensordataUTM SensordataUTM::from_sensordata(const SensordataLatLon& data, int setzone)
{
    SensordataUTM data_utm(
        0, 0, 0, 0, data.depth, data.heave, data.heading, data.pitch, data.roll);

    GeographicLib::UTMUPS::Forward(data.latitude,
                                   data.longitude,
                                   data_utm.utm_zone,
                                   data_utm.northern_hemisphere,
                                   data_utm.easting,
                                   data_utm.northing,
                                   setzone);

    return data_utm;
}

// ----- file I/O -----
SensordataUTM SensordataUTM::from_stream(std::istream& is)
{
    SensordataUTM data(SensordataLocal::from_stream(is), 0, 0);

    is.read(reinterpret_cast<char*>(&data.utm_zone), sizeof(int));
    is.read(reinterpret_cast<char*>(&data.northern_hemisphere), sizeof(bool));

    return data;
}

void SensordataUTM::to_stream(std::ostream& os) const
{
    SensordataLocal::to_stream(os);

    os.write(reinterpret_cast<const char*>(&utm_zone), sizeof(int));
    os.write(reinterpret_cast<const char*>(&northern_hemisphere), sizeof(bool));
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensordataUTM::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("SensordataUTM (struct)", float_precision, superscript_exponents);

    auto base_printer = SensordataLocal::__printer__(float_precision, superscript_exponents);
    base_printer.remove_sections();
    printer.append(base_printer);
    printer.register_value("utm_zone", utm_zone, "", 2);
    printer.register_value("northern_hemisphere", northern_hemisphere, "", 3);

    return printer;
}



} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping