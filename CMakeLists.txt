cmake_minimum_required (VERSION 3.8)

# Scorer Version
set (SCORER_MAJOR    2)
set (SCORER_MINOR    0)
set (SCORER_REVISION 0)
set (SCORER_VERSION ${SCORER_MAJOR}.${SCORER_MINOR}.${SCORER_REVISION})

project (Scorer LANGUAGES CXX VERSION ${SCORER_VERSION} DESCRIPTION "Machine Learning Scorer")
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions (-DMAJOR=${SCORER_MAJOR} -DMINOR=${SCORER_MINOR} -DREVISION=${SCORER_REVISION})

#################################################################
#                         COMPILE OPTIONS                       #
#################################################################

option (OMP     "Enable OpenMP                support" ON  )

#################################################################
#                         SETTING VARIABLES                     #
#################################################################

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/" ${CMAKE_MODULE_PATH})

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
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if ( CMAKE_COMPILER_IS_GNUCXX )
  add_compile_options (-Wall -Wextra -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -Wno-narrowing -Wpedantic)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    string (REGEX REPLACE "-O[0123]" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )
    set (CMAKE_CXX_FLAGS_RELEASE "")
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
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
    string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG" )
  endif()
endif()

if (MSVC)
  set (CMAKE_CXX_FLAGS "/wd4013 /wd4018 /wd4028 /wd4047 /wd4068 /wd4090 /wd4101 /wd4113 /wd4133 /wd4190 /wd4244 /wd4267 /wd4305 /wd4477 /wd4996 /wd4819 /fp:fast ${CMAKE_CXX_FLAGS}")
  string (REGEX REPLACE "/O2" "/Ox" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  add_definitions (-D_CRT_RAND_S)
  add_definitions (-DNOMINMAX)
  add_definitions (-D_USE_MATH_DEFINES)
  add_definitions (-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
  set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG ("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE AND NOT MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")
endif ()

#################################################################
#                         PARSE OPTIONS                         #
#################################################################

if (OMP)
  find_package(OpenMP REQUIRED)
  if (OPENMP_FOUND)
    message(STATUS "OpenMP found")
    if (OpenMP_CXX_VERSION_MAJOR LESS 4)
      message(FATAL_ERROR " Your OpenMP is too old. Required OpenMP 4.0. Please upgrade.")
    endif()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    if (APPLE)
      list(APPEND linked_libs OpenMP::OpenMP_CXX)
    endif()
  endif()
else()
  message(STATUS "OpenMP disabled")
endif()

if (MSVC)
  add_definitions (-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
endif()


#################################################################
#                         SETTING DIRECTORIES                   #
#################################################################

set(INC_DIR  ${CMAKE_SOURCE_DIR}/include  CACHE PATH "Path where find header files"                     )
set(SRC_DIR  ${CMAKE_SOURCE_DIR}/src      CACHE PATH "Path where find cpp files"                        )
set(TST_DIR  ${CMAKE_SOURCE_DIR}/example  CACHE PATH "Path where find test files"                       )
set(PYC_DIR  ${CMAKE_SOURCE_DIR}/scorer   CACHE PATH "Path where find cython files"                     )  # cython directory
set(LIB_DIR  ${CMAKE_SOURCE_DIR}/lib      CACHE PATH "Path where lib will be installed"            FORCE)
set(OUT_DIR  ${CMAKE_SOURCE_DIR}/bin      CACHE PATH "Path where outputs will be installed"        FORCE)

set (scorerlib scorer)
file (GLOB SRC    "${SRC_DIR}/*.cpp")
file (GLOB HEADER "${INC_DIR}/*.h"  )
file (GLOB EXE    "${EXAMPLE}/*.cpp")

include_directories(${INC_DIR})
include_directories(${PYC_DIR})

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

include( UseCython )

#################################################################
#                          SUMMARY                              #
#################################################################

message(STATUS ""                                                                       )
message(STATUS "=================== Scorer configuration Summary =================="    )
message(STATUS "   Scorer version: ${SCORER_MAJOR}.${SCORER_MINOR}.${SCORER_REVISION}"  )
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
message(STATUS ""                                                                       )

#################################################################
#                         MAIN RULES                            #
#################################################################

add_library(${scorerlib} SHARED ${SRC} ${HEADER})
set_property(TARGET ${scorerlib} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${scorerlib} ${linked_libs})

add_subdirectory(${PYC_DIR}/source)

add_custom_target(example_test)
add_executable( example ${TST_DIR}/example.cpp )
add_dependencies(example_test example)
target_link_libraries(example ${linked_libs} ${scorerlib})

#################################################################
#                          INSTALLERS                           #
#################################################################

install(TARGETS ${scorerlib}        EXPORT ScorerTargets
                                    RUNTIME DESTINATION ${OUT_DIR}
                                    LIBRARY DESTINATION ${LIB_DIR}
                                    ARCHIVE DESTINATION ${LIB_DIR}
                                    PUBLIC_HEADER DESTINATION ${LIB_DIR}/include
                                    COMPONENT dev
                                    )

install(TARGETS example            DESTINATION ${OUT_DIR})
