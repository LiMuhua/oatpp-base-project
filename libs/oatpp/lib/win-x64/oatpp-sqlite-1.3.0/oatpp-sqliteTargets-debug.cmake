#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "oatpp::oatpp-sqlite" for configuration "Debug"
set_property(TARGET oatpp::oatpp-sqlite APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(oatpp::oatpp-sqlite PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/oatpp-sqlite.lib"
  )

list(APPEND _cmake_import_check_targets oatpp::oatpp-sqlite )
list(APPEND _cmake_import_check_files_for_oatpp::oatpp-sqlite "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/oatpp-sqlite.lib" )

# Import target "oatpp::sqlite" for configuration "Debug"
set_property(TARGET oatpp::sqlite APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(oatpp::sqlite PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/sqlite.lib"
  )

list(APPEND _cmake_import_check_targets oatpp::sqlite )
list(APPEND _cmake_import_check_files_for_oatpp::sqlite "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/sqlite.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
