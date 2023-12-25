cmake_minimum_required(VERSION 3.21)

# detect if CavalierContours is a subproject or not
# do not include examples, tests, and benchmarks in that case
if (NOT DEFINED PROJECT_NAME)
  set(NOT_SUBPROJECT ON)
endif()

project(CavalierContours VERSION 0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CPP Header only library
# Copy hpp files to build/include
set(CAVC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/build/include/cavc)
set(CAVC_C_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/build/include/cavc_c)
set(CAVC_INTERNAL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/build/include/cavc/internal)

if (EXISTS ${CAVC_INCLUDE_DIR})
    file(REMOVE_RECURSE ${CAVC_INCLUDE_DIR})
endif()

set(CAVC_HEADERS
    include/intrlineseg2circle2.hpp
    include/intrlineseg2lineseg2.hpp
    include/mathutils.hpp
    include/intrcircle2circle2.hpp
    include/vector.hpp
    include/plinesegment.hpp
    include/polyline.hpp
    include/polylinecombine.hpp
    include/polylineintersects.hpp
    include/polylineoffset.hpp
    include/polylineoffsetislands.hpp
    include/staticspatialindex.hpp
    include/vector2.hpp
)

foreach(CAVC_HEADER ${CAVC_HEADERS})
    file(COPY ${CAVC_HEADER} DESTINATION ${CAVC_INCLUDE_DIR})
endforeach()

set(CAVC_INTERNAL_HEADERS
    include/internal/diagnostics.hpp
    include/internal/common.hpp
)

foreach(CAVC_INTERNAL_HEADER ${CAVC_INTERNAL_HEADERS})
    file(COPY ${CAVC_INTERNAL_HEADER} DESTINATION ${CAVC_INTERNAL_INCLUDE_DIR})
endforeach()

# C API Library


set(CAVC_C_API_LIB ${PROJECT_NAME})

add_library(${CAVC_C_API_LIB}
    STATIC
    src/cavaliercontours.h
    src/cavaliercontours.cpp)

target_include_directories(${CAVC_C_API_LIB}
PRIVATE
    ${PROJECT_SOURCE_DIR}/build/include
    )

file(COPY src/cavaliercontours.h DESTINATION ${CAVC_C_INCLUDE_DIR})

# compiler warnings, note: not using /W4 on MSVC since it emits warning due to default of /W3
# from cmake
if(MSVC)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        target_compile_options(${CAVC_C_API_LIB} PRIVATE
        /clang:-Werror /clang:-Wall /clang:-Wextra /clang:-pedantic-errors /clang:-Wsign-conversion /clang:-Wconversion)
    endif()
    target_compile_options(${CAVC_C_API_LIB} PRIVATE
        /WX)
else()
    target_compile_options(${CAVC_C_API_LIB} PRIVATE
        -Werror -Wall -Wextra -pedantic-errors -Wsign-conversion -Wconversion)
endif()

target_compile_definitions(${CAVC_C_API_LIB} PRIVATE CAVC_EXPORTS)
target_include_directories(${CAVC_C_API_LIB} PUBLIC c_api_include/)
target_link_libraries(${CAVC_C_API_LIB} PRIVATE ${CAVC_CPP_HEADER_ONLY_LIB})


# Add test
if (NOT_SUBPROJECT)
    find_package(GTest REQUIRED)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
