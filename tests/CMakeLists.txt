
include( CTest )
include( ExternalProject )

# Set default ExternalProject root directory
set_directory_properties( PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/extern )

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

# Specify include dir
ExternalProject_Get_Property( googletest source_dir )
include_directories( ${source_dir}/googletest/include )

set( Suffix ".a" )
set( Pthread "-pthread" )


#
# Money tests
#
add_executable( MoneyTests MoneyTests.cpp )
add_dependencies( MoneyTests googletest )
ExternalProject_Get_Property( googletest binary_dir )
add_test( MoneyTests MoneyTests )
target_link_libraries(
  MoneyTests
  debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${Suffix}
  debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${Suffix}
  optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
  optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
  ${Pthread}
  finance
)
install( TARGETS MoneyTests RUNTIME DESTINATION ${INSTALL_BIN_DIR}/tests )


add_executable( LoanTests LoanTests.cpp )
add_dependencies( LoanTests googletest )
ExternalProject_Get_Property( googletest binary_dir )
add_test( LoanTests LoanTests )
target_link_libraries(
  LoanTests
  debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${Suffix}
  debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${Suffix}
  optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
  optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
  ${Pthread}
  finance
)
install( TARGETS LoanTests RUNTIME DESTINATION ${INSTALL_BIN_DIR}/tests )
