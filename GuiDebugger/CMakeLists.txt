

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui)
set(Qt_LIBRARIES Qt6::Core Qt6::Quick Qt6::Gui)
set(Qt_LIBRARY_DIR ${Qt6_LIBRARY_DIR})
set(Qt_INCLUDE_DIR ${Qt6_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/build/include
                    ${PROJECT_SOURCE_DIR}/PolyDebugger)

add_executable(PolyGui
    offsetisland/plineoffsetislandsalgorithmview.cpp
    offsetisland/plineoffsetislandsalgorithmview.h
    offsetisland/PlineOffsetIslandsScene.qml

    combine/plinecombinealgorithmview.cpp
    combine/plinecombinealgorithmview.h
    combine/PlineCombineScene.qml

    settings/settings.h
    settings/settings.cpp
    settings/DebuggerSettings.qml

    offset/plineoffsetalgorithmview.cpp
    offset/plineoffsetalgorithmview.h
    offset/rawoffsetsegmentsnode.cpp
    offset/rawoffsetsegmentsnode.h
    offset/PlineOffsetScene.qml
    offset/spatialindexboundingboxesnode.h

    viewer/geometrycanvasitem.cpp
    viewer/geometrycanvasitem.h
    viewer/plinesegmentnode.cpp
    viewer/plinesegmentnode.h
    viewer/pointsetnode.cpp
    viewer/pointsetnode.h
    viewer/viewmodel.h
    viewer/viewmodel.cpp

    casedata.cpp
    casedata.h
    datamanager.h

    viewer/flatcolorgeometrynode.cpp
    viewer/flatcolorgeometrynode.h
    viewer/graphicshelpers.cpp
    viewer/graphicshelpers.h
    viewer/simplecirclenode.cpp
    viewer/simplecirclenode.h
    viewer/GeometrySceneView.qml

    main.cpp
    main.qml
    qml.qrc
)

target_compile_definitions(PolyGui
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(PolyGui
  PRIVATE ${Qt_LIBRARIES})
