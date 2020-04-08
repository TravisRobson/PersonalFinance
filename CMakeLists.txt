

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
# Point toward CMake modules
###############################################################################
list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )


###############################################################################
# Google tests
###############################################################################
if ( GOOGLE_TEST )

  include( CTest )
  enable_testing()

  # place tests in the build tree
  set( GOOGLE_TEST_BINDIR ${CMAKE_BINARY_DIR}/bin/tests CACHE PATH "Installation directory for Google test executables" )
  message( STATUS "${GOOGLE_TEST_BINDIR}" )
  
  include( ExternalProject )
  set_directory_properties( PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/extern ) # Set default ExternalProject root directory
  ExternalProject_Add( googletest
    GIT_REPOSITORY     https://github.com/google/googletest.git
    GIT_TAG            release-1.10.0 # there seems to be an issue with master
    # Disable install step
    INSTALL_COMMAND    ""
    TIMEOUT            10
    # force separate output paths for debug and release buils to allow easy
    # identification of correct lib in subsequest TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS         -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                       -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
                       -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
                       -Dgtest_force_shared_crt=ON
    # Wrap download, configure, and build steps in a script to log output
    LOG_DOWNLOAD       ON
    LOG_CONFIGURE      ON
    LOG_BUILD          ON
  )
  ExternalProject_Get_Property( googletest source_dir )
  include_directories( ${source_dir}/googletest/include )

  add_subdirectory( tests )

endif()


###############################################################################
# Qt 5
###############################################################################
# Turn on automatic invocation of the MOC, UIC & RCC
# cmake_policy( SET CMP0071 NEW )
# set( CMAKE_AUTOMOC ON )
# set( CMAKE_AUTOUIC ON )
# set( CMAKE_AUTORCC ON )
# # set( CMAKE_INCLUDE_CURRENT_DIR ON )
# find_package( Qt5 COMPONENTS REQUIRED  Widgets Core Gui )
# 
# qt5_wrap_ui( ui_wrap mainwindow.ui ) # wrap the ui file to a C++ header
# qt5_wrap_cpp( moc_sources mainwindow.h )
# 
# add_executable( gui mainwindow.cpp main.cpp mainwindow.h ${ui_wrap} ${moc_sources} )
# target_include_directories( gui PRIVATE ${CMAKE_BINARY_DIR} )
# target_link_libraries( gui 
#  PUBLIC
#  Qt5::Core
#  Qt5::Gui
#  Qt5::Widgets
# )



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
  src/Date.cpp
  src/Loan.cpp
  src/Money.cpp
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
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS ON
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

if ( COMPILER_WARNINGS )

  target_compile_options( 
    finance PRIVATE 
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>                          # GCC compiler options
    $<$<CXX_COMPILER_ID:AppleClang>:-Weverything -Wno-c++98-compat>  # Clang compiler options
  ) # \todo turn on C++98-compat later

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




