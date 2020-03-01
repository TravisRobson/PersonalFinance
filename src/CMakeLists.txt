

#configure_file( config.hpp.in "${CMAKE_CURRENT_BINARY_DIR}/config.hpp" @ONLY )


# add_library( 
#   finance SHARED
#   Money.cpp
#   Loan.cpp
#   #config.hpp
# )
# set_target_properties(
#   finance PROPERTIES
#   SOVERSION 0
#   VERSION ${CMAKE_PROJECT_VERSION}
#   PUBLIC_HEADER "Money.hpp" #;${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
# )
# target_include_directories( finance PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

# target_compile_options( 
#   finance PRIVATE 
#   $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>        # GCC compiler options
#   $<$<CXX_COMPILER_ID:AppleClang>:-Weverything>  # Clang compiler options
# )

# # Register library to exports (i.e. make finance a target that can be exported and installed)
# # \todo perhaps move to a PersonaFinanceTargets.cmake?
# include( GNUInstallDirs )
# install( 
#   TARGETS finance 
#   EXPORT Finance-targets
#   RUNTIME       DESTINATION ${INSTALL_BIN_DIR} 
#   LIBRARY       DESTINATION ${INSTALL_LIB_DIR} 
#   ARCHIVE       DESTINATION ${INSTALL_LIB_DIR}
#   PUBLIC_HEADER DESTINATION ${INSTALL_INCLUDE_DIR}/finance
# )





# if ( GOOGLE_TEST )
#   add_subdirectory( tests )
# endif()