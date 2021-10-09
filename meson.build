# vim: set ft=conf
project('planar_brillouin', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

# Only 5 errors, please
add_global_arguments('-fmax-errors=5', language: 'cpp')
# Include directories
include_dir = include_directories('include')

# For better formatting
fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')
eigen_proj = subproject('eigen')
eigen_dep = eigen_proj.get_variable('eigen_dep')
cairo_proj = subproject('cairo')
cairo_dep = dependency('cairo')

exe = executable('pb', sources: ['src/main.cpp'], dependencies: [fmt_dep, eigen_dep, cairo_dep], include_directories: include_dir, override_options: ['cpp_std=c++20'])

test('basic', exe)
