cmake_minimum_required(VERSION 3.19)
project(ProjectQT LANGUAGES CXX)
 
# ✅ Use Qt6 with required modules
find_package(Qt6 6.9.0 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
 
qt_standard_project_setup()
 
# ✅ Add your executable
qt_add_executable(ProjectQT
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    
    screens/scenecreator.h 
    screens/scenecreator.cpp

    widgets/shapes_sidebar.h
    widgets/shapes_sidebar.cpp 

    widgets/scene_renderer.h 
    widgets/scene_renderer.cpp 

    widgets/transformation_sidebar.h 
    widgets/transformation_sidebar.cpp

    includes/shape.h 
    includes/shapes.h 
    includes/threed-utils.h 
    includes/transformations.h 
    includes/drawable-shape.h 
    includes/scene.h 
    includes/file-utils.h

    src/shapes/cuboid.cpp 
    src/shapes/cylinder.cpp 
    src/shapes/sphere.cpp 
    src/threed-utils.cpp 
    src/transformations.cpp
    src/scene.cpp
    src/file-utils.cpp
    src/drawable-shape.cpp
    
    # myopenglwidget.cpp
    # myopenglwidget.h

    test/test-window.h
    test/test-window.cpp
    test/sidebar.h 
    test/sidebar.cpp 
    test/point.h
    test/bezier_curve.h 
    test/bezier_curve.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/shapes
    ${PROJECT_SOURCE_DIR}/widgets
    ${PROJECT_SOURCE_DIR}/screens
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/test
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

