# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- module name
module_name = 'navigation'
        
# -- sources
sources = [
    'module.cpp',
    'm_navtools.cpp',
    'navdata/c_positionaloffsets.cpp',
    'navdata/c_geolocation.cpp',
    'navdata/c_geolocationutm.cpp',
    'navdata/c_geolocationlocal.cpp',
    'navdata/c_sensordata.cpp',
    'navdata/c_sensordatalocal.cpp',
    'navdata/c_sensordatalatlon.cpp',
    'navdata/c_sensordatautm.cpp',
    'navdata/c_sensordatalocal.cpp'
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
    cpp_args : '-DPYTHON_LIB='+module_name,
    install : true,
    install_dir : pythoninstallpath,
    install_tag : 'python-runtime'
)



        
