

add_executable( MoneyTests MoneyTests.cpp )
add_dependencies( MoneyTests googletest )
ExternalProject_Get_Property( googletest binary_dir )
add_test( MoneyTests MoneyTests )

set( Suffix ".a" )
set( Pthread "-pthread" )

# Specify test's link libraries
target_link_libraries(
  MoneyTests
  debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtestd${Suffix}
  debug ${binary_dir}/googletest/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_maind${Suffix}
  optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
  optimized ${binary_dir}/googletest/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${Suffix}
  ${Pthread}
  finance
)

install( TARGETS MoneyTests RUNTIME DESTINATION ${INSTALL_BIN_DIR} )
