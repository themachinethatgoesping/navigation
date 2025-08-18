// Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "sensordatalocal.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// Constructor implementations
SensordataLocal::SensordataLocal(Sensordata data, double northing, double easting)
    : Sensordata(std::move(data))
    , northing(northing)
    , easting(easting)
{
}

SensordataLocal::SensordataLocal(double northing,
                                 double easting,
                                 float depth,
                                 float heave,
                                 float heading,
                                 float pitch,
                                 float roll)
    : Sensordata(depth, heave, heading, pitch, roll)
    , northing(northing)
    , easting(easting)
{
}

// Operator implementations
bool SensordataLocal::operator!=(const SensordataLocal& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool SensordataLocal::operator==(const SensordataLocal& rhs) const
{
    if (Sensordata::operator==(rhs))
        if (tools::helper::approx(northing, rhs.northing))
            if (tools::helper::approx(easting, rhs.easting))
                return true;

    return false;
}

// I/O implementations
SensordataLocal SensordataLocal::from_stream(std::istream& is)
{
    SensordataLocal data(Sensordata::from_stream(is), 0., 0.);

    is.read(reinterpret_cast<char*>(&data.northing), 2 * sizeof(double));

    return data;
}

void SensordataLocal::to_stream(std::ostream& os) const
{
    Sensordata::to_stream(os);
    os.write(reinterpret_cast<const char*>(&northing), 2 * sizeof(double));
}

// Printer implementation
tools::classhelper::ObjectPrinter SensordataLocal::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("SensordataLocal (struct)", float_precision, superscript_exponents);

    printer.register_value("northing", northing, "positive northwards, m");
    printer.register_value("easting", easting, "positive eastwards, m");

    printer.append(Sensordata::__printer__(float_precision, superscript_exponents));

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping