# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_navigation'
headerdir = projectnamespace + '/navigation'

# -- source files --
sources = [
  'sensorconfiguration.cpp',
]

headers = [
  'datastructures.hpp',
  'i_navigationinterpolator.hpp',
  'navigationinterpolatorlatlon.hpp',
  'navigationinterpolatorlocal.hpp',
  'navtools.hpp',
  'nmea_0183.hpp',
  'sensorconfiguration.hpp',
  'datastructures/geolocation.hpp',
  'datastructures/geolocationlatlon.hpp',
  'datastructures/geolocationlocal.hpp',
  'datastructures/geolocationutm.hpp',
  'datastructures/positionaloffsets.hpp',
  'datastructures/sensordata.hpp',
  'datastructures/sensordatalatlon.hpp',
  'datastructures/sensordatalocal.hpp',
  'datastructures/sensordatautm.hpp',
  'datastructures/.docstrings/geolocation.doc.hpp',
  'datastructures/.docstrings/geolocationlatlon.doc.hpp',
  'datastructures/.docstrings/geolocationlocal.doc.hpp',
  'datastructures/.docstrings/geolocationutm.doc.hpp',
  'datastructures/.docstrings/positionaloffsets.doc.hpp',
  'datastructures/.docstrings/sensordata.doc.hpp',
  'datastructures/.docstrings/sensordatalatlon.doc.hpp',
  'datastructures/.docstrings/sensordatalocal.doc.hpp',
  'datastructures/.docstrings/sensordatautm.doc.hpp',
  '.docstrings/datastructures.doc.hpp',
  '.docstrings/i_navigationinterpolator.doc.hpp',
  '.docstrings/navigationinterpolatorlatlon.doc.hpp',
  '.docstrings/navigationinterpolatorlocal.doc.hpp',
  '.docstrings/navtools.doc.hpp',
  '.docstrings/nmea_0183.doc.hpp',
  '.docstrings/sensorconfiguration.doc.hpp',
  'nmea_0183/helper.hpp',
  'nmea_0183/nmea_base.hpp',
  'nmea_0183/nmea_gga.hpp',
  'nmea_0183/nmea_gll.hpp',
  'nmea_0183/nmea_gst.hpp',
  'nmea_0183/nmea_hdt.hpp',
  'nmea_0183/nmea_rmc.hpp',
  'nmea_0183/nmea_unknown.hpp',
  'nmea_0183/nmea_vhw.hpp',
  'nmea_0183/nmea_vlw.hpp',
  'nmea_0183/nmea_vtg.hpp',
  'nmea_0183/nmea_zda.hpp',
  'nmea_0183/.docstrings/helper.doc.hpp',
  'nmea_0183/.docstrings/nmea_base.doc.hpp',
  'nmea_0183/.docstrings/nmea_gga.doc.hpp',
  'nmea_0183/.docstrings/nmea_gll.doc.hpp',
  'nmea_0183/.docstrings/nmea_gst.doc.hpp',
  'nmea_0183/.docstrings/nmea_hdt.doc.hpp',
  'nmea_0183/.docstrings/nmea_rmc.doc.hpp',
  'nmea_0183/.docstrings/nmea_unknown.doc.hpp',
  'nmea_0183/.docstrings/nmea_vhw.doc.hpp',
  'nmea_0183/.docstrings/nmea_vlw.doc.hpp',
  'nmea_0183/.docstrings/nmea_vtg.doc.hpp',
  'nmea_0183/.docstrings/nmea_zda.doc.hpp',
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  navigation_lib = static_library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          #proj_dep,
                          geographiclib_dep,
                          tools_dep
                          ],
                        override_options: [
                          'b_lundef=false'
                      ],
                        # cpp_pch : 'pch/pch.hpp',
                        install : true, 
                        install_tag : 'library'
                        )
else  
  navigation_lib = library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          #proj_dep,
                          geographiclib_dep,
                          tools_dep
                          ],
                        override_options: [
                          'b_lundef=false'
                      ],
                        # cpp_pch : 'pch/pch.hpp',
                        install : true, 
                        install_tag : 'library'
                        )
endif
                      

# -- internal dependency --
navigation_dep = declare_dependency(
  dependencies : [
    boost_dep,
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
