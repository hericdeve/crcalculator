project('crcalculator', 'cpp',
  default_options : ['cpp_std=c++17', 'warning_level=3'])



# Add dependencies
boost_dep = dependency('boost')
rapidfuzz_dep = dependency('rapidfuzz')


#sources = files('*.cpp')

# Add executable and install it
executable('crcalculator', '*.cpp',
  dependencies : [boost_dep, rapidfuzz_dep],
  install : true)

# Add a test
test('crcalculator_test', find_program('tests/crcalculator_test'))
