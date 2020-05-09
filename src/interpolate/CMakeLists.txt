add_library(interpolate STATIC)

target_include_directories(interpolate
PUBLIC
  ../../include
)

target_sources(interpolate
PRIVATE
  ../../include/interpolate/bilinear_lookup.h
  ../../include/interpolate/linear_lookup.h
  bilinear_lookup.cpp
  linear_lookup.cpp
)

target_compile_features(interpolate
PRIVATE
  cxx_std_17
)

