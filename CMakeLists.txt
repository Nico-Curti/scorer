cmake_minimum_required (VERSION 3.8)

# Scorer Version
set (SCORER_MAJOR    2)
set (SCORER_MINOR    0)
set (SCORER_REVISION 2)
set (SCORER_VERSION ${SCORER_MAJOR}.${SCORER_MINOR}.${SCORER_REVISION})

set (CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/Nico-Curti/scorer")
set (CMAKE_PROJECT_DESCRIPTION "Multi-class scorer computation library")

message (STATUS "scorer VERSION: ${SCORER_VERSION}")

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
  message(STATUS "VCPKG found: $ENV{VCPKG_ROOT}")
  message(STATUS "Using VCPKG integration")
  message(STATUS "VCPKG_MANIFEST_FEATURES: ${VCPKG_MANIFEST_FEATURES}")
  if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
    message(STATUS "Setting default vcpkg target triplet to $ENV{VCPKG_DEFAULT_TRIPLET}")
    set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET})
  endif()
endif()

project (scorer LANGUAGES CXX VERSION ${SCORER_VERSION} DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION})

enable_language(CXX)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions (-DMAJOR=${SCORER_MAJOR} -DMINOR=${SCORER_MINOR} -DREVISION=${SCORER_REVISION})

#################################################################
#                         COMPILE OPTIONS                       #
#################################################################

option (OMP        "Enable OpenMP                  support" OFF)
option (PYWRAP     "Enable Python wrap compilation        " OFF)
option (BUILD_DOCS "Enable Documentaion builid     support" OFF)

#################################################################
#                         SETTING VARIABLES                     #
#################################################################

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

if ( NOT APPLE )
  set (CMAKE_SKIP_BUILD_RPATH             FALSE )
  set (CMAKE_BUILD_WITH_INSTALL_RPATH     FALSE )
  set (CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE  )
endif()

# make sure that the default is a RELEASE
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}" CACHE PATH "Install prefix" FORCE)
endif()

if ( CMAKE_COMPILER_IS_GNUCXX )
  add_compile_options (-Wall -Wextra -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -Wno-narrowing -Wpedantic)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    string (REGEX REPLACE "-O[0123]" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )
    set (CMAKE_CXX_FLAGS_RELEASE "")
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    # The fast-math operations are not supported by HYPOTHESIS Python package!
    #string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG" )
    set (CMAKE_CXX_FLAGS_DEBUG "")
  endif()
