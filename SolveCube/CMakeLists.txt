cmake_minimum_required(VERSION 3.5)

project(SolveCube VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -ftest-coverage -fprofile-arcs")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -ftest-coverage -fprofile-arcs")
set(CMAKE_EXE_LINKER_FLAGS "-ftest-coverage -fprofile-arcs")

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS QtGui REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS OpenGL REQUIRED)
find_package(Qt6 COMPONENTS OpenGLWidgets REQUIRED)
find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})

set(PROJECT_SOURCES
        mainwindow.cpp
        mainwindow.h
        main.cpp
        rubik.cpp
        rubik.h
        rubik.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SolveCube
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(SolveCube SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SolveCube
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SolveCube PRIVATE Qt6::Widgets)
target_link_libraries(SolveCube PRIVATE Qt6::OpenGL)
target_link_libraries(SolveCube PRIVATE Qt6::Gui)
target_link_libraries(SolveCube PRIVATE Qt6::Core)
target_link_libraries(SolveCube PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(SolveCube PRIVATE ${GLUT_LIBRARIES})
target_link_libraries(SolveCube PRIVATE ${OPENGL_LIBRARIES})

set (QT_USE_QTOPENGL TRUE)
set_target_properties(SolveCube PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SolveCube)
endif()
