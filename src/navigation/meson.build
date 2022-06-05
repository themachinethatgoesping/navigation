# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_navigation'
headerdir = projectnamespace + '/navigation'

# -- source files --
sources = [
  'vessel.cpp'
]

headers = [
  'vessel.h'
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  navigation_lib = static_library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          hinnant_date_dep],
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
                          omp_dep],
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
    omp_dep
  ],
  link_with : [navigation_lib],
  #include_directories : ['../']
  )


# -- installation setup --

# install headers
if headers != ['']
    install_headers(headers, subdir : headerdir+'/')
endif

# create pkgconfig file
pkg = import('pkgconfig')
pkg.generate(navigation_lib,
             description : 'Functions for interpolating and transforming ship navigation data',
             url : 'https://github.com/themachinethatgoesping/navigation')
