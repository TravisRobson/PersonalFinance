

###############################################################################
# \brief  Add a google test installed in build tree at GOOGLE_TEST_BINDIR
#
# Example call: add_google_test( ExTests ExTests.cpp lib1 lib2 lib3 )
#
# \precondition function assumes a singular *.cpp file for the test
#
# \author  Travis Robson
###############################################################################
function( add_google_test TESTNAME )

  if ( NOT DEFINED GOOGLE_TEST_BINDIR )
    string( ASCII 27 esc    )
    set( end "${esc}[m"     )
    set( red "${esc}[1;31m" )
    message( FATAL_ERROR "${red}Specify GOOGLE_TEST_BINDIR for \
      google test executable installation${end}" )
  else()
    message( STATUS "Google tests are installed in ${GOOGLE_TEST_BINDIR}" )
  endif()

  add_executable( ${TESTNAME} ${ARGV1} ) # extract first argument to get test source file
  set_target_properties(
    ${TESTNAME} PROPERTIES
    CXX_STANDARD 11 # \todo standard should be propagated from top level
    CXX_EXTENSIONS ON
    CXX_STANDARD_REQUIRED YES
    POSITION_INDEPENDENT_CODE ON
  )
  target_include_directories( ${TESTNAME} PRIVATE ${INSTALL_INCLUDE_DIR} ) # \todo have a test for INSTALL_INCLUDE_DIR
  add_dependencies( ${TESTNAME} googletest )
  ExternalProject_Get_Property( googletest binary_dir )
  add_test( NAME ${TESTNAME} COMMAND ${TESTNAME} )

  list( REMOVE_ITEM ARGN ${ARGV1} )      # the rest of the arguments are the libraries
  set( Suffix ".a" )
  target_link_libraries(
    ${TESTNAME}
    debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${Suffix}
    debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${Suffix}
    optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
    -pthread
    ${ARGN}
  )

  install( 
    TARGETS ${TESTNAME} 
    RUNTIME DESTINATION ${GOOGLE_TEST_BINDIR}
  )

endfunction()


