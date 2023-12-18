# Install script for directory: /home/dean/Wisconsin/cyclus_fusion/Fusion/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/dean/.local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  set(CMAKE_OBJDUMP "/home/dean/miniconda3/envs/cyclus/bin/x86_64-conda-linux-gnu-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fusion" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so"
         RPATH "/home/dean/.local/lib:/home/dean/.local/lib/cyclus:/home/dean/miniconda3/envs/cyclus/lib:/home/dean/miniconda3/envs/cyclus/lib/cyclus:/home/dean/.local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cyclus" TYPE SHARED_LIBRARY FILES "/home/dean/Wisconsin/cyclus_fusion/Fusion/build/lib/cyclus/fusion/libfusion.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so"
         OLD_RPATH "/home/dean/.local/lib:/home/dean/.local/lib/cyclus:/home/dean/miniconda3/envs/cyclus/lib:/home/dean/miniconda3/envs/cyclus/lib/cyclus:/home/dean/.local/lib:"
         NEW_RPATH "/home/dean/.local/lib:/home/dean/.local/lib/cyclus:/home/dean/miniconda3/envs/cyclus/lib:/home/dean/miniconda3/envs/cyclus/lib/cyclus:/home/dean/.local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/dean/miniconda3/envs/cyclus/bin/x86_64-conda-linux-gnu-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cyclus/libfusion.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fusion" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "fusion_testing" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests"
         RPATH "/home/dean/.local/lib:/home/dean/.local/lib/cyclus:/home/dean/miniconda3/envs/cyclus/lib:/home/dean/miniconda3/envs/cyclus/lib/cyclus:/home/dean/.local/lib:/home/dean/.local/lib/cyclus")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/dean/Wisconsin/cyclus_fusion/Fusion/build/bin/fusion_unit_tests")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests"
         OLD_RPATH "/home/dean/.local/lib:/home/dean/.local/lib/cyclus:/home/dean/miniconda3/envs/cyclus/lib:/home/dean/miniconda3/envs/cyclus/lib/cyclus:/home/dean/.local/lib:/home/dean/Wisconsin/cyclus_fusion/Fusion/build/lib/cyclus/fusion:/home/dean/.local/lib/cyclus:"
         NEW_RPATH "/home/dean/.local/lib:/home/dean/.local/lib/cyclus:/home/dean/miniconda3/envs/cyclus/lib:/home/dean/miniconda3/envs/cyclus/lib/cyclus:/home/dean/.local/lib:/home/dean/.local/lib/cyclus")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/dean/miniconda3/envs/cyclus/bin/x86_64-conda-linux-gnu-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fusion_unit_tests")
    endif()
  endif()
endif()

