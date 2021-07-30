cmake_minimum_required(VERSION 3.5)
project(gear)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include)
include_directories(src)
include_directories(src/base)
include_directories(external)
include_directories(external/asio)

add_definitions(-DMONGOCXX_STATIC -DBSONCXX_STATIC -DMONGOC_STATIC -DBSON_STATIC)
add_definitions(-DNDEBUG)
add_definitions(-DASIO_STANDALONE)
add_definitions(-DBIG_VARLEN)

#set(MEM_DEBUG_MONITOR1 "-fsanitize=address")
#set(MEM_DEBUG_MONITOR2 "-fsanitize=leak")
#set(CMAKE_CXX_FLAGS "-std=c++11 -g -O2 -march=corei7 -Wall -Wno-unused-function -Wno-class-memaccess -Wno-sign-compare -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "-std=c++11 -g -O2 -march=corei7 -Wall -fvisibility=hidden")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
#aux_source_directory(. SOURCES)

file(GLOB INCLUDE_HEADERS "include/*.h" "include/*.hpp")
file(GLOB BASE_SOURCES "src/base/*.h" "src/base/*.cpp")
file(GLOB NETWORK_SOURCES "src/network/*.h" "src/network/*.cpp")
file(GLOB_RECURSE EXTERNAL_SOURCES "external/*.h", "external/*.hpp", "external/*.cpp")
file(GLOB SOURCES "src/*.cpp")
# 源码分组
#source_group(includes ${INCLUDE_HEADERS})
#source_group(sources ${SOURCES})
source_group(external ${EXTERNAL_SOURCES})
source_group(base FILES ${BASE_SOURCES})
source_group(network FILES ${NETWORK_SOURCES})
source_group(external FILES ${EXTERNAL_SOURCES})

add_library(gear STATIC 
    ${SOURCES}
    ${INCLUDE_HEADERS}
    ${BASE_SOURCES}
    ${NETWORK_SOURCES}
    ${EXTERNAL_SOURCES}
)
