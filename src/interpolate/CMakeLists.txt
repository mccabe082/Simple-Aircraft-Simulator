add_library(interpolate STATIC)

target_include_directories(interpolate
PUBLIC
  ../../include
)

target_sources(interpolate
PRIVATE
  ../../include/interpolate/lookup1D.h
  bilinear_lookup.cpp
  bilinear_lookup.h
  linear_lookup.cpp
  linear_lookup.h
)

target_compile_features(interpolate
PRIVATE
  cxx_std_17
)

