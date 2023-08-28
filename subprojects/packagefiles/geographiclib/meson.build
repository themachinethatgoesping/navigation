# SPDX-FileCopyrightText: 2011-2022 Squall Line Software, LLC
# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MIT

# source: https://oss.squalllinesoftware.com/projects/disorder/files *geographiclib-2.0.meson.tar.gz
# souce(direct link): https://oss.squalllinesoftware.com/attachments/30

project(
    'GeographicLib',
    'cpp',
    version : '2.3',
    license : 'MIT',
    default_options : ['cpp_std=c++11'],
)

version = meson.project_version().split('.')
config = configuration_data()
cxx = meson.get_compiler('cpp')

config.set('PROJECT_VERSION', meson.project_version())
config.set('PROJECT_VERSION_MAJOR', version[0])
config.set('PROJECT_VERSION_MINOR', version[1])
config.set('PROJECT_VERSION_PATCH', version.length() == 3 ? version[2] : 0)

config.set(
    'GEOGRAPHICLIB_DATA',
    (host_machine.system() == 'windows' ? 'C:/ProgramData' : '/usr/local/share')
    / meson.project_name()
)

config.set10(
    'GEOGRAPHICLIB_HAVE_LONG_DOUBLE',
    cxx.sizeof('long double') > cxx.sizeof('double')
)

config.set10('GEOGRAPHICLIB_WORDS_BIGENDIAN', host_machine.endian() == 'big')

config.set(
    'GEOGRAPHICLIB_LIB_TYPE_VAL',
    {'static':0, 'shared':1, 'both':2}.get(get_option('default_library'), 1)
)

config.set(
    'GEOGRAPHICLIB_PRECISION',
    {'float':1, 'double':2, 'extended':3, 'quadruple':4, 'variable':5}.get(
        get_option('precision'), 2)
)

subdir('include' / meson.project_name())
subdir('src')

geographiclib_include_directories = include_directories('include')

geographiclib_library = library(
    meson.project_name(),
    geographiclib_sources,
    include_directories : geographiclib_include_directories,
    install: true
)

geographiclib_dep = declare_dependency(
    link_with : geographiclib_library,
    include_directories : geographiclib_include_directories,
)