endif()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  add_compile_options(-Wno-deprecated -Wno-writable-strings)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    string (REGEX REPLACE "-O0" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    #string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG" )
  endif()
endif()

if (MSVC)
  set (CMAKE_CXX_FLAGS "/wd4013 /wd4018 /wd4028 /wd4047 /wd4068 /wd4090 /wd4101 /wd4113 /wd4133 /wd4190 /wd4244 /wd4267 /wd4305 /wd4477 /wd4996 /wd4819 /fp:fast ${CMAKE_CXX_FLAGS}")
  string (REGEX REPLACE "/O2" "/Ox" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  add_definitions (-D_CRT_RAND_S)
  add_definitions (-DNOMINMAX)
  #add_definitions (-D_USE_MATH_DEFINES)
  add_definitions (-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
  set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG ("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE AND NOT MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
endif ()


#################################################################
#                         PARSE OPTIONS                         #
#################################################################

if (OMP)
  find_package(OpenMP REQUIRED)
  if (OPENMP_FOUND)
    message(STATUS "OpenMP found")
    # It is not more required by the current version
    # if (OpenMP_CXX_VERSION_MAJOR LESS 4)
    #   message(FATAL_ERROR " Your OpenMP is too old. Required OpenMP 4.0. Please upgrade.")
    # endif()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    if (APPLE)
      list(APPEND linked_libs OpenMP::OpenMP_CXX)
    endif()
  endif()
else()
  message(STATUS "OpenMP - disabled")
endif()

#################################################################
#                         SETTING DIRECTORIES                   #
#################################################################

set(INSTALL_BIN_DIR "${CMAKE_CURRENT_LIST_DIR}/bin" CACHE PATH "Path where exe and dll will be installed")
set(INSTALL_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/lib" CACHE PATH "Path where lib will be installed")

set(INSTALL_INCLUDE_DIR  "include/scorer"  CACHE PATH "Path where headers will be installed")
set(INSTALL_CMAKE_DIR    "share/scorer"    CACHE PATH "Path where cmake configs will be installed")

set(CMAKE_DEBUG_POSTFIX d)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/include/version.h.in"
  "${CMAKE_CURRENT_LIST_DIR}/include/version.h" @ONLY
)

file (GLOB SCORER_SRC    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"  )
file (GLOB SCORER_HEADER "${CMAKE_CURRENT_LIST_DIR}/include/*.h")

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

find_package (Python REQUIRED COMPONENTS Interpreter)
add_custom_target(make_scorer_obj ALL
  COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/utils/make_script.py"
  COMMENT "Generate scorer object using dependency graph..."
)

if (PYWRAP)
  include( UseCython )
  add_custom_target(make_scorer_cython ALL
    COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/utils/make_cython.py"
    COMMENT "Generate scorer cython wrap..."
  )
  add_dependencies(make_scorer_cython make_scorer_obj)
endif ()

set (scorerlib scorer)

# allow the export of LD_LIBRARY_PATH env variable
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

configure_file(
  "${CMAKE_CURRENT_LIST_DIR}/Scorer.pc.in"
  "${CMAKE_CURRENT_LIST_DIR}/Scorer.pc" @ONLY
)
message(STATUS "Pkg-config generated")

# Make relative paths absolute (needed later on)
foreach (p LIB BIN INCLUDE CMAKE)
  set (var INSTALL_${p}_DIR)
  if (NOT IS_ABSOLUTE "${${var}}")
    set (FULLPATH_${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

#################################################################
#                          SUMMARY                              #
#################################################################

message(STATUS ""                                                                       )
message(STATUS "=================== Scorer configuration Summary =================="    )
message(STATUS "   Scorer version: ${SCORER_VERSION}"                                   )
message(STATUS ""                                                                       )
message(STATUS "   Build type : ${CMAKE_BUILD_TYPE}"                                    )
message(STATUS "   C++ :"                                                               )
message(STATUS "      C++ Compiler : ${CMAKE_CXX_COMPILER}"                             )
message(STATUS "      C++ flags    :"                                                   )
foreach(FLAG ${CMAKE_CXX_FLAGS_LIST})
  message(STATUS "                    * ${FLAG}"                                        )
endforeach(FLAG)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "      C++ Debug flags:"                                               )
  foreach(FLAG ${CMAKE_CXX_FLAGS_DEBUG})
    message(STATUS "                    * ${FLAG}"                                      )
  endforeach(FLAG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "      C++ Release flags  :"                                           )
  foreach(FLAG ${CMAKE_CXX_FLAGS_RELEASE})
    message(STATUS "                    * ${FLAG}"                                      )
  endforeach(FLAG)
endif()
message(STATUS "      Linker flags : "                                                  )
foreach(FLAG ${linked_libs})
  message(STATUS "                    * ${FLAG}"                                        )
endforeach(FLAG)
message(STATUS ""                                                                       )
message(STATUS "   OpenMP support : ${OMP}"                                             )
message(STATUS "   Cython support : ${PYWRAP}"                                          )
message(STATUS "   Documentation support : ${BUILD_DOCS}"                               )
message(STATUS ""                                                                       )

#################################################################
#                         MAIN RULES                            #
#################################################################

add_library(${scorerlib} SHARED ${SCORER_SRC} ${SCORER_HEADER})
set_target_properties(${scorerlib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${scorerlib}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
  $<INSTALL_INTERFACE:${INSTALL_INCLUDE_DIR}>)
target_link_libraries(${scorerlib} ${linked_libs})
add_dependencies(${scorerlib} make_scorer_obj)

set_target_properties(${scorerlib}
  PROPERTIES
  PUBLIC_HEADER "${SCORER_HEADER}"
)

install(TARGETS ${scorerlib} EXPORT ScorerTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
  COMPONENT dev
)

add_custom_target(example_test)
add_executable( example "${CMAKE_CURRENT_LIST_DIR}/example/example.cpp" )
add_dependencies(example_test example)
target_link_libraries(example ${linked_libs} ${scorerlib})

install(TARGETS example DESTINATION "${INSTALL_BIN_DIR}")

if (PYWRAP)
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/scorer/source")
endif ()

# This must be the latest subdirectory included!!
if (BUILD_DOCS)
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/docs/")
endif ()

#################################################################
#                          EXPORTS                              #
#################################################################

install(EXPORT ScorerTargets
  FILE ScorerTargets.cmake
  NAMESPACE Scorer::
  DESTINATION "${INSTALL_CMAKE_DIR}"
)

# Export the package for use from the build-tree (this registers the build-tree with a global CMake-registry)
export(PACKAGE Scorer)

# Create the ScorerConfig.cmake
# First of all we compute the relative path between the cmake config file and the include path
file(RELATIVE_PATH REL_INCLUDE_DIR "${FULLPATH_INSTALL_CMAKE_DIR}" "${FULLPATH_INSTALL_INCLUDE_DIR}")
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(ScorerConfig.cmake.in "${PROJECT_BINARY_DIR}/ScorerConfig.cmake" @ONLY)
set(CONF_INCLUDE_DIRS "\${Scorer_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(ScorerConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/ScorerConfig.cmake" @ONLY)

# Create the ScorerConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/ScorerConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/ScorerConfig.cmake"
  "${PROJECT_BINARY_DIR}/ScorerConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}"
)
