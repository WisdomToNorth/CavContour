add_library(PolylineFactory
STATIC
    polylinefactory.hpp
    polylinefactory.cpp)

target_include_directories(PolylineFactory
    PUBLIC ${PROJECT_SOURCE_DIR}/build/include)

target_link_libraries(PolylineFactory
    PUBLIC
        ${CAVC_CPP_HEADER_ONLY_LIB}
        ${CAVC_C_API_LIB})
