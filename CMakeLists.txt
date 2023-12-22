cmake_minimum_required(VERSION 3.21)
project(CavalierContoursDev)

SET(CAVC_HEADER_ONLY ON CACHE BOOL "using headers only")

# add subdir projects
add_subdirectory(NgCavlierContour)
add_subdirectory(interactiveui)
