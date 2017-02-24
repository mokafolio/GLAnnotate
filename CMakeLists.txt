cmake_minimum_required (VERSION 2.8.11)
project (GLAnnotate)
set(CMAKE_CXX_FLAGS "-std=c++11 -fno-exceptions -w")

option(BuildExamples "BuildExamples" OFF)
include_directories (${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include)
link_directories(/usr/local/lib)

set (GLANNOTATEINC 
GLAnnotate/GLAnnotate.hpp
)

foreach ( file ${GLANNOTATEINC} )
    get_filename_component( dir ${file} DIRECTORY )
    install( FILES ${file} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${dir} )
endforeach()

if(BuildExamples)
add_subdirectory (Examples)
endif()
