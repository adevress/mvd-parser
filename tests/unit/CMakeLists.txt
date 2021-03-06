
enable_testing()

find_package(Boost 1.41 REQUIRED COMPONENTS filesystem system unit_test_framework)


SET(MVD2_TEST_FILE ${CMAKE_SOURCE_DIR}/tests/circuit.mvd2)
SET(MVD3_TEST_FILE ${CMAKE_SOURCE_DIR}/tests/circuit.mvd3)


add_definitions(-DMVD2_FILENAME="${MVD2_TEST_FILE}")
add_definitions(-DMVD3_FILENAME="${MVD3_TEST_FILE}")
add_definitions(-Wno-unused-local-typedefs)

include_directories(${HDF5_INCLUDE_DIRS})



## mvd2
file(GLOB  tests_mvd2_src "*mvd2.cpp")
add_executable(test_mvd2 ${tests_mvd2_src})

target_link_libraries(test_mvd2 ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES})

add_test(NAME test_parser_mvd2 COMMAND test_mvd2)


#mvd3
file(GLOB  tests_mvd3_src "*mvd3.cpp")
add_executable(test_mvd3 ${tests_mvd3_src})

target_link_libraries(test_mvd3 ${Boost_UNIT_TEST_FRAMEWORK_LIBRARIES} ${HDF5_LIBRARIES})

add_test(NAME test_parser_mvd3 COMMAND test_mvd3)
