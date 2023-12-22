cmake_minimum_required(VERSION 3.21)
find_package(GTest REQUIRED)

set(gtesthelper
${CMAKE_CURRENT_SOURCE_DIR}/include/c_api_test_helpers.hpp
${CMAKE_CURRENT_SOURCE_DIR}/include/testhelpers.hpp
)

macro(cavc_add_test name)
  add_executable(${name} ${name}.cpp ${gtesthelper})

  target_include_directories(${name}
    PRIVATE
    ${GTEST_INCLUDE_DIRS})

  target_link_libraries(${name}
    PRIVATE PolylineFactory ${CAVC_C_API_LIB} GTest::gtest_main GTest::gtest GTest::gmock)

  # note: adding executable as single test rather than discovering tests via gtest_discover_tests
  # because it adds parmeterized tests as individual tests and ctest runs them one by one which is
  # quite slow
  add_test(NAME ${name} COMMAND ${name})
endmacro()

cavc_add_test(TEST_cavc_pline)
cavc_add_test(TEST_cavc_pline_function)
cavc_add_test(TEST_cavc_parallel_offset)
cavc_add_test(TEST_cavc_combine_plines)
cavc_add_test(TEST_staticspatialindex)
