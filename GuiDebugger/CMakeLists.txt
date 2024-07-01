

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
set(QML_IMPORT_PATH ${Qt${QT_VERSION_MAJOR}_QML_IMPORT_PATH})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


add_executable(PolyGui

    viewer/segmentnode.cpp
    viewer/segmentnode.h
    viewer/PlineGraphicItem.cpp
    viewer/PlineGraphicItem.h
    viewer/caseviewmodel.h
    viewer/caseviewmodel.cpp
    viewer/drawstyle.h
    viewer/drawstyle.cpp
    viewer/vmparameter.h
    viewer/vmparameter.cpp
    viewer/GeoNode.cpp
    viewer/GeoNode.h
    viewer/simplecirclenode.cpp
    viewer/simplecirclenode.h
    viewer/Viewer2d.h
    viewer/Viewer2d.cpp

    CaseCreator.h
    CaseCreator.cpp
    DocManager.cpp
    DocManager.h
    DocData.h
    DocData.cpp
    main.cpp
    qml.qrc

    settings/settings.h
    settings/settings.cpp

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
