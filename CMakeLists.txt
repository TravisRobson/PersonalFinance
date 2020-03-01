

cmake_minimum_required( VERSION 3.8.0 FATAL_ERROR )
project( finance VERSION 0.1.0 LANGUAGES CXX )


set( CMAKE_CXX_STANDARD 11 )


set( FINANCE_MAJOR_VERSION 0 )
set( FINANCE_MINOR_VERSION 1 )
set( FINANCE_PATCH_VERSION 0 )
set( 
  FINANCE_VERSION
  ${FINANCE_MAJOR_VERSION}.${FINANCE_MINOR_VERSION}.${FINANCE_PATCH_VERSION}
)



#
# Handle runtime pathing (RPATH)
#
set( CMAKE_SKIP_BUILD_RPATH            FALSE )
set( CMAKE_BUILD_WITH_INSTALL_RPATH    FALSE )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE  )
set( CMAKE_INSTALL_RPATH               "${CMAKE_INSTALL_PREFIX}/lib" )


#
# Set installation directories
#
set( INSTALL_LIB_DIR     lib               CACHE PATH "Installation directory for libraries"    )
set( INSTALL_BIN_DIR     bin               CACHE PATH "Installation directory for binaries"     )
set( INSTALL_INCLUDE_DIR include           CACHE PATH "Installation directory for header files" )
set( INSTALL_CMAKE_DIR   lib/CMake/finance CACHE PATH "Installation directory for CMake files"  )

# 
# Make relative paths absolute
#
foreach( path LIB BIN INCLUDE CMAKE )

  set( var INSTALL_${path}_DIR )
  if ( NOT IS_ABSOLUTE "${${var}}" )
    set( ${var} "${CMAKE_INSTALL_PREFIX}/${${var}}" )
  endif() 

endforeach()


#
# Google Tests
#
if ( GOOGLE_TEST )

  include( CTest )
  include( ExternalProject )

  # Set default ExternalProject root directory
  set_directory_properties( PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/extern )

  ExternalProject_Add( googletest
    GIT_REPOSITORY     https://github.com/google/googletest.git
    GIT_TAG            release-1.10.0
    # Disable install step
    INSTALL_COMMAND    ""
    TIMEOUT            10
    # force separate output paths for debug and release buils to allow easy
    # identification of correct lib in subsequest TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS         -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                       -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
                       -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
                       -Dgtest_force_shared_crt=ON
                       #-DCMAKE_CXX_FLAGS=-Wc++11-extensions
    # Wrap download, configure, and build steps in a script to log output
    LOG_DOWNLOAD       ON
    LOG_CONFIGURE      ON
    LOG_BUILD          ON
  )

  # Specify include dir
  ExternalProject_Get_Property( googletest source_dir )
  include_directories( ${source_dir}/googletest/include )

  enable_testing()

endif()


#
# Doxygen
#
if ( GENERATE_DOXYGEN )

endif()

include_directories(
  "${PROJECT_SOURCE_DIR}" # to find src/money.h (or whatever I want to expose in the future)
  "${PROJECT_BINARY_DIR}" # to find src/config.h (if I want such a file)
)


add_subdirectory( src  )
add_subdirectory( apps )


# export the targets of build tree
export( 
  TARGETS finance
  FILE "${PROJECT_BINARY_DIR}/FinanceTargets.cmake"
)


# export the package for use from the build tree
# registers the build tree with a global CMake registry
export( PACKAGE finance )


# Create FinanceConfig.cmake and FinanceConfigVersion.cmake
file(
  RELATIVE_PATH REL_INCLUDE_DIR 
  "${INSTALL_CMAKE_DIR}"
  "${INSTALL_INCLUDE_DIR}"
)


# ... for the build tree
set( CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" )
configure_file(
  FinanceConfig.cmake.in
  "${PROJECT_BINARY_DIR}/FinanceConfig.cmake" @ONLY
)


# ... for the install tree
set( CONF_INCLUDE_DIRS "\${FINANCE_CMAKE_DIR}/${REL_INCLUDE_DIR}" )
configure_file(
  FinanceConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/FinanceConfig.cmake" @ONLY
)


# ... for both
configure_file(
  FinanceConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/FinanceConfigVersion.cmake" @ONLY
)


#
# Install the FinanceConfig.cmake and FinanceConfigVersion.cmake
#
install(
  FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/FinanceConfig.cmake"
  "${PROJECT_BINARY_DIR}/FinanceConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" 
  COMPONENT dev
)














