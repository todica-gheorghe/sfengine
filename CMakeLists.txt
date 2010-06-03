cmake_minimum_required(VERSION 2.6)

project(sfengine)

file(
	GLOB_RECURSE
	srcBin
	src/main.cpp
)

FILE(
	GLOB_RECURSE
	srcLib
	src/*
	extlibs/lua/src/*
	extlibs/luabind/src/*
	extlibs/tinyxml/src/*
)

include_directories(include)
include_directories(extlibs/)
include_directories(extlibs/lua/src)
include_directories(extlibs/luabind)
include_directories(extlibs/tinyxml/include)

# INCLUDE BOOST
find_package(Boost 1.41.0)
include_directories(${BOOST_INCLUDEDIR})
link_directories(${BOOST_LIBRARYDIR})

# Find SFML
if (SFML_INCLUDEDIR)
	include_directories(${SFML_INCLUDEDIR})
else (SFML_INCLUDEDIR)
	message(FATAL_ERROR "You have to set up the SFML_INCLUDEDIR variable")
endif (SFML_INCLUDEDIR)
if (SFML_LIBRARYDIR)
	link_directories(${SFML_LIBRARYDIR})
else (SFML_LIBRARYDIR)
	message(FATAL_ERROR "You have to set up the SFML_LIBRARYDIR variable")
endif (SFML_LIBRARYDIR)


set(EXECUTABLE_OUTPUT_PATH bin/)
set(LIBRARY_OUTPUT_PATH lib/)

add_library(
	sfengine-s
	STATIC
	${srcLib}
)

target_link_libraries(
	sfengine-s
	sfml-graphics
	sfml-window
	sfml-system
)
