# If the pyx file is a C++ file, we should specify that here.

set(PYC_SRC_DIR    ${PYC_DIR}/source       CACHE PATH "Path where find pyx files" )
set(PYC_INC_DIR    ${PYC_DIR}/lib          CACHE PATH "Path where find pxd files" )

set_source_files_properties( ${PYC_SRC_DIR}/scorer.pyx PROPERTIES CYTHON_IS_CXX TRUE )

# Include *.pxd directory

include_directories(${PYC_INC_DIR})

# Multi-file cython modules do not appear to be working at the moment.
cython_add_module( pyscorer scorer.pyx ${SRC_DIR}/scorer.cpp ${INC_DIR}/scorer.h )
target_link_libraries(pyscorer ${linked_libs} ${scorerlib})
set_target_properties(pyscorer PROPERTIES OUTPUT_NAME "scorer")
add_dependencies(pyscorer make_scorer_obj make_scorer_cython)

# Installation of targets
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/pyscorer.cpp      DESTINATION ${PYC_SRC_DIR} RENAME scorer.cpp)
install(TARGETS pyscorer                                    DESTINATION ${PYC_INC_DIR})
