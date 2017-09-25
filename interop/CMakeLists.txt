cmake_minimum_required(VERSION 3.7)
project(hdf5_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(HDF5)
find_package(Silo)


set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES c_wrapper.c)
add_executable(silotest ${SOURCE_FILES})

target_link_libraries(silotest ${HDF5_LIBRARY} ${Silo_LIBRARY} stdc++ sz z)
