add_executable(interpolateTest)

target_sources(interpolateTest
PRIVATE
  linear_lookup.test.cpp
)

target_include_directories(interpolateTest
PRIVATE
  ${CMAKE_SOURCE_DIR}/include 
  ${CMAKE_SOURCE_DIR}/src 
)

target_link_libraries(interpolateTest
PRIVATE
  $<TARGET_OBJECTS:interpolate>
  ::Catch2
)

add_test("interpolateTest" ${CMAKE_BINARY_DIR}/src/interpolate_test/Debug/interpolateTest.exe)