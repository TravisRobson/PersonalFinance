

cmake_minimum_required( VERSION 3.8.0 FATAL_ERROR )
project( finance VERSION 0.1.0 LANGUAGES CXX )


set( CMAKE_CXX_STANDARD 11 )


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
set( INSTALL_CMAKE_DIR   lib/cmake/finance CACHE PATH "Installation directory for CMake files"  )

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

set_target_properties(
  finance PROPERTIES
  SOVERSION     ${FINANCE_MAJOR_VERSION}
  VERSION       ${FINANCE_VERSION}
  #PUBLIC_HEADER "Money.hpp;Loan.hpp"
)

target_include_directories(
  finance 
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# target_link_libraries( # currently none are linked
#   finance
#   PUBLIC
#
#   PRIVATE
#
# )

if ( COMPILER_WARNINGS )

  target_compile_options( 
    finance PRIVATE 
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>        # GCC compiler options
    $<$<CXX_COMPILER_ID:AppleClang>:-Weverything>  # Clang compiler options
  )

endif()


###############################################################################
# External installation instruction
###############################################################################
include( GNUInstallDirs ) # use GNU's standard installation directories
install(
  TARGETS finance
  EXPORT finance-targets
  RUNTIME       DESTINATION ${INSTALL_BIN_DIR} 
  LIBRARY       DESTINATION ${INSTALL_LIB_DIR} 
  ARCHIVE       DESTINATION ${INSTALL_LIB_DIR}
  PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}/personalFinance
)

set_target_properties( finance PROPERTIES EXPORT_NAME PersonalFinance )

install( DIRECTORY include/ DESTINATION ${INSTALL_INCLUDE_DIR} ) # \todo or should I use: ${CMAKE_INSTALL_INCLUDEDIR}

install( # export targets to a script
  EXPORT finance-targets 
  FILE
    PersonalFinanceTargets.cmake
  NAMESPACE
    PersonalFinance::
  DESTINATION
    ${INSTALL_CMAKE_DIR} # \todo or should this be: ${CMAKE_INSTALL_LIBDIR}/cmake/personalFinance
)


include( CMakePackageConfigHelpers ) # create a PersonalFinanceConfigVersion.cmake
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/PersonaFinanceConfigVersion.cmake
  VERSION ${FINANCE_VERSION}
  COMPATIBILITY AnyNewerVersion 
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/PersonalFinanceConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CMAKE_DIR} # \todo or should this be: ${CMAKE_INSTALL_LIBDIR}/cmake/personalFinance
)

install( FILES #install the config and configversion find modules
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfigversion.cmake
  DESTINATION ${INSTALL_CMAKE_DIR} # \todo or should this be: ${CMAKE_INSTALL_LIBDIR}/cmake/personalFinance
)


# export from the build tree
export(
  EXPORT
  finance-targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/PersonalFinanceConfig.cmake
  NAMESPACE PersonalFinance::
)

export( PACKAGE PersonaFinance ) # register package in user's package registry


# # export the targets of build tree
# export( 
#   TARGETS finance
#   FILE "${PROJECT_BINARY_DIR}/FinanceTargets.cmake"
# )


# # export the package for use from the build tree
# # registers the build tree with a global CMake registry
# export( PACKAGE finance )


# # Create FinanceConfig.cmake and FinanceConfigVersion.cmake
# file(
#   RELATIVE_PATH REL_INCLUDE_DIR 
#   "${INSTALL_CMAKE_DIR}"
#   "${INSTALL_INCLUDE_DIR}"
# )


# # ... for the build tree
# set( CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" )
# configure_file(
#   FinanceConfig.cmake.in
#   "${PROJECT_BINARY_DIR}/FinanceConfig.cmake" @ONLY
# )


# # ... for the install tree
# set( CONF_INCLUDE_DIRS "\${FINANCE_CMAKE_DIR}/${REL_INCLUDE_DIR}" )
# configure_file(
#   FinanceConfig.cmake.in
#   "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/FinanceConfig.cmake" @ONLY
# )


# # ... for both
# configure_file(
#   FinanceConfigVersion.cmake.in
#   "${PROJECT_BINARY_DIR}/FinanceConfigVersion.cmake" @ONLY
# )


# #
# # Install the FinanceConfig.cmake and FinanceConfigVersion.cmake
# #
# install(
#   FILES
#   "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/FinanceConfig.cmake"
#   "${PROJECT_BINARY_DIR}/FinanceConfigVersion.cmake"
#   DESTINATION "${INSTALL_CMAKE_DIR}" 
#   COMPONENT dev
# )














