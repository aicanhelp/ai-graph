cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(opengl-sb5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLU REQUIRED glu)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

include(GNUInstallDirs)
include_directories(include)
include_directories(OpenEXR/include)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLU_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLUT_INCLUDE_DIRS})

#message("${GLU_INCLUDE_DIRS}")

if(WIN32)
    set(COMMON_LIBS GLTools ${OPENGL_LIBRARIES} optimized glfw3 debug glfw3_d)
elseif (UNIX)
    set(COMMON_LIBS GLTools ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} ${GLU_LIBRARIES} GL rt dl)
else()
    set(COMMON_LIBS GLTools)
endif()

add_subdirectory(src)
