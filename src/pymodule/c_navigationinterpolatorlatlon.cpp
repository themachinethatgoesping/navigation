// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include <themachinethatgoesping/tools/vectorinterpolators.hpp>
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include "../themachinethatgoesping/navigation/navigationinterpolatorlatlon.hpp"

// -- include pybind11 headers
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::navigation;
using themachinethatgoesping::tools::vectorinterpolators::t_extr_mode;

void init_c_NavigationInterpolatorLatLon(py::module& m)
{
    py::class_<NavigationInterpolatorLatLon>(
        m,
        "NavigationInterpolatorLatLon",
        DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon))
        .def(py::init<const SensorConfiguration&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 NavigationInterpolatorLatLon),
             py::arg("sensor_configuration"),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("set_extrapolation_mode",
             &NavigationInterpolatorLatLon::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLatLon::compute_target_position, py::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 compute_target_position),
             py::arg("target_id"),
             py::arg("timestamp"))
        .def("compute_target_position",
             py::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLatLon::compute_target_position, py::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 compute_target_position),
             py::arg("target_id"),
             py::arg("timestamp"))
        .def("get_sensor_data",
             py::overload_cast<double>(&NavigationInterpolatorLatLon::get_sensor_data, py::const_),
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon, get_sensor_data),
             py::arg("timestamp"))
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
             py::arg("sensor_configuration"))
        .def("add_target",
             py::overload_cast<const std::string&, float, float, float, float, float, float>(
                 &NavigationInterpolatorLatLon::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target),
             py::arg("target_id"),
             py::arg("x"),
             py::arg("y"),
             py::arg("z"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"))
        .def("add_target",
             py::overload_cast<const std::string&, const datastructures::PositionalOffsets&>(
                 &NavigationInterpolatorLatLon::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target_2),
             py::arg("target_id"),
             py::arg("target_offsets"))
        .def("set_data_position",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_position),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLatLon,
                 set_data_position),
             py::arg("timestamp"),
             py::arg("latitude"),
             py::arg("longitude"))

        // set heave data
        .def("set_data_heave",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLatLon::set_data_heave),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heave),
             py::arg("timestamp"),
             py::arg("heave"))

        // set depth data
        .def("set_data_depth",
             py::overload_cast<const std::vector<double>&, const std::vector<float>&>(
                 &NavigationInterpolatorLatLon::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth),
             py::arg("timestamp"),
             py::arg("depth"))

        // set attitude data (no yaw)
        .def("set_data_attitude",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<float>&,
                               const std::vector<float>&>(
                 &NavigationInterpolatorLatLon::set_data_attitude),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_attitude),
             py::arg("timestamp"),
             py::arg("pitch"),
             py::arg("roll"))

        // set data compass
        .def("set_data_heading",
             py::overload_cast<const std::vector<double>&, const std::vector<float>&>(
                 &NavigationInterpolatorLatLon::set_data_heading),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heading),
             py::arg("timestamp"),
             py::arg("heading"))

        // access interpolators
        // latitude / longitude
        .def_property(
            "interpolator_latitude",
            &NavigationInterpolatorLatLon::interpolator_latitude,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_latitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLatLon,
                interpolator_latitude))
        .def_property(
            "interpolator_longitude",
            &NavigationInterpolatorLatLon::interpolator_longitude,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_longitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLatLon,
                interpolator_longitude))

        // heave, depth, attitude, compass
        .def_property(
            "interpolator_heave",
            &NavigationInterpolatorLatLon::interpolator_heave,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_heave() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heave))
        .def_property(
            "interpolator_depth",
            &NavigationInterpolatorLatLon::interpolator_depth,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::LinearInterpolator<double,
                                                                                            float>&
                   interpolator) { self.interpolator_depth() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_depth))
        .def_property(
            "interpolator_attitude",
            &NavigationInterpolatorLatLon::interpolator_attitude,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator<double,
                                                                                           float>&
                   interpolator) { self.interpolator_attitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                I_NavigationInterpolator,
                interpolator_attitude))
        .def_property(
            "interpolator_heading",
            &NavigationInterpolatorLatLon::interpolator_heading,
            [](NavigationInterpolatorLatLon& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator<double,
                                                                                           float>&
                   interpolator) { self.interpolator_heading() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heading))
        .def("merge",
             &NavigationInterpolatorLatLon::merge,
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, merge),
             py::arg("other"))

        .def("__eq__",
             &NavigationInterpolatorLatLon::operator==,
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLatLon, operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(NavigationInterpolatorLatLon)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NavigationInterpolatorLatLon)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NavigationInterpolatorLatLon)
        // end NavigationInterpolatorLatLon
        ;
}
