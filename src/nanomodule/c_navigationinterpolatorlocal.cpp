// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers

#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>
#include <xtensor-python/nanobind/pytensor.hpp>

#include <themachinethatgoesping/navigation/datastructures.hpp>
#include <themachinethatgoesping/navigation/navigationinterpolatorlocal.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/set.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation;
using themachinethatgoesping::tools::vectorinterpolators::o_extr_mode;
using themachinethatgoesping::tools::vectorinterpolators::t_extr_mode;

void init_c_NavigationInterpolatorLocal(nb::module_& m)
{
    nb::class_<NavigationInterpolatorLocal>(
        m,
        "NavigationInterpolatorLocal",
        DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal))
        .def(nb::init<const SensorConfiguration&, o_extr_mode>(),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 NavigationInterpolatorLocal),
             nb::arg("sensor_configuration"),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("set_extrapolation_mode",
             &NavigationInterpolatorLocal::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 set_extrapolation_mode),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             nb::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLocal::compute_target_position, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 compute_target_position),
             nb::arg("target_id"),
             nb::arg("timestamp"))
        .def("__call__",
             nb::overload_cast<const std::string&, const std::vector<double>&, int>(
                 &NavigationInterpolatorLocal::compute_target_position, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 compute_target_position_2),
             nb::arg("target_id"),
             nb::arg("timestamps"),
             nb::arg("mp_cores") = 1)
        .def("compute_target_position",
             nb::overload_cast<const std::string&, double>(
                 &NavigationInterpolatorLocal::compute_target_position, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 compute_target_position),
             nb::arg("target_id"),
             nb::arg("timestamp"))
        .def("compute_target_position",
             nb::overload_cast<const std::string&, const std::vector<double>&, int>(
                 &NavigationInterpolatorLocal::compute_target_position, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 compute_target_position_2),
             nb::arg("target_id"),
             nb::arg("timestamps"),
             nb::arg("mp_cores") = 1)
        .def("get_sensor_data",
             nb::overload_cast<double>(&NavigationInterpolatorLocal::get_sensor_data, nb::const_),
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal, get_sensor_data),
             nb::arg("timestamp"))
        .def("get_sensor_data",
             nb::overload_cast<const std::vector<double>&, int>(
                 &NavigationInterpolatorLocal::get_sensor_data, nb::const_),
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 get_sensor_data_2),
             nb::arg("timestamps"),
             nb::arg("mp_cores") = 1)
        .def("get_sampled_timestamps",
             &NavigationInterpolatorLocal::get_sampled_timestamps,
             DOC(themachinethatgoesping,
                 navigation,
                 NavigationInterpolatorLocal,
                 get_sampled_timestamps),
             nb::arg("downsample_interval") = std::numeric_limits<double>::quiet_NaN(),
             nb::arg("max_gap")             = std::numeric_limits<double>::quiet_NaN(),
             nb::arg("sensor_names")        = std::set<std::string>{ "northing", "easting" })
        .def("get_sensor_configuration",
             &NavigationInterpolatorLocal::get_sensor_configuration,
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 get_sensor_configuration))
        .def("set_sensor_configuration",
             &NavigationInterpolatorLocal::set_sensor_configuration,
             DOC(themachinethatgoesping,
                 navigation,
                 I_NavigationInterpolator,
                 set_sensor_configuration),
             nb::arg("sensor_configuration"))
        .def("add_target",
             nb::overload_cast<const std::string&, float, float, float, float, float, float>(
                 &NavigationInterpolatorLocal::add_target),
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
                 &NavigationInterpolatorLocal::add_target),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, add_target_2),
             nb::arg("target_id"),
             nb::arg("target_offsets"))
        .def(
            "set_data_position",
            nb::overload_cast<const std::vector<double>&,
                              const std::vector<double>&,
                              const std::vector<double>&>(
                &NavigationInterpolatorLocal::set_data_position),
            DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal, set_data_position),
            nb::arg("timestamp"),
            nb::arg("northing"),
            nb::arg("easting"))

        // set heave data
        .def("set_data_heave",
             nb::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &NavigationInterpolatorLocal::set_data_heave),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heave),
             nb::arg("timestamp"),
             nb::arg("heave"))

        // set depth data
        .def("set_data_depth",
             nb::overload_cast<const std::vector<double>&, const std::vector<float>&>(
                 &NavigationInterpolatorLocal::set_data_depth),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_depth),
             nb::arg("timestamp"),
             nb::arg("depth"))

        // set attitude data (no yaw)
        .def("set_data_attitude",
             nb::overload_cast<const std::vector<double>&,
                               const std::vector<float>&,
                               const std::vector<float>&>(
                 &NavigationInterpolatorLocal::set_data_attitude),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_attitude),
             nb::arg("timestamp"),
             nb::arg("pitch"),
             nb::arg("roll"))

        // set data compass
        .def("set_data_heading",
             nb::overload_cast<const std::vector<double>&, const std::vector<float>&>(
                 &NavigationInterpolatorLocal::set_data_heading),
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, set_data_heading),
             nb::arg("timestamp"),
             nb::arg("heading"))

        // access interpolators
        // northing / easting
        .def_prop_rw(
            "interpolator_northing",
            [](NavigationInterpolatorLocal& self) -> auto& { return self.interpolator_northing(); },
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_northing() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLocal,
                interpolator_northing))
        .def_prop_rw(
            "interpolator_easting",
            [](NavigationInterpolatorLocal& self) -> auto& { return self.interpolator_easting(); },
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_easting() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                NavigationInterpolatorLocal,
                interpolator_easting))

        // heave, depth, attitude, compass
        .def_prop_rw(
            "interpolator_heave",
            [](NavigationInterpolatorLocal& self) -> auto& { return self.interpolator_heave(); },
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::AkimaInterpolator<double>&
                   interpolator) { self.interpolator_heave() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heave))
        .def_prop_rw(
            "interpolator_depth",
            [](NavigationInterpolatorLocal& self) -> auto& { return self.interpolator_depth(); },
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::LinearInterpolator<double,
                                                                                            float>&
                   interpolator) { self.interpolator_depth() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_depth))
        .def_prop_rw(
            "interpolator_attitude",
            [](NavigationInterpolatorLocal& self) -> auto& { return self.interpolator_attitude(); },
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator<double,
                                                                                           float>&
                   interpolator) { self.interpolator_attitude() = interpolator; },
            DOC(themachinethatgoesping,
                navigation,
                I_NavigationInterpolator,
                interpolator_attitude))
        .def_prop_rw(
            "interpolator_heading",
            [](NavigationInterpolatorLocal& self) -> auto& { return self.interpolator_heading(); },
            [](NavigationInterpolatorLocal& self,
               const themachinethatgoesping::tools::vectorinterpolators::SlerpInterpolator<double,
                                                                                           float>&
                   interpolator) { self.interpolator_heading() = interpolator; },
            DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, interpolator_heading))
        .def("merge",
             &NavigationInterpolatorLocal::merge,
             DOC(themachinethatgoesping, navigation, I_NavigationInterpolator, merge),
             nb::arg("other"))

        .def("__eq__",
             &NavigationInterpolatorLocal::operator==,
             DOC(themachinethatgoesping, navigation, NavigationInterpolatorLocal, operator_eq),
             nb::arg("other"))

        // default copy functionss
        __PYCLASS_DEFAULT_COPY__(NavigationInterpolatorLocal)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(NavigationInterpolatorLocal)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(NavigationInterpolatorLocal)
        // end NavigationInterpolatorLocal
        ;
}
