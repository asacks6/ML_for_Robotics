# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_shore_follower_observe_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED shore_follower_observe_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(shore_follower_observe_FOUND FALSE)
  elseif(NOT shore_follower_observe_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(shore_follower_observe_FOUND FALSE)
  endif()
  return()
endif()
set(_shore_follower_observe_CONFIG_INCLUDED TRUE)

# output package information
if(NOT shore_follower_observe_FIND_QUIETLY)
  message(STATUS "Found shore_follower_observe: 0.0.0 (${shore_follower_observe_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'shore_follower_observe' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT shore_follower_observe_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(shore_follower_observe_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${shore_follower_observe_DIR}/${_extra}")
endforeach()
