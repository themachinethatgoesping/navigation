# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- module name
module_name = 'navigation'
        
# -- sources
sources = [
    'module.cpp',
    'm_navtools.cpp',
    'datastructures/c_positionaloffsets.cpp',
    'datastructures/c_geolocation.cpp',
    'datastructures/c_geolocationlatlon.cpp',
    'datastructures/c_geolocationlocal.cpp',
    'datastructures/c_geolocationutm.cpp',
    'datastructures/c_sensordata.cpp',
    'datastructures/c_sensordatalocal.cpp',
    'datastructures/c_sensordatalatlon.cpp',
    'datastructures/c_sensordatautm.cpp',
    'datastructures/c_sensordatalocal.cpp',
    'c_sensorconfiguration.cpp',
    'c_navigationinterpolatorlocal.cpp',
    'c_navigationinterpolatorlatlon.cpp',
    'nmea_0183/c_nmea_base.cpp',
    'nmea_0183/c_nmea_zda.cpp',
    'nmea_0183/c_nmea_vlw.cpp',
    'nmea_0183/c_nmea_vtg.cpp',
    'nmea_0183/c_nmea_vhw.cpp',
    'nmea_0183/c_nmea_rmc.cpp',
    'nmea_0183/c_nmea_hdt.cpp',
    'nmea_0183/c_nmea_gll.cpp',
    'nmea_0183/c_nmea_gga.cpp',
    'nmea_0183/c_nmea_unknown.cpp'
]

# define python module
py_navigation = pymod.extension_module(
    module_name,
    sources: sources,
    dependencies : [
        navigation_dep,
        pybind11_dep,
        python3_dep],
    link_language : 'cpp',
    override_options: [
        #'cpp_rtti=true',
    ],
    cpp_args : ['-DMODULE_NAME='+module_name, '-DMODULE_VERSION=' + '"' + meson.project_version() + '"'],
    install : true,
    install_dir : pythoninstallpath,
    install_tag : 'python-runtime'
)



        
