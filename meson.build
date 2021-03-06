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
docopt_proj = subproject('docopt')
docopt_dep = dependency('docopt')
catch2_proj = subproject('catch2')
catch2_dep = dependency('catch2')

exe = executable('pb', sources: ['src/main.cpp', 'src/lattice.cpp'], dependencies: [fmt_dep, eigen_dep, cairo_dep, docopt_dep], include_directories: include_dir, override_options: ['cpp_std=c++20'])
test_exe = executable('test_pb', sources: ['src/lattice.cpp', 'tests/lattice_test.cpp'], dependencies: [catch2_dep, fmt_dep, eigen_dep, cairo_dep, docopt_dep], include_directories: include_dir, override_options: ['cpp_std=c++20'])
