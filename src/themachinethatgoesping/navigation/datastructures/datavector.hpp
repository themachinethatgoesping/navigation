// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/datavector.doc.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

#include <themachinethatgoesping/tools/classhelper/objectprinter.hpp>

namespace themachinethatgoesping {
namespace navigation {
namespace datastructures {

/**
 * @brief A base template class to store a vector of data elements with timestamps.
 * Provides direct access to internal vectors via const and non-const references.
 *
 * @tparam T_DataType The type of data elements stored (e.g., Geolocation, Sensordata)
 * @tparam T_Derived The derived class type (for CRTP pattern)
 */
template<typename T_DataType, typename T_Derived>
class DataVector
{
  protected:
    std::vector<double>     _timestamps; ///< timestamps in seconds since epoch
    std::vector<T_DataType> _data;       ///< data elements

  public:
    using value_type = T_DataType;

    /**
     * @brief Construct an empty DataVector
     */
    DataVector() = default;

    /**
     * @brief Construct a DataVector with pre-allocated capacity
     * @param capacity number of elements to reserve
     */
    explicit DataVector(size_t capacity)
    {
        _timestamps.reserve(capacity);
        _data.reserve(capacity);
    }

    /**
     * @brief Construct a DataVector from existing data
     * @param timestamps vector of timestamps
     * @param data vector of data elements (must be same size as timestamps)
     */
    DataVector(std::vector<double> timestamps, std::vector<T_DataType> data)
        : _timestamps(std::move(timestamps))
        , _data(std::move(data))
    {
        if (_timestamps.size() != _data.size())
        {
            throw std::invalid_argument(
                "DataVector: timestamps and data must have the same size");
        }
    }

    virtual ~DataVector() = default;

    // ----- element access -----
    /**
     * @brief Get the number of elements
     * @return size_t number of elements stored
     */
    size_t size() const { return _data.size(); }

    /**
     * @brief Check if the vector is empty
     * @return true if no elements are stored
     */
    bool empty() const { return _data.empty(); }

    /**
     * @brief Reserve capacity for n elements
     * @param n number of elements to reserve space for
     */
    void reserve(size_t n)
    {
        _timestamps.reserve(n);
        _data.reserve(n);
    }

    /**
     * @brief Clear all elements
     */
    void clear()
    {
        _timestamps.clear();
        _data.clear();
    }

    /**
     * @brief Resize the vectors
     * @param n new size
     */
    void resize(size_t n)
    {
        _timestamps.resize(n);
        _data.resize(n);
    }

    /**
     * @brief Get data element at index
     * @param index position in the vector
     * @return const reference to data element
     */
    const T_DataType& at(size_t index) const { return _data.at(index); }

    /**
     * @brief Get data element at index (non-const)
     * @param index position in the vector
     * @return reference to data element
     */
    T_DataType& at(size_t index) { return _data.at(index); }

    /**
     * @brief Get timestamp at index
     * @param index position in the vector
     * @return timestamp value
     */
    double timestamp_at(size_t index) const { return _timestamps.at(index); }

    // ----- direct access to internal vectors (const) -----
    /**
     * @brief Get const reference to timestamps vector
     * @return const reference to timestamps
     */
    const std::vector<double>& get_timestamps() const { return _timestamps; }

    /**
     * @brief Get const reference to data vector
     * @return const reference to data elements
     */
    const std::vector<T_DataType>& get_data() const { return _data; }

    // ----- direct access to internal vectors (non-const) -----
    /**
     * @brief Get non-const reference to timestamps vector
     * @return reference to timestamps
     */
    std::vector<double>& timestamps() { return _timestamps; }

    /**
     * @brief Get non-const reference to data vector
     * @return reference to data elements
     */
    std::vector<T_DataType>& data() { return _data; }

    // ----- operators -----
    bool operator==(const DataVector& other) const
    {
        return _timestamps == other._timestamps && _data == other._data;
    }

    bool operator!=(const DataVector& other) const { return !(*this == other); }

    // ----- file I/O helpers -----
  protected:
    /**
     * @brief Read base data from stream (for derived class from_stream)
     */
    void read_from_stream(std::istream& is)
    {
        uint64_t size;
        is.read(reinterpret_cast<char*>(&size), sizeof(size));

        _timestamps.resize(size);
        _data.resize(size);

        is.read(reinterpret_cast<char*>(_timestamps.data()), size * sizeof(double));

        for (size_t i = 0; i < size; ++i)
        {
            _data[i] = T_DataType::from_stream(is);
        }
    }

    /**
     * @brief Write base data to stream (for derived class to_stream)
     */
    void write_to_stream(std::ostream& os) const
    {
        uint64_t size = _timestamps.size();
        os.write(reinterpret_cast<const char*>(&size), sizeof(size));

        os.write(reinterpret_cast<const char*>(_timestamps.data()), size * sizeof(double));

        for (const auto& d : _data)
        {
            d.to_stream(os);
        }
    }

    /**
     * @brief Helper for derived class printer
     */
    void add_base_info_to_printer(tools::classhelper::ObjectPrinter& printer) const
    {
        printer.register_value("size", _data.size());

        if (!_timestamps.empty())
        {
            printer.register_value("timestamp_min", _timestamps.front(), "s");
            printer.register_value("timestamp_max", _timestamps.back(), "s");
        }
    }
};

} // namespace datastructures
} // namespace navigation
} // namespace themachinethatgoesping
