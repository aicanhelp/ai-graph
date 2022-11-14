# Install script for directory: /home/modongsong/workspace/github-aican/ai-graph/content/opengl-sb5/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/GLTools/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter01/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter02/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter03/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter04/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter05/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter06/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter07/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter08/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter09/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter10/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter11/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter12/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter13/cmake_install.cmake")
  include("/home/modongsong/workspace/github-aican/ai-graph/content/build-opengl-sb5-Desktop_Qt_6_4_0_GCC_64bit-Debug/src/Chapter15/cmake_install.cmake")

endif()

