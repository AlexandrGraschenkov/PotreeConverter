cmake_minimum_required(VERSION 2.8)

project(Potree)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(LASZIP_ROOT "/Users/alex/Documents/helpers_progect/LAStools/LASzip")
set(LASZIP_INCLUDE_DIRS "${LASZIP_ROOT}/dll")
set(LASZIP_LIBRARY "${LASZIP_ROOT}/build/src/liblaszip.dylib")

#if(UNIX)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -pthread -lstdc++ -lstdc++fs -lm")
#    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lstdc++fs" )
#endif()

add_subdirectory(PotreeConverter)
