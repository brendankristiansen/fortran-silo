cmake_minimum_required(VERSION 3.8)
project(silof)
enable_language(Fortran)

set (CMAKE_Fortran_FLAGS_RELEASE "-funroll-all-loops -fno-f2c -O3")
set (CMAKE_Fortran_FLAGS_DEBUG   "-fno-f2c -O0 -g")

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Silo)
find_package(HDF5)

set(SOURCE_FILES silof.f90 silof_wrapper.c generate-data.c silof_wrapper.h)
add_executable(silof ${SOURCE_FILES})

target_link_libraries(silof ${HDF5_LIBRARY} ${Silo_LIBRARY} stdc++ sz z)