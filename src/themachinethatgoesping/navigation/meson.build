# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_navigation'
headerdir = projectnamespace + '/navigation'

# -- source files --
sources = [
  'sensorcoordinatesystem.cpp'
]

headers = [
  'navdata/positionaloffsets.hpp',
  'navdata/geolocation.hpp',
  'navdata/geolocationlatlon.hpp',
  'navdata/geolocationutm.hpp',
  'navdata/geolocationlocal.hpp',
  'navdata/sensordata.hpp',
  'navdata/sensordatalatlon.hpp',
  'navdata/sensordatautm.hpp',
  'navdata/sensordatalocal.hpp',
  'sensorcoordinatesystem.hpp',
  'navtools.hpp'
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  navigation_lib = static_library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          geographiclib_dep,
                          tools_dep
                          ],
                        override_options: [
                          'b_lundef=false'
                      ],
                        install : true, 
                        install_tag : 'library'
                        )
else  
  navigation_lib = library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          geographiclib_dep,
                          tools_dep
                          ],
                        override_options: [
                          'b_lundef=false'
                      ],
                        install : true, 
                        install_tag : 'library'
                        )
endif
                      

# -- internal dependency --
navigation_dep = declare_dependency(
  dependencies : [
    boost_dep,
    eigen3_dep,
    omp_dep,
    geographiclib_dep,
    tools_dep
  ],
  link_with : [navigation_lib],
  include_directories : ['../../']
  )


# -- installation setup --

# install headers
if headers != ['']
    install_headers(headers, subdir: headerdir+'/', preserve_path: true)
endif

# create pkgconfig file
pkg = import('pkgconfig')
pkg.generate(navigation_lib,
             description : 'Functions for interpolating and transforming ship navigation data',
             url : 'https://github.com/themachinethatgoesping/navigation')
