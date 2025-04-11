cmake_minimum_required(VERSION 3.19)
project(ProjectQT LANGUAGES CXX)
 
# ✅ Use Qt6 with required modules
find_package(Qt6 6.9.0 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
 
qt_standard_project_setup()
 
# ✅ Add your executable
qt_add_executable(ProjectQT
    WIN32 MACOSX_BUNDLE
    main.cpp
    # mainwindow.cpp
    # mainwindow.h
    # mainwindow.ui
    myopenglwidget.cpp
    myopenglwidget.h
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