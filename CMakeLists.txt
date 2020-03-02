

cmake_minimum_required( VERSION 3.8.0 FATAL_ERROR )
project( finance VERSION 0.1.0 LANGUAGES CXX )


###############################################################################
# Versioning
###############################################################################
set( FINANCE_MAJOR_VERSION 0 )
set( FINANCE_MINOR_VERSION 1 )
set( FINANCE_PATCH_VERSION 0 )
set( 
  FINANCE_VERSION
  ${FINANCE_MAJOR_VERSION}.${FINANCE_MINOR_VERSION}.${FINANCE_PATCH_VERSION}
)


###############################################################################
# Handle runtime pathing (RPATH)
###############################################################################
set( CMAKE_SKIP_BUILD_RPATH            FALSE )
set( CMAKE_BUILD_WITH_INSTALL_RPATH    FALSE )
set( CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE  )
set( CMAKE_INSTALL_RPATH               "${CMAKE_INSTALL_PREFIX}/lib" )


###############################################################################
# Set installation directories
###############################################################################
set( INSTALL_LIB_DIR     lib               CACHE PATH "Installation directory for libraries"    )
set( INSTALL_BIN_DIR     bin               CACHE PATH "Installation directory for binaries"     )
set( INSTALL_INCLUDE_DIR include           CACHE PATH "Installation directory for header files" )
set( INSTALL_CMAKE_DIR   lib/CMake/finance CACHE PATH "Installation directory for CMake files"  )

# Make relative paths absolute
foreach( path LIB BIN INCLUDE CMAKE )

  set( var INSTALL_${path}_DIR )
  if ( NOT IS_ABSOLUTE "${${var}}" )
    set( ${var} "${CMAKE_INSTALL_PREFIX}/${${var}}" )
  endif() 

endforeach()


###############################################################################
# Google tests
###############################################################################
if ( GOOGLE_TEST )

  enable_testing()
  add_subdirectory( tests )

endif()


###############################################################################
# Doxygen
###############################################################################
if ( GENERATE_DOXYGEN )
 # \todo fill this out
endif()


###############################################################################
# Finance library
###############################################################################
add_library(
  finance SHARED
  src/Money.cpp
  src/Loan.cpp
)

target_include_directories(
  finance 
  PUBLIC # the public header needs to be in a different location depending on whether we are building or installing
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(
  finance PROPERTIES
  SOVERSION     ${FINANCE_MAJOR_VERSION}
  VERSION       ${FINANCE_VERSION}
  POSITION_INDEPENDENT_CODE ON
)

# target_link_libraries( # currently none are linked
#   finance
#   PUBLIC
#
#   PRIVATE
#
# )

target_compile_features( finance PUBLIC cxx_std_11 ) 
if ( COMPILER_WARNINGS )

  target_compile_options( 
    finance PRIVATE 
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>        # GCC compiler options
    $<$<CXX_COMPILER_ID:AppleClang>:-Weverything>  # Clang compiler options
  )

endif()

configure_file( 
  "${PROJECT_SOURCE_DIR}/src/config.hpp.in"
  "${PROJECT_BINARY_DIR}/include/personalFinance/config.hpp"
  @ONLY 
)

message(STATUS ${CMAKE_INSTALL_INCLUDEDIR}/personalFinance )
install( 
  FILES "${PROJECT_BINARY_DIR}/include/personalFinance/config.hpp" 
  DESTINATION ${INSTALL_INCLUDE_DIR}/personalFinance
)


###############################################################################
# External installation instruction
###############################################################################
include( GNUInstallDirs ) # use GNU's standard installation directories
install(
  TARGETS finance
  EXPORT finance-targets
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}  
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties( finance PROPERTIES EXPORT_NAME PersonalFinance )

install( DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

install( # export targets to a script
  EXPORT finance-targets 
  FILE
    PersonalFinanceTargets.cmake
  NAMESPACE
    PersonalFinance::
  DESTINATION
    ${INSTALL_CMAKE_DIR} 
)


include( CMakePackageConfigHelpers ) # create a ConfigVersion.cmake
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfigVersion.cmake
  VERSION ${FINANCE_VERSION}
  COMPATIBILITY AnyNewerVersion 
)

configure_package_config_file( # create a Config.cmake file
  ${CMAKE_CURRENT_LIST_DIR}/cmake/PersonalFinanceConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CMAKE_DIR} 
)

install( FILES # install the config and configversion find modules
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfigVersion.cmake
  DESTINATION ${INSTALL_CMAKE_DIR} 
)


# export from the build tree
export(
  EXPORT
  finance-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfig.cmake
  NAMESPACE PersonalFinance::
)

export( PACKAGE PersonaFinance ) # register package in user's package registry




