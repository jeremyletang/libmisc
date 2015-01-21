# min config
cmake_minimum_required (VERSION 2.8.1)
cmake_policy(SET CMP0042 NEW)

#include paths
set (LIBMISC_INC ${CMAKE_SOURCE_DIR}/include)

# lib paths
set (LIBMISC_LIB ${CMAKE_BINARY_DIR})

include_directories (${LIBMISC_INC})

project (libmisc C)

file (GLOB headers "*.h")
file (GLOB sources "*.c")

set (DIRS "src" "include")

foreach (dir ${DIRS})
   file (GLOB h_${dir} "${dir}/*.h")
   file (GLOB s_${dir} "${dir}/*.c")
   source_group (${dir} FILES ${s_${dir}} ${h_${dir}})
   set (sources ${sources} ${s_${dir}})
   set (header ${headers} ${h_${dir}})
endforeach ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu11")
endif()

add_library (misc SHARED ${sources})

add_subdirectory (tests)