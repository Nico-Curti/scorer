# If the pyx file is a C++ file, we should specify that here.

set_source_files_properties( "${CMAKE_CURRENT_SOURCE_DIR}/scorer.pyx" PROPERTIES CYTHON_IS_CXX TRUE )

# Include *.pxd directory

include_directories("${CMAKE_SOURCE_DIR}/scorer/lib")

# Multi-file cython modules do not appear to be working at the moment.
cython_add_module(pyscorer "${CMAKE_CURRENT_SOURCE_DIR}/scorer.pyx")
target_link_libraries(pyscorer ${linked_libs} ${scorerlib})
set_target_properties(pyscorer PROPERTIES OUTPUT_NAME "scorer")
add_dependencies(pyscorer make_scorer_obj make_scorer_cython)

# Installation of targets
install(TARGETS pyscorer                                 DESTINATION "${CMAKE_SOURCE_DIR}/scorer/lib")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pyscorer.cpp" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}" RENAME scorer.cpp)

# setup installation

configure_file(
  "${CMAKE_SOURCE_DIR}/setup.py.in"
  "${CMAKE_SOURCE_DIR}/setup_.py" @ONLY)
configure_file(
  "${CMAKE_SOURCE_DIR}/scorer/__version__.py.in"
  "${CMAKE_SOURCE_DIR}/scorer/__version__.py" @ONLY)
configure_file(
  "${CMAKE_SOURCE_DIR}/setup.cfg.in"
  "${CMAKE_SOURCE_DIR}/setup.cfg" @ONLY)

add_custom_target(setup_scorer ALL
  DEPENDS pyscorer
  COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/setup_.py" develop --user
  #COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/setup_.py" install --user
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  COMMENT "Setup Python installation..."
)
