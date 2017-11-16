cmake_minimum_required (VERSION 2.6)
project (dev-big)
enable_language (Fortran)

set (CMAKE_Fortran_FLAGS_RELEASE "-funroll-all-loops -fno-f2c -O3")
set (CMAKE_Fortran_FLAGS_DEBUG   "-fno-f2c -O0 -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(HDF5)
find_package(Silo)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES wrapper.c silo_readwrite.f90)

add_executable(interop-test ${SOURCE_FILES})

target_link_libraries(interop-test ${HDF5_LIBRARY} ${Silo_LIBRARY} stdc++ sz z)