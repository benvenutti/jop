# ---------------------------------------------------------------------------------------
# in-tree build guard

if( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "Prevented in-tree build. Please create a build"
        " directory outside of the source code and call cmake from there" )
endif()

# ---------------------------------------------------------------------------------------
# project

cmake_minimum_required( VERSION 3.12 FATAL_ERROR )
project( jvp VERSION 0.0.1 LANGUAGES CXX )

# ---------------------------------------------------------------------------------------
# dependencies

set( Boost_USE_STATIC_LIBS ON )
find_package( Boost 1.54 COMPONENTS filesystem system iostreams REQUIRED )

# ---------------------------------------------------------------------------------------
# cmake modules

include( cmake/StandardProjectSettings.cmake )
include( cmake/CompilerWarnings.cmake )

# ---------------------------------------------------------------------------------------
# project configuration

add_library( project_options INTERFACE )
target_compile_features( project_options INTERFACE cxx_std_17 )

add_library( project_warnings INTERFACE )
set_project_warnings( project_warnings )

# ---------------------------------------------------------------------------------------
# project options

option( ENABLE_TESTING "Enable Test Builds" ON )

if( ENABLE_TESTING )
    enable_testing()
    message( STATUS "Building Tests: nothing to build at the moment..." )
endif()

# ---------------------------------------------------------------------------------------
# directories

add_subdirectory( src )
