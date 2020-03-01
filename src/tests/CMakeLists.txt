

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
