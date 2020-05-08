find_path(RapidXML_INCLUDE_DIR
NAMES
  rapidxml.hpp
PATHS
  ${CMAKE_SOURCE_DIR}/external/rapidxml-1.13
)

set(RapidXML_VERSION "1.13")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RapidXML
FOUND_VAR RapidXML_FOUND
REQUIRED_VARS
  RapidXML_INCLUDE_DIR
)

if (RapidXML_FOUND AND NOT TARGET ::RapidXML)
  add_library(::RapidXML INTERFACE IMPORTED)
  set_target_properties(::RapidXML PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES
    ${RapidXML_INCLUDE_DIR}
  )
endif()

mark_as_advanced(
    RapidXML_INCLUDE_DIR
)
