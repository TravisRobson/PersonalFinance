

cmake_minimum_required( VERSION 3.8.0 FATAL_ERROR )
project( demo VERSION 0.1.0 LANGUAGES CXX )


find_package( PersonalFinance 0.1 REQUIRED )

add_executable( main main.cpp )

# add_executable( main main.cpp )


# target_link_libraries( main finance )


# #target_include_directories( main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

# install( 
#   TARGETS main 
#   # IMPORTANT: Add the bar executable to the "export-set"
#   EXPORT FinanceTargets
#   RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
# )

