add_executable(data.utilities.test)

target_sources(data.utilities.test
PRIVATE
  bilinear_interpolation.test.cpp
  linear_interpolation.test.cpp
  nearest_neighbour2d.test.cpp
)

target_include_directories(data.utilities.test
PRIVATE
  ${CMAKE_SOURCE_DIR}/include 
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(data.utilities.test
PRIVATE
  $<TARGET_OBJECTS:data.utilities>
  ::Catch2
)

add_test("data.utilities.test" ${CMAKE_BINARY_DIR}/src/interpolate_test/Debug/data.utilities.test.exe)