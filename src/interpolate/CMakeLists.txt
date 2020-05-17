add_library(interpolate STATIC)

target_include_directories(interpolate
PUBLIC
  ../../include
)

target_sources(interpolate
PRIVATE
  ../../include/interpolate/lookup_table_1d.h
  ../../include/interpolate/lookup_table_2d.h
  bilinear_interpolation.cpp
  bilinear_interpolation.h
  xml_lookup_table_2d_reading.cpp
  xml_lookup_table_2d_reading.h
  linear_interpolation.cpp
  linear_interpolation.h
  nearest_neighbour2d.cpp
  nearest_neighbour2d.h
)

target_link_libraries(interpolate
PRIVATE
  ::RapidXML
)

target_compile_features(interpolate
PRIVATE
  cxx_std_17
)
