

set( lib finance )

add_library( 
  ${lib} SHARED
  Money.cpp
)
set_target_properties(
  ${lib} PROPERTIES
  SOVERSION 0
  VERSION ${CMAKE_PROJECT_VERSION}
)
target_include_directories( ${lib} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )
install( TARGETS ${lib} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   )



if ( GOOGLE_TEST )
  add_subdirectory( tests )
endif()