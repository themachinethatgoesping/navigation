// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers

#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolatorlatlon.hpp"

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation;
using themachinethatgoesping::tools::vectorinterpolators::o_extr_mode;
using themachinethatgoesping::tools::vectorinterpolators::t_extr_mode;

void init_c_NavigationInterpolatorLatLon(nb::module_& m)
{
    nb::class_<NavigationInterpolatorLatLon>(
        m,
        "NavigationInterpolatorLatLon",
        DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon))
        .def(nb::init<const SensorConfiguration&, o_extr_mode>(),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 NavigationInterpolatorLatLon),
             nb::arg("sensor_configuration"),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("set_extrapolation_mode",
             &NavigationInterpolatorLatLon::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_extrapolation_mode),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             nb::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLatLon::compute_target_position, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 compute_target_position),
             nb::arg("target_id"),
             nb::arg("timestamp"))
        .def("compute_target_position",
             nb::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLatLon::compute_target_position, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 compute_target_position),
             nb::arg("target_id"),
             nb::arg("timestamp"))
        .def("get_sensor_data",
             nb::overload_cast<double>(&NavigationInterpolatorLatLon::get_sensor_data, nb::const_),
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon, get_sensor_data),
             nb::arg("timestamp"))
        .def("get_sensor_configuration",
             &NavigationInterpolatorLatLon::get_sensor_configuration,
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 get_sensor_configuration))
        .def("set_sensor_configuration",
             &NavigationInterpolatorLatLon::set_sensor_configuration,
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_sensor_configuration),
             nb::arg("sensor_configuration"))
        .def("add_target",
             nb::overload_cast<const std::string&, float, float, float, float, float, float>(
                 &NavigationInterpolatorLatLon::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target),
             nb::arg("target_id"),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"),
             nb::arg("yaw"),
             nb::arg("pitch"),
             nb::arg("roll"))
        .def("add_target",
             nb::overload_cast<const std::string&, const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLatLon::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target_2),
             nb::arg("target_id"),
             nb::arg("target_offsets"))
        .def("set_data_position",
             nb::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_position),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_data_position),
             nb::arg("timestamp"),
             nb::arg("latitude"),
             nb::arg("longitude"))

        // set heave data
        .def("set_data_heave",
             nb::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_heave),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heave),
             nb::arg("timestamp"),
             nb::arg("heave"))

        // set depth data
        .def("set_data_depth",
             nb::overload_cast<const std::vector<double>&, const std::vector<float>&>(
                 &NavigationInterpolatorLatLon::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth),
             nb::arg("timestamp"),
             nb::arg("depth"))

        // set attitude data (no yaw)
        .def("set_data_attitude",
             nb::overload_cast<const std::vector<double>&,
                               const std::vector<float>&,
                               const std::vector<float>&>(
                 &NavigationInterpolatorLatLon::set_data_attitude),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_attitude),
             nb::arg("timestamp"),
             nb::arg("pitch"),
             nb::arg("roll"))

        // set data compass
        .def("set_data_heading",
             nb::overload_cast<const std::vector<double>&, const std::vector<float>&>(
                 &NavigationInterpolatorLatLon::set_data_heading),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heading),
             nb::arg("timestamp"),
             nb::arg("heading"))

        // access interpolators
        // latitude / longitude
        .def_prop_rw(
            "interpolator_latitude",
            [](NavigationInterpolatorLatLon& self) -> auto& { return self.interpolator_latitude(); },
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_latitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLatLon,
                interpolator_latitude))
        .def_prop_rw(
            "interpolator_longitude",
            [](NavigationInterpolatorLatLon& self) -> auto& { return self.interpolator_longitude(); },
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_longitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLatLon,
                interpolator_longitude))

        // heave, depth, attitude, compass
        .def_prop_rw(
            "interpolator_heave",
            [](NavigationInterpolatorLatLon& self) -> auto& { return self.interpolator_heave(); },
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_heave() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heave))
        .def_prop_rw(
            "interpolator_depth",
            [](NavigationInterpolatorLatLon& self) -> auto& { return self.interpolator_depth(); },
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::LinearInterpolator<double,
                                                                                            float>&
                   interpolator) { self.interpolator_depth() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_depth))
        .def_prop_rw(
            "interpolator_attitude",
            [](NavigationInterpolatorLatLon& self) -> auto& { return self.interpolator_attitude(); },
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator<double,
                                                                                           float>&
                   interpolator) { self.interpolator_attitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                I_NavigationInterpolator,
                interpolator_attitude))
        .def_prop_rw(
            "interpolator_heading",
            [](NavigationInterpolatorLatLon& self) -> auto& { return self.interpolator_heading(); },
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator<double,
                                                                                           float>&
                   interpolator) { self.interpolator_heading() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heading))
        .def("merge",
             &NavigationInterpolatorLatLon::merge,
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, merge),
             nb::arg("other"))

        .def("__eq__",
             &NavigationInterpolatorLatLon::operator==,
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon, operator_eq),
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NavigationInterpolatorLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NavigationInterpolatorLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NavigationInterpolatorLatLon)
        // end NavigationInterpolatorLatLon
        ;
}
