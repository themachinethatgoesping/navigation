// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0


// -- c++ library headers
#include "../themachinethatgoesping/navigation/datastructures.hpp"
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::navigation::datastructures;

#define DOC_SensorPose(ARG)                                                                 \
    DOC(themachinethatgoesping, navigation, datastructures, SensorPose, ARG)

void init_c_positionaloffsets(nb::module_& m)
{

    nb::class_<SensorPose>(
        m,
        "SensorPose",
        DOC(themachinethatgoesping, navigation, datastructures, SensorPose))
    .def(nb::init<std::string, float, float, float, float, float, float, bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorPose,
                 SensorPose_2),
             nb::arg("name")  = "",
             nb::arg("x")       = 0.0f,
             nb::arg("y")       = 0.0f,
             nb::arg("z")       = 0.0f,
             nb::arg("yaw")     = 0.0f,
             nb::arg("pitch")   = 0.0f,
             nb::arg("roll")    = 0.0f,
             nb::arg("ypr_offsets_applied") = false)
        .def(nb::init<std::string,
                      float,
                      float,
                      float,
                      themachinethatgoesping::tools::rotationfunctions::Rotation<float>,
                      bool>(),
             DOC(themachinethatgoesping,
                 navigation,
                 datastructures,
                 SensorPose,
                 SensorPose_3),
             nb::arg("name"),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"),
             nb::arg("rotation"),
             nb::arg("ypr_offsets_applied") = false)
        .def_static("from_txrx",
                    &SensorPose::from_txrx,
                    DOC_SensorPose(from_txrx),
                    nb::arg("tx"),
                    nb::arg("rx"),
                    nb::arg("name"))

        .def("__eq__",
             &SensorPose::operator==,
             DOC_SensorPose(operator_eq),
             nb::arg("other"))
        .def_rw("name", &SensorPose::name, DOC_SensorPose(name))
        .def_rw("x", &SensorPose::x, DOC_SensorPose(x))
        .def_rw("y", &SensorPose::y, DOC_SensorPose(y))
        .def_rw("z", &SensorPose::z, DOC_SensorPose(z))
        .def_rw("rotation", &SensorPose::rotation, DOC_SensorPose(rotation))
        .def_prop_rw("yaw", &SensorPose::yaw, &SensorPose::set_yaw, DOC_SensorPose(yaw))
        .def_prop_rw("pitch", &SensorPose::pitch, &SensorPose::set_pitch, DOC_SensorPose(pitch))
        .def_prop_rw("roll", &SensorPose::roll, &SensorPose::set_roll, DOC_SensorPose(roll))
        .def("set_ypr", &SensorPose::set_ypr, DOC_SensorPose(set_ypr), nb::arg("yaw"), nb::arg("pitch"), nb::arg("roll"))
        .def_rw("ypr_offsets_applied",
                &SensorPose::ypr_offsets_applied,
                "if true, the yaw/pitch/roll offsets are already applied to the associated sensor "
                "data (e.g. Kongsberg .all logs the attitude/heading already corrected for the "
                "sensor mounting offsets). If so, the SensorConfiguration does not re-apply them.")
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SensorPose)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SensorPose)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SensorPose)
        // end SensorPose
        ;
}
