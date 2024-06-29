cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE D:/CODE/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(
    NgPolyDebugger
    VERSION 0.1.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
enable_language(C)

add_subdirectory(cavc)
add_subdirectory(clipper2)
add_subdirectory(ngpoly)

add_subdirectory(GuiDebugger)
