

#configure_file( config.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/config.hpp" @ONLY )


add_library( 
  finance SHARED
  Money.cpp
  Loan.cpp
  #config.hpp
)
set_target_properties(
  finance PROPERTIES
  SOVERSION 0
  VERSION ${CMAKE_PROJECT_VERSION}
  PUBLIC_HEADER "Money.hpp;" #${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
)
target_include_directories( finance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

target_compile_definitions( -Wall -Wextra )

install( 
  TARGETS finance 
  # add finance library to the "export set"
  EXPORT FinanceTargets 
  RUNTIME       DESTINATION ${INSTALL_BIN_DIR}             COMPONENT bin 
  LIBRARY       DESTINATION ${INSTALL_LIB_DIR}             COMPONENT shlib
  PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}/finance COMPONENT dev
)



if ( GOOGLE_TEST )
  add_subdirectory( tests )
endif()