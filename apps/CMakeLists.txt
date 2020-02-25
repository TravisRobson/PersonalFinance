

add_executable( main main.cpp )


target_link_libraries( main finance )


#target_include_directories( main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

install( 
  TARGETS main 
  # IMPORTANT: Add the bar executable to the "export-set"
  EXPORT FinanceTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
)