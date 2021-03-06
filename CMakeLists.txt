project(mvd-parser)
cmake_minimum_required(VERSION 2.8)


set(VERSION_MAJOR "0")
set(VERSION_MINOR "9")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
      ${PROJECT_SOURCE_DIR}/CMake/portability
      ${PROJECT_SOURCE_DIR}/CMake/packages
      ${PROJECT_SOURCE_DIR}/CMake/config)

include(DefineInstallationPaths)
include(ReleaseDebugAutoFlags)


## find dependencies
find_package(Boost 1.41 REQUIRED COMPONENTS system)
find_package(HDF5 REQUIRED)


file(GLOB MVD_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/mvd/*)
file(GLOB MVD_HEADERS_BITS ${CMAKE_CURRENT_SOURCE_DIR}/include/mvd/*/*)


include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${BOOST_INCLUDE_DIR} ${HDF5_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/deps/highfive/include)

add_definitions(-DMVD_VERSION_MAJOR=\"${VERSION_MAJOR}\" -DMVD_VERSION_MINOR=\"${VERSION_MINOR}\")

aux_source_directory(src SRC_LIST)
add_executable(mvd-tool ${SRC_LIST} ${MVD_HEADERS} ${MVD_HEADERS_BITS})
target_link_libraries(mvd-tool ${HDF5_C_LIBRARIES} ${HDF5_HL_LIBRARIES})


install(TARGETS mvd-tool
        RUNTIME DESTINATION ${BIN_INSTALL_DIR} )

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mvd DESTINATION ${INCLUDE_INSTALL_DIR}/)


add_subdirectory(tests/unit)

