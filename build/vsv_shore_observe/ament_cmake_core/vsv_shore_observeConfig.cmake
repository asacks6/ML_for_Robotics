# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_vsv_shore_observe_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED vsv_shore_observe_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(vsv_shore_observe_FOUND FALSE)
  elseif(NOT vsv_shore_observe_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(vsv_shore_observe_FOUND FALSE)
  endif()
  return()
endif()
set(_vsv_shore_observe_CONFIG_INCLUDED TRUE)

# output package information
if(NOT vsv_shore_observe_FIND_QUIETLY)
  message(STATUS "Found vsv_shore_observe: 0.0.0 (${vsv_shore_observe_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'vsv_shore_observe' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT vsv_shore_observe_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(vsv_shore_observe_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${vsv_shore_observe_DIR}/${_extra}")
endforeach()
