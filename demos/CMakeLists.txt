

cmake_minimum_required( VERSION 3.8.0 FATAL_ERROR )
project( demo VERSION 0.1.0 LANGUAGES CXX )

find_package( PersonalFinance 0.1 REQUIRED )


###############################################################################
# Handle runtime pathing (RPATH)
###############################################################################
set( CMAKE_SKIP_BUILD_RPATH            FALSE )
set( CMAKE_BUILD_WITH_INSTALL_RPATH    FALSE )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE  )
set( CMAKE_INSTALL_RPATH               "${CMAKE_INSTALL_PREFIX}/lib" )


###############################################################################
# Create executable
###############################################################################
add_executable( main main.cpp )
target_link_libraries( main PersonalFinance::PersonalFinance )
target_compile_features( main PUBLIC cxx_std_11 ) 
install( TARGETS main DESTINATION ${CMAKE_INSTALL_BINDIR} )
set_target_properties(
  main PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS ON
)


