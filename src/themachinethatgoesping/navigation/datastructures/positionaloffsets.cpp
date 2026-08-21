// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "positionaloffsets.hpp"

#include <themachinethatgoesping/tools/helper/approx.hpp>
#include <themachinethatgoesping/tools/classhelper/stream.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

// ----- constructors -----
SensorPose::SensorPose(std::string_view name,
                                   float            x,
                                   float            y,
                                   float            z,
                                   float            yaw,
                                   float            pitch,
                                   float            roll,
                                   bool             ypr_offsets_applied)
    : name(std::string(name))
    , x(x)
    , y(y)
    , z(z)
    , rotation(yaw, pitch, roll)
    , ypr_offsets_applied(ypr_offsets_applied)
{
}

SensorPose::SensorPose(std::string_view                          name,
                                     float                                     x,
                                     float                                     y,
                                     float                                     z,
                                     tools::rotationfunctions::Rotation<float> rotation,
                                     bool                                      ypr_offsets_applied)
    : name(std::string(name))
    , x(x)
    , y(y)
    , z(z)
    , rotation(rotation)
    , ypr_offsets_applied(ypr_offsets_applied)
{
}

// ----- yaw/pitch/roll accessors -----
float SensorPose::yaw() const { return rotation.ypr()[0]; }
float SensorPose::pitch() const { return rotation.ypr()[1]; }
float SensorPose::roll() const { return rotation.ypr()[2]; }

bool SensorPose::has_zero_rotation() const
{
    // the identity quaternion has a zero imaginary (vector) part
    return rotation.vec().squaredNorm() <= 1e-9f;
}

void SensorPose::set_ypr(float yaw, float pitch, float roll)
{
    rotation = tools::rotationfunctions::Rotation<float>(yaw, pitch, roll);
}
void SensorPose::set_yaw(float yaw)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(yaw, ypr[1], ypr[2]);
}
void SensorPose::set_pitch(float pitch)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(ypr[0], pitch, ypr[2]);
}
void SensorPose::set_roll(float roll)
{
    const auto ypr = rotation.ypr();
    rotation       = tools::rotationfunctions::Rotation<float>(ypr[0], ypr[1], roll);
}

// ----- static functions -----
SensorPose SensorPose::from_txrx(const SensorPose& tx,
                                               const SensorPose& rx,
                                               std::string              name)
{
    SensorPose trx;

    trx.name = std::move(name);

    /* x,y,z are the average of tx and rx */
    //trx.x = (tx.x + rx.x) * 0.5;
    //trx.y = (tx.y + rx.y) * 0.5;
    trx.z = (tx.z + rx.z) * 0.5;

    /* x is taken from the transmitter, y from the receiver */
    trx.y = rx.y;
    trx.x = tx.x;

    /* take pitch and yaw from tx and roll from rx*/
    trx.set_ypr(tx.yaw(), tx.pitch(), rx.roll());

    return trx;
}

// ----- operators -----
bool SensorPose::operator!=(const SensorPose& rhs) const 
{ 
    return !(operator==(rhs)); 
}

bool SensorPose::operator==(const SensorPose& rhs) const
{
    using tools::helper::approx;
    return name == rhs.name && approx(x, rhs.x) && approx(y, rhs.y) && approx(z, rhs.z) &&
           rotation == rhs.rotation && ypr_offsets_applied == rhs.ypr_offsets_applied;
}

// ----- file I/O -----
SensorPose SensorPose::from_stream(std::istream& is)
{
    SensorPose data;

    data.name = tools::classhelper::stream::container_from_stream<std::string>(is);

    is.read(reinterpret_cast<char*>(&data.x), 3 * sizeof(float));
    data.rotation = tools::rotationfunctions::Rotation<float>::from_stream(is);
    is.read(reinterpret_cast<char*>(&data.ypr_offsets_applied), sizeof(bool));

    return data;
}

void SensorPose::to_stream(std::ostream& os) const
{
    tools::classhelper::stream::container_to_stream(os, name);

    os.write(reinterpret_cast<const char*>(&x), 3 * sizeof(float));
    rotation.to_stream(os);
    os.write(reinterpret_cast<const char*>(&ypr_offsets_applied), sizeof(bool));
}

// ----- printer -----
tools::classhelper::ObjectPrinter SensorPose::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer("SensorPose (struct)", float_precision, superscript_exponents);

    printer.register_string("name", name, "The name of the sensor");
    printer.register_value("x", x, "positive forwards, m");
    printer.register_value("y", y, "positive starboard, m");
    printer.register_value("z", z, "positive downwards, m");
    const auto ypr = rotation.ypr();
    printer.register_value("yaw", ypr[0], "° positive means clockwise rotation");
    printer.register_value("pitch", ypr[1], "° positive means bow up");
    printer.register_value("roll", ypr[2], "° positive means port up");
    printer.register_value(
        "ypr_offsets_applied", ypr_offsets_applied, "yaw/pitch/roll already applied to sensor data");

    return printer;
}

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping