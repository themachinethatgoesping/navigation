// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "nmea_base.hpp"

#include <charconv>
#include <themachinethatgoesping/tools/helper/stringconversion.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

NMEA_Base::NMEA_Base(std::string data)
    : _sentence(std::move(data))
{
    parse_fields();
}

NMEA_Base NMEA_Base::from_stream(std::istream& is, size_t length)
{
    NMEA_Base nmea_base;
    nmea_base._sentence.resize(length);
    is.read(nmea_base._sentence.data(), nmea_base._sentence.size());

    return nmea_base;
}

NMEA_Base NMEA_Base::from_stream(std::istream& is)
{
    NMEA_Base nmea_base;
    size_t    size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    nmea_base._sentence.resize(size);
    is.read(nmea_base._sentence.data(), nmea_base._sentence.size());

    return nmea_base;
}

void NMEA_Base::to_stream(std::ostream& os) const
{
    size_t size = this->size();
    os.write(reinterpret_cast<char*>(&size), sizeof(size));
    os.write(this->_sentence.data(), this->_sentence.size());
}

void NMEA_Base::to_stream_dont_write_size(std::ostream& os) const
{
    os.write(this->_sentence.data(), this->_sentence.size());
}

void NMEA_Base::parse_fields()
{
    _fields.clear();
    // find all ','
    int i = 0;
    for (; i < int(_sentence.size()); i++)
    {
        if (_sentence[i] == ',')
            _fields.push_back(i);
        if (_sentence[i] == '\x00')
            break;
    }
    _fields.push_back(i);
};

std::string_view NMEA_Base::get_field(size_t index) const
{
    if (index < _fields.size() - 1)
        return std::string_view(_sentence).substr(_fields[index] + 1,
                                                  _fields[index + 1] - _fields[index] - 1);

    return "";
}

template<typename t_float>
t_float NMEA_Base::get_field_as_floattype(size_t index) const
{
    return themachinethatgoesping::tools::helper::string_to_floattype<t_float>(
        get_field(index));
}

// Explicit template instantiation for commonly used types
template float NMEA_Base::get_field_as_floattype<float>(size_t index) const;
template double NMEA_Base::get_field_as_floattype<double>(size_t index) const;

int NMEA_Base::get_field_as_int(size_t index) const
{
    try
    {
        return std::stoi(std::string(get_field(index)));
    }
    catch (...)
    {
        return 0;
    }
}

std::string_view NMEA_Base::get_sender_id() const
{
    try
    {
        if (_sentence.at(0) != '$')
            return "invalid";

        return std::string_view(_sentence).substr(1, 2);
    }
    catch (...)
    {
        return "invalid";
    }
}

std::string_view NMEA_Base::get_sentence_type() const
{
    try
    {
        if (_sentence.at(0) != '$')
            return "invalid";

        return std::string_view(_sentence).substr(3, 3);
    }
    catch (...)
    {
        return "invalid";
    }
}

std::string_view NMEA_Base::get_sentence_id() const
{
    try
    {
        if (_sentence.at(0) != '$')
            return "invalid";

        return std::string_view(_sentence).substr(1, 5);
    }
    catch (...)
    {
        return "invalid";
    }
}

tools::classhelper::ObjectPrinter NMEA_Base::__printer__(unsigned int float_precision,
                                                          bool         superscript_exponents) const
{
    tools::classhelper::ObjectPrinter printer(
        "NMEA sentence", float_precision, superscript_exponents);

    printer.register_value("Sender", get_sender_id(), "");
    printer.register_value("Type", get_sentence_type(), "");
    printer.register_value("Full sentence", get_sentence(), "");

    return printer;
}

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping