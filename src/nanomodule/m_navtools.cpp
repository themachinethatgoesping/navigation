// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers

#include <themachinethatgoesping/navigation/datastructures.hpp>
#include <themachinethatgoesping/navigation/navtools.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/pair.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/tuple.h>

#include <themachinethatgoesping/tools_nanobind/nanobind_xtensor.hpp> // Numpy bindings
// #include <themachinethatgoesping/tools_nanobind/xtensor-python/pytensor.hpp>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation::navtools;
using namespace themachinethatgoesping::navigation;
using namespace themachinethatgoesping;

template<std::floating_point T_float>
void create_distance_functions(nb::module_& m_navtools)
{
    m_navtools.def("compute_latlon_distance_m",
                   &compute_latlon_distance_m<T_float>,
                   DOC(themachinethatgoesping, navigation, navtools, compute_latlon_distance_m),
                   nb::arg("lat1"),
                   nb::arg("lon1"),
                   nb::arg("lat2"),
                   nb::arg("lon2"));

    m_navtools.def("compute_latlon_distances_m",
                   &compute_latlon_distances_m<xt::xtensor<double, 1>, xt::xtensor<T_float, 1>>,
                   DOC(themachinethatgoesping, navigation, navtools, compute_latlon_distances_m),
                   nb::arg("latitudes"),
                   nb::arg("longitudes"));

    m_navtools.def("cumulative_latlon_distances_m",
                   &cumulative_latlon_distances_m<xt::xtensor<double, 1>, xt::xtensor<T_float, 1>>,
                   DOC(themachinethatgoesping, navigation, navtools, cumulative_latlon_distances_m),
                   nb::arg("latitudes"),
                   nb::arg("longitudes"));
}

template<typename T_LLHolder>
void create_distance_functions(nb::module_& m_navtools)
{
    m_navtools.def("compute_latlon_distance_m",
                   &compute_latlon_distance_m<T_LLHolder>,
                   DOC(themachinethatgoesping, navigation, navtools, compute_latlon_distance_m),
                   nb::arg("geolocation_latlon_1"),
                   nb::arg("geolocation_latlon_2"));

    m_navtools.def("compute_latlon_distances_m",
                   &compute_latlon_distances_m<xt::xtensor<double, 1>, std::vector<T_LLHolder>>,
                   DOC(themachinethatgoesping, navigation, navtools, compute_latlon_distances_m),
                   nb::arg("geolocations_latlon"));

    m_navtools.def("cumulative_latlon_distances_m",
                   &cumulative_latlon_distances_m<xt::xtensor<double, 1>, std::vector<T_LLHolder>>,
                   DOC(themachinethatgoesping, navigation, navtools, cumulative_latlon_distances_m),
                   nb::arg("geolocations_latlon"));
}

// template<size_t Dim>
// std::array<std::size_t, Dim> shape_from(const auto& arr)
// {
//     std::array<std::size_t, Dim> s;
//     for (std::size_t i = 0; i < Dim; ++i)
//         s[i] = arr.shape(i);
//     return s;
// }

// template<typename t_value, size_t Dim>
// std::array<std::size_t, Dim> strides_from(const auto& arr)
// {
//     std::array<std::size_t, Dim> s;
//     for (std::size_t i = 0; i < Dim; ++i)
//         // nanobind exposes strides in bytes, xtensor wants strides in elements
//         s[i] = arr.stride(i) / sizeof(t_value);
//     return s;
// }

// template<typename t_value, size_t dim>
// using ndarray = nb::ndarray<nb::numpy, t_value, nb::ndim<dim>, nb::device::cpu>;

// template<typename t_value, size_t dim>
// class NanoTensor
//     : public xt::xtensor_adaptor<
//           xt::xbuffer_adaptor<t_value*,
//                               xt::no_ownership,
//                               xt::detail::default_allocator_for_ptr_t<t_value*>>,
//           dim,
//           xt::layout_type::dynamic>
// {
//   public:
//     using base_type =
//         xt::xtensor_adaptor<xt::xbuffer_adaptor<t_value*,
//                                                 xt::no_ownership,
//                                                 xt::detail::default_allocator_for_ptr_t<t_value*>>,
//                             dim,
//                             xt::layout_type::dynamic>;
//     using shape_type = std::array<std::size_t, dim>;

//     static base_type base_from_array(const ndarray<t_value, dim>& arr)
//     {
//         return xt::adapt(arr.data(),
//                          arr.size(),
//                          xt::no_ownership(),
//                          shape_from<dim>(arr),
//                          strides_from<t_value, dim>(arr));
//     }

//     static NanoTensor from_shape(const shape_type& shape)
//     {
//         auto arr = ndarray<t_value, dim>(shape);

//         auto tensor = NanoTensor(shape);
//         tensor.add_constructed_array(std::move(arr));
//         return tensor;
//     }

//     // Constructor from nanobind ndarray
//     NanoTensor(ndarray<t_value, dim>& arr)
//         : base_type(base_from_array(arr))
//     {
//     }
//     NanoTensor(const ndarray<t_value, dim>& arr = {})
//         : base_type(base_from_array(arr))
//     {
//     }

//     void resize(const shape_type& shape)
//     {
//         this->base_type::resize(shape);
//     }

//     void add_constructed_array(ndarray<t_value, dim>&& arr) { constructed_array = arr; }
//     std::optional<ndarray<t_value, dim>> constructed_array;

//     // // Constructor from shape
//     // NanoTensor(const shape_type& shape)
//     //     : base_type(shape)
//     // {
//     // }
// };

void init_m_navtools(nb::module_& m)
{

    auto m_navtools =
        m.def_submodule("navtools", "Convenient functions for converting latlon and utm strings.");


    // //----- latitude_to_string -----
    m_navtools.def("latitude_to_string",
                   &latitude_to_string,
                   DOC(themachinethatgoesping, navigation, navtools, latitude_to_string),
                   nb::arg("latitude"),
                   nb::arg("format")    = t_latlon_format::minutes,
                   nb::arg("precision") = 6);

    // vectorized call
    m_navtools.def(
        "latitude_to_string",
        [](const std::vector<double>& latitudes, t_latlon_format format, size_t precision) {
            std::vector<std::string> result;
            result.reserve(latitudes.size());
            for (auto& latitude : latitudes)
            {
                result.push_back(latitude_to_string(latitude, format, precision));
            }
            return result;
        },
        DOC(themachinethatgoesping, navigation, navtools, latitude_to_string),
        nb::arg("latitude"),
        nb::arg("format")    = t_latlon_format::minutes,
        nb::arg("precision") = 6);

    //----- longitude_to_string -----
    m_navtools.def("longitude_to_string",
                   &longitude_to_string,
                   DOC(themachinethatgoesping, navigation, navtools, longitude_to_string),
                   nb::arg("longitude"),
                   nb::arg("format")    = t_latlon_format::minutes,
                   nb::arg("precision") = 6);

    // vectorized call
    m_navtools.def(
        "longitude_to_string",
        [](const std::vector<double>& longitudes, t_latlon_format format, size_t precision) {
            std::vector<std::string> result;
            result.reserve(longitudes.size());
            for (auto& longitude : longitudes)
            {
                result.push_back(longitude_to_string(longitude, format, precision));
            }
            return result;
        },
        DOC(themachinethatgoesping, navigation, navtools, longitude_to_string),
        nb::arg("longitude"),
        nb::arg("format")    = t_latlon_format::minutes,
        nb::arg("precision") = 6);

    // inplace xtensor test
    // m_navtools.def("inplace_1", [](ndarray<double, 1>& nb_tensor) {
    //     // auto tensor = xt::adapt(nb_tensor.data(),
    //     //                         nb_tensor.size(),
    //     //                         xt::no_ownership(),
    //     //                         shape_from<1>(nb_tensor),
    //     //                         strides_from<double, 1>(nb_tensor));
    //     // auto tensor = NanoTensor<double, 1>::base_from_array(nb_tensor);
    //     auto tensor = NanoTensor<double, 1>(nb_tensor);

    //     tensor += 1.0; // Example operation
    // });

    //----- utm conversion -----
    // TODO: documentation is not updated to include these functions for some reason
    m_navtools.def("utm_to_latlon",
                   nb::overload_cast<const xt::xtensor<double, 1>&,
                                     const xt::xtensor<double, 1>&,
                                     int,
                                     bool,
                                     int>(&utm_to_latlon<xt::xtensor<double, 1>>),
                   DOC(themachinethatgoesping, navigation, navtools, utm_to_latlon),
                   nb::arg("northing"),
                   nb::arg("easting"),
                   nb::arg("zone"),
                   nb::arg("northern_hemisphere"),
                   nb::arg("mp_cores") = 1);

    m_navtools.def(
        "utm_to_latlon",
        nb::overload_cast<const xt::xtensor<double, 1>&,
                          const xt::xtensor<double, 1>&,
                          const xt::xtensor<int, 1>&,
                          const xt::xtensor<int, 1>&,
                          int>(&utm_to_latlon<xt::xtensor<double, 1>, xt::xtensor<int, 1>>),
        nb::arg("northing"),
        nb::arg("easting"),
        nb::arg("zone"),
        nb::arg("northern_hemisphere"),
        nb::arg("mp_cores") = 1);

    m_navtools.def("latlon_to_utm",
                   &latlon_to_utm<xt::xtensor<double, 1>>,
                   // DOC(themachinethatgoesping, navigation, navtools, utm_to_latlon),
                   nb::arg("latitude"),
                   nb::arg("longitude"),
                   nb::arg("setzone")  = -1,
                   nb::arg("mp_cores") = 1);

    create_distance_functions<float>(m_navtools);
    create_distance_functions<double>(m_navtools);
    create_distance_functions<datastructures::GeolocationLatLon>(m_navtools);
    create_distance_functions<datastructures::SensordataLatLon>(m_navtools);
    create_distance_functions<std::pair<double, double>>(m_navtools);
    create_distance_functions<std::pair<float, float>>(m_navtools);
}
