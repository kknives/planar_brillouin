project('planar_brillouin', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

# Include directories
include_dir = include_directories('include')

# For better formatting
fmt_proj = subproject('fmt')
fmt_dep = fmt_proj.get_variable('fmt_dep')

exe = executable('pb', sources: ['src/main.cpp', 'src/point.cpp'], dependencies: [fmt_dep], include_directories: include_dir, override_options: ['cpp_std=c++20'])

test('basic', exe)
