#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "oatpp::oatpp" for configuration "Debug"
set_property(TARGET oatpp::oatpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(oatpp::oatpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/oatpp.lib"
  )

list(APPEND _cmake_import_check_targets oatpp::oatpp )
list(APPEND _cmake_import_check_files_for_oatpp::oatpp "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/oatpp.lib" )

# Import target "oatpp::oatpp-test" for configuration "Debug"
set_property(TARGET oatpp::oatpp-test APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(oatpp::oatpp-test PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/oatpp-test.lib"
  )

list(APPEND _cmake_import_check_targets oatpp::oatpp-test )
list(APPEND _cmake_import_check_files_for_oatpp::oatpp-test "${_IMPORT_PREFIX}/lib/oatpp-1.3.0/oatpp-test.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
