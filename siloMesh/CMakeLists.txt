cmake_minimum_required(VERSION 2.6)
project(write-mesh)
enable_language(Fortran)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(HDF5)
find_package(Silo)

set(SOURCE_FILES silo_writeRead.f90)

add_executable(write-mesh ${SOURCE_FILES})

target_link_libraries(write-mesh ${HDF5_LIBRARY} ${Silo_LIBRARY} stdc++ sz z)
