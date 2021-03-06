# FindVLE.cmake
# =============

# Try to find VLE
#
# Copyright 2012 INRA
# Gauthier Quesnel <quesnel@users.sourceforge.net>
#
# Distributed under the OS-approved BSD License (the "License");
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#
# Once done this will define
#
#  VLE_FOUND - system has VLE
#  VLE_INCLUDE_DIRS - the VLE include directory
#  VLE_LIBRARY_DIRS - Directories containing libraries to link
#  VLE_LIBRARIES - Link these to use shared libraries of VLE
#
# Options:
#  
#  FIND_VLE_USING_CMAKE - If true, on windows, use cmake for finding GVLE, 
#                         else use pkgconfig 
#

#=============================================================================
#
# Changelog
# ---------
#
# 1.0 Initial version.
#
# Usage
# -----
#
# find_package(VLE REQUIRED)
#
#=============================================================================

#
# Set default behavior of find vle
#

if (WIN32)
  if (DEFINED FIND_VLE_USING_CMAKE)
     set (_find_vle_using_cmake ${FIND_VLE_USING_CMAKE})
  else (DEFINED FIND_VLE_USING_CMAKE)
     set (_find_vle_using_cmake 1)
  endif (DEFINED FIND_VLE_USING_CMAKE)
else (WIN32)
  set (_find_vle_using_cmake 0)
endif (WIN32)

#
# Find VLE
#

if (${_find_vle_using_cmake})

  if (NOT VLE_INCLUDE_DIRS)
    find_path(VLE_INCLUDE_DIRS vle/vle.hpp PATHS
      /usr/include
      /usr/local/include
      $ENV{HOME}/usr/include
      $ENV{VLE_BASEPATH}/include
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\VLE Development Team\\VLE 1.1.0;Path]/include"
      PATH_SUFFIXES vle-1.1)
  endif ()

  if (NOT VLE_LIBRARIES)
    find_library(VLE_LIBRARIES
      NAMES vle-1.1 libvle-1.1
      HINTS $ENV{HOME}/usr $ENV{VLE_BASEPATH} 
      PATH_SUFFIXES lib lib64
      PATHS  
        /usr
        /usr/local 
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\VLE Development Team\\VLE 1.1.0\\;Path]/lib")
  endif ()

  if (NOT VLE_LIBRARIES OR NOT VLE_INCLUDE_DIRS)
    message(STATUS "VLE include directories: ${VLE_INCLUDE_DIR}")
    message(STATUS "VLE libraries: ${VLE_LIBRARIES}")
  endif ()

  # handle the QUIETLY and REQUIRED arguments and set VLE_FOUND to TRUE if
  # all listed variables are TRUE
  include(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(VLE REQUIRED_VARS VLE_LIBRARIES
    VLE_INCLUDE_DIRS)

  set (VLE_LIBRARY_DIRS "")

else (${_find_vle_using_cmake})

  include(FindPackageHandleStandardArgs)
  find_package(PkgConfig REQUIRED)
  PKG_CHECK_MODULES(VLE vle-1.1 REQUIRED)

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(VLE REQUIRED_VARS
    VLE_LIBRARIES
    VLE_LIBRARY_DIRS
    VLE_INCLUDE_DIRS)

endif (${_find_vle_using_cmake})

mark_as_advanced(VLE_INCLUDE_DIRS VLE_LIBRARIES VLE_LIBRARY_DIRS)
