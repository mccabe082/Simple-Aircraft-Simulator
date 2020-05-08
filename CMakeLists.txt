cmake_minimum_required(VERSION 3.5)
enable_language(CXX)
project(simple-flightpath-simulator)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBIITY_INLINES_HIDDEN YES)

### Installation ####################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin CACHE PATH "..." FORCE)
endif()

### External Libraries ##############

set(FindModuleDir ${CMAKE_SOURCE_DIR}/cmake
CACHE STRING "path to directory containing the Find<Module>.cmake modules"
)
mark_as_advanced(FindModuleDir)

list(APPEND CMAKE_MODULE_PATH ${FindModuleDir})
find_package(Boost REQUIRED MODULE)
find_package(Catch2 REQUIRED MODULE)

### Testing #########################
ENABLE_TESTING()
include(CTest)

### Main Body #######################
add_subdirectory(src)

