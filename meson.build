# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_navigation',
  'cpp',
  license: 'MPL-2.0',

  version: '0.21.0' ,
  default_options: ['warning_level=0', 'buildtype=release', 'cpp_std=c++26'],
  meson_version: '>=1.8.1' #there is a problem with meson 1.8.0 so just use a higher version,,
)

projectnamespace = 'themachinethatgoesping'

# --- flag old compiler ---
cc = meson.get_compiler('cpp')

if cc.get_id() == 'gcc'
  gcc_version = cc.version()
  if not gcc_version.version_compare('>=12.0')
    error(
      'GCC version 12.0 or newer is required. GCC 11 caused segfaults in python tests, likely due to a compiler bug. Found version '
      + gcc_version,
    )
  endif
endif

# --- dependencies ---

# boost
boost_dep = dependency('boost', static: get_option('dynamic_boost').disabled())

# geographiclib
geographiclib_dep = dependency('geographiclib', version: '>=2.7', static: true)
# # NOTE: the geographiclib wrap injects `-std=c++20` via declare_dependency(compile_args: ...).
# # On the command line the last -std wins, so that stray flag silently downgrades every consumer
# # (navigation, echosounders, ...) from the project's cpp_std=c++26 to C++20. Strip the stray
# # compile_args here (keeping includes/links) so downstream targets stay C++26.
# geographiclib_dep = dependency('geographiclib', version: '>=2.7', static: true).partial_dependency(
#   compile_args: false,
#   link_args: true,
#   links: true,
#   includes: true,
#   sources: true,
# )

# proj
# proj_dep = dependency('proj', static: true)

# themachinethatgoesping
# tools
tools_dep = dependency('themachinethatgoesping_tools', required: false)

if not tools_dep.found()
  tools_dep = subproject('tools', default_options: ['cpp_std=' + get_option('cpp_std')]).get_variable('tools_dep')
endif

# -- python modules --
if get_option('build_pythonmodule').enabled()
  pymod = import('python').find_installation(get_option('python_path'), pure: false)

  python3_dep = pymod.dependency()
  tools_nanobind_dep = dependency('themachinethatgoesping_tools_nanobind', required: false)

  # nanobind: split mode uses a header-only frontend dependency + abi3 stable
  # ABI (the libnanobind backend lives in a separate 'nanobind_backend' module
  # imported at runtime); classic mode links libnanobind into the extension.
  # split_mode defaults to enabled only for the top-level themachinethatgoesping
  # package; standalone subproject builds default to classic (see meson_options).
  # See https://nanobind.readthedocs.io/en/latest/split_mode.html
  if get_option('split_mode').allowed()
    nanobind_subp = subproject('nanobind')
    nanobind_dep = nanobind_subp.get_variable('nanobind_frontend_dep')
    nanobind_limited_api = nanobind_subp.get_variable('nanobind_stable_abi')
  else
    nanobind_dep = dependency('nanobind', version: '>=2.9.1', required: false)
    nanobind_limited_api = ''
  endif

  if not tools_nanobind_dep.found()
    tools_nanobind_dep = subproject('tools').get_variable('tools_nanobind_dep')
  endif

  # set path where to install sources (pythonpath/site-packages/projectnamespace)
  message(
    'python module install directory:',
    pymod.get_install_dir(subdir: projectnamespace),
  )
endif

#themachinethatgoesping meta info
meta_dep = dependency('themachinethatgoesping_meta', required: false)
if not meta_dep.found()
  meta_dep = subproject('meta').get_variable('meta_dep')
endif

# add src
subdir('src')

# add python files
subdir('python')