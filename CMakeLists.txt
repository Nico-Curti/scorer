cmake_minimum_required (VERSION 3.8)
project (Scorer)
enable_language (CXX)

if (EXISTS "$ENV{WORKSPACE}/sysconfig/cmake/physycom_config.cmake")
  message(STATUS "Enabling physycom settings")
  include("$ENV{WORKSPACE}/sysconfig/cmake/physycom_config.cmake")
else()
  message(STATUS "Unable to find physycom settings file")
endif()

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set (HPP_DIR ${CMAKE_SOURCE_DIR}/include) # directory of hpp
set (TST_DIR ${CMAKE_SOURCE_DIR}/example) # runtest directory
set (PYC_DIR ${CMAKE_SOURCE_DIR}/pyc)     # cython directory

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  if( OUTPUTCONFIG STREQUAL "RELEASE")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} $ENV{HOME}/bin)
  else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG})
  endif()
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND FORCE_LLVM_CPP_STDLIB)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND ENABLE_PROFILING)
  message(STATUS "Enabled profiling options")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /PROFILE")
  string(REPLACE "/INCREMENTAL" "" CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
endif()

include_directories(
                    ${HPP_DIR}
                    ${TST_DIR}
                    )

find_package(OpenMP)
if (OpenMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

# Include the CMake script UseCython.cmake.  This defines add_cython_module().
# Instruction for use can be found at the top of cmake/UseCython.cmake.
include( UseCython )

# With CMake, a clean separation can be made between the source tree and the
# build tree.  When all source is compiled, as with pure C/C++, the source is
# no-longer needed in the build tree.  However, with pure *.py source, the
# source is processed directly.  To handle this, we reproduce the availability
# of the source files in the build tree.
add_custom_target(  ReplicatePythonSourceTree ALL ${CMAKE_COMMAND} -P
                    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ReplicatePythonSourceTree.cmake
                    ${CMAKE_CURRENT_BINARY_DIR}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    )

enable_testing()
find_file( NOSETESTS_EXECUTABLE nosetests )
add_test( nosetests "${NOSETESTS_EXECUTABLE}" -v --with-xunit )

add_subdirectory(${PYC_DIR})

add_executable( example
                ${TST_DIR}/example.cpp
                ${HPP_DIR}/class_stats.h
                ${HPP_DIR}/overall_stats.h
                ${HPP_DIR}/common_stats.h
                ${HPP_DIR}/scorer.h
              )
