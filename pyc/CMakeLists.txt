# If the pyx file is a C++ file, we should specify that here.

set_source_files_properties(
  ${CYTHON_CMAKE_EXAMPLE_SOURCE_DIR}/Pyscorer.pyx
  PROPERTIES CYTHON_IS_CXX TRUE )

# Multi-file cython modules do not appear to be working at the moment.
cython_add_module( Pyscorer Pyscorer.pyx ${HPP_DIR}/scorer.h )
configure_file( ${CMAKE_BINARY_DIR}/pyc/Pyscorer.so ${CMAKE_SOURCE_DIR}/pyc/Pyscorer.so COPYONLY )
