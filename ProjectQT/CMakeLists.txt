cmake_minimum_required(VERSION 3.19)
project(ProjectQT LANGUAGES CXX)
 
# ✅ Use Qt6 with required modules
find_package(Qt6 6.9.0 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Concurrent)
 
qt_standard_project_setup()

qt_add_resources(RESOURCES resources.qrc)
 
# ✅ Add your executable
qt_add_executable(ProjectQT
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    screen_selector_dialog.h 
    screen_selector_dialog.cpp 
    
    # scene creator
    scene_creator/scene_creator.h 
    scene_creator/scene_creator.cpp
    scene_creator/shapes_sidebar.h
    scene_creator/shapes_sidebar.cpp 
    scene_creator/scene_renderer.h 
    scene_creator/scene_renderer.cpp 
    scene_creator/transformation_sidebar.h 
    scene_creator/transformation_sidebar.cpp

    # bezier sketcher
    bezier_sketcher/bezier_sketcher.h 
    bezier_sketcher/bezier_sketcher.cpp
    bezier_sketcher/bezier_sidebar.h 
    bezier_sketcher/bezier_sidebar.cpp
    bezier_sketcher/bezier_renderer.h
    bezier_sketcher/bezier_renderer.cpp

    # sketcher
    sketcher/sketcher_screen.cpp
    sketcher/sketcher_screen.h
    sketcher/sketch_renderer.h 
    sketcher/sketch_renderer.cpp

    # geometry headers
    includes/shape.h 
    includes/shapes.h 
    includes/threed-utils.h 
    includes/transformations.h 
    includes/drawable-shape.h 
    includes/scene.h 
    includes/file-utils.h
    includes/point.h
    includes/bezier_curve.h
    includes/sketcher_primitives.h 
    includes/sketcher.h 
    includes/boolean2d.h 

    # geometry sources
    src/shapes/cuboid.cpp 
    src/shapes/cylinder.cpp 
    src/shapes/sphere.cpp 
    src/threed-utils.cpp 
    src/transformations.cpp
    src/scene.cpp
    src/file-utils.cpp
    src/drawable-shape.cpp
    src/bezier_curve.cpp
    src/sketcher.cpp 
    src/boolean2d.cpp

    integration/mainscreen.h 
    integration/mainscreen.cpp 

    model_editor/model_editor.h
    model_editor/model_editor.cpp

    ${RESOURCES}
)

include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/shapes

    ${PROJECT_SOURCE_DIR}/scene_creator
    ${PROJECT_SOURCE_DIR}/sketcher
    ${PROJECT_SOURCE_DIR}/bezier_sketcher

    ${PROJECT_SOURCE_DIR}/test
    ${PROJECT_SOURCE_DIR}/integration 
    ${PROJECT_SOURCE_DIR}/model_editor
)
 
# ✅ Link Qt modules and system OpenGL (opengl32 for Windows)
target_link_libraries(ProjectQT
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        opengl32
        Qt6::Concurrent
)
 
include(GNUInstallDirs)
 
# ✅ Install targets and deployment script
install(TARGETS ProjectQT
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
 
qt_generate_deploy_app_script(
    TARGET ProjectQT
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
 
install(SCRIPT ${deploy_script})

