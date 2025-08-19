// SPDX-FileCopyrightText: 2022 Peter Urban, Tim Weiß, GEOMAR Helmholtz Centre for Ocean
// Research Kiel SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/nmea_base.doc.hpp"

#include <string>
#include <vector>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace nmea_0183 {

class NMEA_Base
{
  protected:
    std::string      _sentence;
    std::vector<int> _fields;

  public:
    NMEA_Base() = default;
    NMEA_Base(std::string data);

    static NMEA_Base from_stream(std::istream& is, size_t length);
    static NMEA_Base from_stream(std::istream& is);

    void to_stream(std::ostream& os) const;
    void to_stream_dont_write_size(std::ostream& os) const;

    // operators
    bool   operator==(const NMEA_Base& other) const { return _sentence == other._sentence; }
    bool   operator!=(const NMEA_Base& other) const { return _sentence != other._sentence; }
    size_t size() const { return _sentence.size(); }

    void parse_fields();
    std::string_view get_field(size_t index) const;

    template<typename t_float>
    t_float get_field_as_floattype(size_t index) const;

    int get_field_as_int(size_t index) const;
    std::string_view get_sender_id() const;
    std::string_view get_sentence_type() const;
    std::string_view get_sentence_id() const;

    std::string_view get_sentence() const { return std::string_view(_sentence); }

    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const;

    // ----- class helper macros -----
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NMEA_Base)
};

} // nmea_0183
} // namespace navigation
} // namespace themachinethatgoesping
