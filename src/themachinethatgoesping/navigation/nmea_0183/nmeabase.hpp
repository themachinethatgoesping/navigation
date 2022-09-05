// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <string>
#include <charconv>

#include <themachinethatgoesping/tools/classhelpers/objectprinter.hpp>
#include <themachinethatgoesping/tools/classhelpers/stream.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

class NMEABase
{
    protected:
    std::string _sentence;
    std::vector<int> _fields;

  public:
    NMEABase() = default;

    NMEABase(std::string data)
        : _sentence(std::move(data))
    {
        parse_fields();
    }

    // NMEABase(std::string&& data)
    //     : _sentence(std::move(data))
    // {
    //     parse_fields();
    // }

    static NMEABase from_stream(std::istream& is, size_t length)
    {
        NMEABase nmea_sentence;
        nmea_sentence._sentence.resize(length);
        is.read(nmea_sentence._sentence.data(), nmea_sentence._sentence.size());

        return nmea_sentence;
    }

    static NMEABase from_stream(std::istream& is)
    {
        NMEABase nmea_sentence;
        size_t size;
        is.read(reinterpret_cast<char*>(&size), sizeof(size));
        nmea_sentence._sentence.resize(size);
        is.read(nmea_sentence._sentence.data(), nmea_sentence._sentence.size());

        return nmea_sentence;
    }

    void to_stream(std::ostream& os)
    {
        NMEABase nmea_sentence;
        size_t size = nmea_sentence.size();
        os.write(reinterpret_cast<char*>(&size), sizeof(size));
        os.write(nmea_sentence._sentence.data(), nmea_sentence._sentence.size());
    }

    // operators
    bool   operator==(const NMEABase& other) const { return _sentence == other._sentence; }
    bool   operator!=(const NMEABase& other) const { return _sentence != other._sentence; }
    size_t size() const { return _sentence.size(); }


    void parse_fields()
    {
        _fields.clear();
        // find all ',' 
        size_t i = 0;
        for (; i < _sentence.size(); i++)
        {
            if (_sentence[i] == ',')
                _fields.push_back(i);
            if (_sentence[i] == '\x00')
                break;
        }
        _fields.push_back(i);
    };

    std::string_view get_field(size_t index) const
    {
        if (index < _fields.size() - 1)
            return std::string_view(_sentence).substr(_fields[index] + 1, _fields[index + 1] - _fields[index] - 1);
            
        throw std::out_of_range("NMEABase::get_field: index out of range");
    }

    double get_field_as_double(size_t index) const
    {
        return std::stod(std::string(get_field(index)));
    }

    int get_field_as_int(size_t index) const
    {
        return std::stoi(std::string(get_field(index)));
    }


    void to_stream(std::ostream& os) const
    {
        os.write(_sentence.data(), _sentence.size());
    }

    std::string_view get_sender() const
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

    std::string_view get_type() const
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

    std::string_view get_name() const
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

    std::string_view get_sentence() const { return std::string_view(_sentence); }

    // ----- objectprinter -----
    tools::classhelpers::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        tools::classhelpers::ObjectPrinter printer("NMEA sentence", float_precision);

        printer.register_value("Sender", get_sender(), "");
        printer.register_value("Type", get_type(), "");
        printer.register_value("Full sentence", get_sentence(), "");

        return printer;
    }

    // ----- class helper macros -----
    __CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEABase)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
