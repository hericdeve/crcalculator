project('crcalculator', 'cpp',
  default_options : ['cpp_std=c++17', 'warning_level=3'])


add_project_arguments(language: 'cpp')

# Add dependencies
boost_dep = dependency('boost')
rapidfuzz_dep = dependency('rapidfuzz')


sources = files('fileManagement.cpp', 'grade.cpp', 'resources.cpp','menuInterface.cpp', 'subject.cpp', 'main.cpp')

# Add executable and install it
executable('crcalculator', sources,
  dependencies : [boost_dep, rapidfuzz_dep],
  install : true)

# Add a test
#test('crcalculator_test', find_program('tests/crcalculator_test'))
