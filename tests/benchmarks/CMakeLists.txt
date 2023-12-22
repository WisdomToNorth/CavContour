cmake_minimum_required(VERSION 3.11)

find_package(benchmark REQUIRED)

set(ClipperFile
${CMAKE_CURRENT_SOURCE_DIR}/clipper/clipper.cpp
${CMAKE_CURRENT_SOURCE_DIR}/clipper/clipper.hpp
${CMAKE_CURRENT_SOURCE_DIR}/clipper/clipper_export.hpp
)

macro(add_benchmark name)
  add_executable(${name} ${name}.cpp ${ClipperFile})
  target_link_libraries(${name}
    PRIVATE ${CAVC_CPP_HEADER_ONLY_LIB})
  target_link_libraries(${name}
    PRIVATE PolylineFactory)
  target_link_libraries(${name}
    PRIVATE benchmark::benchmark)
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
# target_link_libraries(clipperbenchmarks
#   PRIVATE clipper_static)
