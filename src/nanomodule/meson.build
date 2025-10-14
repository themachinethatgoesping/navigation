# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- module name
module_name = 'navigation_nanopy'
        
# -- sources
sources = [
  'c_navigationinterpolatorlatlon.cpp',
  'c_navigationinterpolatorlocal.cpp',
  'c_sensorconfiguration.cpp',
  'm_navtools.cpp',
  'module.cpp',
  'datastructures/c_geolocation.cpp',
  'datastructures/c_geolocationlatlon.cpp',
  'datastructures/c_geolocationlocal.cpp',
  'datastructures/c_geolocationutm.cpp',
  'datastructures/c_positionaloffsets.cpp',
  'datastructures/c_sensordata.cpp',
  'datastructures/c_sensordatalatlon.cpp',
  'datastructures/c_sensordatalocal.cpp',
  'datastructures/c_sensordatautm.cpp',
  'nmea_0183/c_nmea_base.cpp',
  'nmea_0183/c_nmea_gga.cpp',
  'nmea_0183/c_nmea_gll.cpp',
  'nmea_0183/c_nmea_gst.cpp',
  'nmea_0183/c_nmea_hdt.cpp',
  'nmea_0183/c_nmea_rmc.cpp',
  'nmea_0183/c_nmea_unknown.cpp',
  'nmea_0183/c_nmea_vhw.cpp',
  'nmea_0183/c_nmea_vlw.cpp',
  'nmea_0183/c_nmea_vtg.cpp',
  'nmea_0183/c_nmea_zda.cpp',
]

# define python module
py_navigation = pymod.extension_module(
    module_name,
    sources: sources,
    dependencies : [
        tools_nanobind_dep,
        navigation_dep,
        nanobind_dep,
        python3_dep],
    link_language : 'cpp',
     cpp_pch : '../pch/navigation_navigation_nanopy.hpp',
    override_options: [
        #'cpp_rtti=true',
    ],
    cpp_args : ['-DMODULE_NAME='+module_name, '-DMODULE_VERSION=' + '"' + meson.project_version() + '"'],
    install : true,
    subdir : projectnamespace,
    install_tag : 'python-runtime',
    override_options: ['unity=off']
)



        
