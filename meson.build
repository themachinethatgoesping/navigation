# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_navigation',
  'cpp',
  license: 'MPL-2.0',

  version: '0.4.2',
  default_options: ['warning_level=3', 'buildtype=release', 'cpp_std=c++17'],
  meson_version: '>=0.63' #0.63 added preserve_path for install headers option
)

projectnamespace = 'themachinethatgoesping'

# --- dependencies ---

# system
if meson.get_compiler('cpp').get_id() == 'clang'
  omp_dep = declare_dependency(
    compile_args: ['-Xpreprocessor', '-fopenmp']
  )
else
  omp_dep = dependency('openmp')
endif

# boost
boost_dep = dependency('boost', static: true)

# eigen 3
eigen3_dep = dependency('eigen3', required: false)

if not eigen3_dep.found()
    eigen3_project = subproject('eigen')
    eigen3_dep = eigen3_project.get_variable('eigen_dep')
endif

# geographiclib
geographiclib_dep = dependency('geographiclib', required: false)

if not geographiclib_dep.found()
    geographiclib_dep = subproject('geographiclib').get_variable('geographiclib_dep')
endif

# themachinethatgoesping
# tools
tools_dep = dependency('themachinethatgoesping_tools', required: false)

if not tools_dep.found()
    tools_dep = subproject('tools').get_variable('tools_dep')
endif

#themachinethatgoesping meta info
meta_dep = dependency('themachinethatgoesping_meta', required: false)
if not meta_dep.found()
    meta_dep = subproject('meta').get_variable('meta_dep')
endif


# add src
subdir('src')
 
# add python files
#subdir('python')
