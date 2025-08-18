// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge GEOMAR Helmholtz
// Centre for Ocean Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban,
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "positionaloffsets.hpp"

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>
#include <themachinethatgoesping/tools/helper/approx.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// Constructor implementations
PositionalOffsets::PositionalOffsets(std::string_view name,
                                     float            x,
                                     float            y,
                                     float            z,
                                     float            yaw,
                                     float            pitch,
                                     float            roll)
    : name(std::string(name))
    , x(x)
    , y(y)
    , z(z)
    , yaw(yaw)
    , pitch(pitch)
    , roll(roll)
{
}

// Static method implementations
PositionalOffsets PositionalOffsets::from_txrx(const PositionalOffsets& tx,
                                               const PositionalOffsets& rx,
                                               std::string              name)
{
    PositionalOffsets trx;

    trx.name = std::move(name);

    /* x,y,z are the average of tx and rx */
    //trx.x = (tx.x + rx.x) * 0.5;
    //trx.y = (tx.y + rx.y) * 0.5;
    trx.z = (tx.z + rx.z) * 0.5;

    /* x and y are the transducer receiver values*/
    trx.y = rx.y;
    trx.x = tx.y;

    /* take pitch and yaw from tx and roll from rx*/
    trx.pitch = tx.pitch;
    trx.yaw   = tx.yaw; // not sure about this one ...
    trx.roll  = rx.roll;

    return trx;
}

// Operator implementations
bool PositionalOffsets::operator!=(const PositionalOffsets& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool PositionalOffsets::operator==(const PositionalOffsets& rhs) const
{
    if (name == rhs.name)
        if (tools::helper::approx(x, rhs.x))
            if (tools::helper::approx(y, rhs.y))
                if (tools::helper::approx(z, rhs.z))
                    if (tools::helper::approx(yaw, rhs.yaw))
                        if (tools::helper::approx(pitch, rhs.pitch))
                            if (tools::helper::approx(roll, rhs.roll))
                                return true;

    return false;
}

// I/O implementations
PositionalOffsets PositionalOffsets::from_stream(std::istream& is)
{
    PositionalOffsets data;

    data.name = tools::classhelper::stream::container_from_stream<std::string>(is);

    is.read(reinterpret_cast<char*>(&data.x), 6 * sizeof(float));

    return data;
}

void PositionalOffsets::to_stream(std::ostream& os) const
{
    tools::classhelper::stream::container_to_stream(os, name);

    os.write(reinterpret_cast<const char*>(&x), 6 * sizeof(float));
}

// Printer implementation
tools::classhelper::ObjectPrinter PositionalOffsets::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("PositionalOffsets (struct)", float_precision, superscript_exponents);

    printer.register_string("name", name, "The name of the sensor");
    printer.register_value("x", x, "positive forwards, m");
    printer.register_value("y", y, "positive starboard, m");
    printer.register_value("z", z, "positive downwards, m");
    printer.register_value("yaw", yaw, "° positive means clockwise rotation");
    printer.register_value("pitch", pitch, "° positive means bow up");
    printer.register_value("roll", roll, "° positive means port up");

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping