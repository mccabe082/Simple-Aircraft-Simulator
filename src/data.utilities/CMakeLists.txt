add_library(data.utilities STATIC)

target_include_directories(data.utilities
PUBLIC
  ../../include
)

target_sources(data.utilities
PRIVATE
  ../../include/data.utilities/lookup_table_1d.h
  ../../include/data.utilities/lookup_table_2d.h
  lookup_table_1d.cpp
  lookup_table_2d.cpp
  bilinear_interpolation.cpp
  bilinear_interpolation.h
  xml_lookup_table_1d_reading.cpp
  xml_lookup_table_1d_reading.h
  xml_lookup_table_2d_reading.cpp
  xml_lookup_table_2d_reading.h
  linear_interpolation.cpp
  linear_interpolation.h
  nearest_neighbour2d.cpp
  nearest_neighbour2d.h
)

target_link_libraries(data.utilities
PRIVATE
  ::RapidXML
)

target_compile_features(data.utilities
PRIVATE
  cxx_std_17
)
