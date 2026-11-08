#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cv_bridge2::cv_bridge2" for configuration ""
set_property(TARGET cv_bridge2::cv_bridge2 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(cv_bridge2::cv_bridge2 PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "rcpputils::rcpputils"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libcv_bridge2.so"
  IMPORTED_SONAME_NOCONFIG "libcv_bridge2.so"
  )

list(APPEND _cmake_import_check_targets cv_bridge2::cv_bridge2 )
list(APPEND _cmake_import_check_files_for_cv_bridge2::cv_bridge2 "${_IMPORT_PREFIX}/lib/libcv_bridge2.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
