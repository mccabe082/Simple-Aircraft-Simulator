add_executable(rapidxmlTest)

target_sources(rapidxmlTest
PRIVATE
  main.cpp
)

target_link_libraries(rapidxmlTest
PRIVATE
  ::Catch2
  ::RapidXML
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/NPTG-metadata.xml
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test("test" ${CMAKE_BINARY_DIR}/external/rapidxml_test/Debug/rapidxmlTest.exe)