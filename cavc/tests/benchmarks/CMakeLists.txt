cmake_minimum_required(VERSION 3.21)

find_package(benchmark REQUIRED)

set(HelperFile
    benchmarkprofiles.h
    clipper/clipper.cpp
    clipper/clipper.hpp
    clipper/clipper_export.hpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/build/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/clipper
    )

macro(add_benchmark name)
    add_executable(${name} ${name}.cpp ${HelperFile})
    target_link_libraries(${name}
    PRIVATE
        ${CAVC_CPP_HEADER_ONLY_LIB}
        PolylineFactory
        benchmark::benchmark)

    if (MSVC)
        target_link_options(${name} PRIVATE $<$<CONFIG:RELWITHDEBINFO>:/PROFILE>)
    endif()
endmacro()

add_benchmark(offsetbenchmarks)
add_benchmark(spatialindexbenchmarks)
add_benchmark(extentsbenchmarks)
add_benchmark(areabenchmarks)
add_benchmark(pathlengthbenchmarks)
add_benchmark(windingnumberbenchmarks)
add_benchmark(combinebenchmarks)
add_benchmark(clipperbenchmarks)

