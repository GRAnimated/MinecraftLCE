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

target_include_directories(mcswitch PUBLIC lib/stb_image)
target_include_directories(mcswitch PUBLIC lib/libpng)
target_include_directories(mcswitch PUBLIC lib)

target_compile_definitions(mcswitch PRIVATE NON_MATCHING)
target_compile_options(mcswitch PRIVATE -fno-exceptions)
target_compile_options(mcswitch PRIVATE -fno-strict-aliasing)
target_compile_options(mcswitch PRIVATE -Wall -Wextra -Wdeprecated)
target_compile_options(mcswitch PRIVATE -Wno-unused-parameter -Wno-unused-private-field)
target_compile_options(mcswitch PRIVATE -Wno-invalid-offsetof)
target_compile_options(mcswitch PRIVATE -Wextra-semi)
target_compile_options(mcswitch PRIVATE -fno-inline)

add_definitions(-D SAFETY_CHECKS)

# Add zlib and libpng as subdirectories
#add_subdirectory(lib/zlib)
#add_subdirectory(lib/libpng)

# Include necessary directories from submodules
#include_directories("${PROJECT_SOURCE_DIR}/lib/zlib" "${PROJECT_SOURCE_DIR}/lib/libpng")

# Link with zlib and libpng libraries statically
#target_link_libraries(mcswitch PRIVATE zlibstatic png)








## include(FetchContent)
## 
## # zlib
## FetchContent_Declare(
##   zlib
##   GIT_REPOSITORY https://github.com/madler/zlib.git
##   GIT_TAG        9712272c78b9d9c93746d9c8e156a3728c65ca72
## )
## FetchContent_Populate(zlib)
## list(FILTER zlib_POPULATED_INCLUDE_DIRS EXCLUDE REGEX ".*/zconf\\.h$")
## 
## # Specify the ZLIB_LIBRARY variable
## set(ZLIB_LIBRARY ${zlib_POPULATED_LIBRARIES})
## 
## # libpng
## FetchContent_Declare(
##   libpng
##   GIT_REPOSITORY https://github.com/pnggroup/libpng.git
##   GIT_TAG        809355b4aa84ae06f9a4e063c7e9d22fd7930170
## )
## FetchContent_Populate(libpng)
## 
## # stb_image.h
## FetchContent_Declare(
##   stb_image
##   GIT_REPOSITORY https://github.com/nothings/stb.git
##   GIT_TAG        ec9db6f84b39988a6a3375058e97598fe63fca4e
## )
## FetchContent_MakeAvailable(stb_image)
#
## target_link_libraries(mcswitch PRIVATE zlib libpng16::libpng16)
#
## libpng configurable options
#set(PNG_SHARED ON CACHE BOOL "" FORCE)
#set(PNG_STATIC ON CACHE BOOL "" FORCE)
#set(PNG_EXECUTABLES OFF CACHE BOOL "" FORCE) # we only want lib
#set(PNG_TESTS OFF CACHE BOOL "" FORCE) # we only want lib
#set(SKIP_INSTALL_ALL OFF CACHE BOOL "" FORCE) # we only want lib
#
#include_directories(${PROJECT_SOURCE_DIR}/lib/libpng)
#
## Find ZLIB using ZLIB_ROOT variable
#find_package(ZLIB REQUIRED)
#
#if(ZLIB_FOUND)
#    include_directories(${ZLIB_INCLUDE_DIRS})
#endif()
#
#add_subdirectory(lib/zlib)
#add_subdirectory(lib/libpng)