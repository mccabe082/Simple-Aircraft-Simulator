add_library(interpolate STATIC)

target_include_directories(interpolate
PUBLIC
  ../../include
)

target_sources(interpolate
PRIVATE
  ../../include/interpolate/lookup1d.h
  ../../include/interpolate/lookup2d.h
  bilinear_lookup.cpp
  bilinear_lookup.h
  xml_lookup_reading.cpp
  xml_lookup_reading.h
  linear_lookup.cpp
  linear_lookup.h
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
