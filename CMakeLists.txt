

cmake_minimum_required( VERSION 3.8.0 FATAL_ERROR )
project( finance VERSION 0.1.0 )


set( CMAKE_CXX_STANDARD 11 )


#
# Handle runtime pathing (RPATH)
#
set( CMAKE_SKIP_BUILD_RPATH            FALSE )
set( CMAKE_BUILD_WITH_INSTALL_RPATH    FALSE )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE  )
set( CMAKE_INSTALL_RPATH               "${CMAKE_INSTALL_PREFIX}/lib" )


#
# Google Tests
#
if ( GOOGLE_TEST )

endif()


#
# Doxygen
#
if ( GENERATE_DOXYGEN )

endif()


add_subdirectory( src  )
add_subdirectory( apps )

