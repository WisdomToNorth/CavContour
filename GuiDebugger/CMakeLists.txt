

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# QT
find_package(QT NAMES Qt6 Qt5 REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Quick REQUIRED)

set(Qt_LIBRARIES
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Gui)

set(Qt_LIBRARY_DIR ${Qt${QT_VERSION_MAJOR}_LIBRARY_DIR})
set(Qt_INCLUDE_DIR ${Qt${QT_VERSION_MAJOR}_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_executable(PolyGui

    viewer/GeoCanvasHelper.cpp
    viewer/GeoCanvasHelper.h
    viewer/segmentnode.cpp
    viewer/segmentnode.h
    viewer/PlineGraphicItem.cpp
    viewer/PlineGraphicItem.h
    viewer/viewmodel.h
    viewer/viewmodel.cpp
    viewer/drawstyle.h
    viewer/drawstyle.cpp
    viewer/vmparameter.h
    viewer/vmparameter.cpp
    viewer/flatcolorgeometrynode.cpp
    viewer/flatcolorgeometrynode.h
    viewer/graphicshelpers.cpp
    viewer/graphicshelpers.h
    viewer/simplecirclenode.cpp
    viewer/simplecirclenode.h

    casedata.cpp
    casedata.h
    datamanager.h
    main.cpp
    qml.qrc

    settings/settings.h
    settings/settings.cpp

    offsetisland/offsetview.h
    offsetisland/offsetview.cpp
)

target_include_directories(PolyGui
PRIVATE
    ${Qt_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/build/include
    ${PROJECT_SOURCE_DIR}/PolyDebugger)

target_compile_definitions(PolyGui
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(PolyGui
  PRIVATE ${Qt_LIBRARIES})
