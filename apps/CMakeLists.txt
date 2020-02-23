

add_executable( main main.cpp )
target_link_libraries( main finance )
target_include_directories( main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
install( TARGETS main RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} )