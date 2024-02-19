cmake_minimum_required(VERSION 3.13)
project(mcswitch CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Use response files when linking objects because of the large number of source files
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
  # Required to silence "unused argument" warnings for -stdlib=libc++ when using distcc
  add_compile_options(-Wno-unused-command-line-argument)
  # Required to fix source paths in debug info when using distcc
  add_compile_options(-fdebug-prefix-map=/tmp=${CMAKE_CURRENT_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES_GAME ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.h)

add_executable(mcswitch ${SOURCES_GAME})

# Writing sources to a file so build.py script knows the sources
set(SOURCES_OUTPUT_FILE "${CMAKE_BINARY_DIR}/.build_sources")
file(WRITE ${SOURCES_OUTPUT_FILE} "")

get_target_property(SOURCES_COMBINED mcswitch SOURCES)

foreach (SOURCE ${SOURCES_COMBINED})
  file(APPEND ${SOURCES_OUTPUT_FILE} "${SOURCE}\n")
endforeach()

set(NN_SDK_MAJOR 4)
set(NN_SDK_MINOR 4)
set(NN_SDK_PATCH 1)
set(NN_SDK_TYPE "Release")

target_include_directories(mcswitch PRIVATE src)
target_include_directories(mcswitch PUBLIC lib/nnheaders/include)
target_compile_definitions(mcswitch PRIVATE NON_MATCHING)
target_compile_options(mcswitch PRIVATE -fno-exceptions)
target_compile_options(mcswitch PRIVATE -fno-strict-aliasing)
target_compile_options(mcswitch PRIVATE -Wall -Wextra -Wdeprecated)
target_compile_options(mcswitch PRIVATE -Wno-unused-parameter -Wno-unused-private-field)
target_compile_options(mcswitch PRIVATE -Wno-invalid-offsetof)
target_compile_options(mcswitch PRIVATE -Wextra-semi)
# target_compile_options(mcswitch PRIVATE -fno-inline)

add_definitions(-D SAFETY_CHECKS)
