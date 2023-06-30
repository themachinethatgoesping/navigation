# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_navigation'
headerdir = projectnamespace + '/navigation'

# -- source files --
sources = [
  'sensorconfiguration.cpp'
]

headers = [
  'navtools.hpp',
  'datastructures/positionaloffsets.hpp',
  'datastructures/geolocation.hpp',
  'datastructures/geolocationlatlon.hpp',
  'datastructures/geolocationutm.hpp',
  'datastructures/geolocationlocal.hpp',
  'datastructures/sensordata.hpp',
  'datastructures/sensordatalatlon.hpp',
  'datastructures/sensordatautm.hpp',
  'datastructures/sensordatalocal.hpp',
  'sensorconfiguration.hpp',
  'i_navigationinterpolator.hpp',
  'navigationinterpolatorlocal.hpp',
  'navigationinterpolatorlatlon.hpp',
  'nmea_0183.hpp',
  'nmea_0183/helper.hpp',
  'nmea_0183/nmea_base.hpp',
  'nmea_0183/nmea_zda.hpp',
  'nmea_0183/nmea_vlw.hpp',
  'nmea_0183/nmea_vtg.hpp',
  'nmea_0183/nmea_vhw.hpp',
  'nmea_0183/nmea_rmc.hpp',
  'nmea_0183/nmea_hdt.hpp',
  'nmea_0183/nmea_gll.hpp',
  'nmea_0183/nmea_gga.hpp',
  'nmea_0183/nmea_gst.hpp',
  'nmea_0183/nmea_unknown.hpp'
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  navigation_lib = static_library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          omp_dep,
                          #proj_dep,
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
                          omp_dep,
                          #proj_dep,
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
