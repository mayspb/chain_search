cmake_minimum_required(VERSION 2.8)

# CMP0015 - link_directories() treats paths relative to the source dir
cmake_policy(SET CMP0015 NEW)

project(Chain_search)

# Platform dependent (Linux) add C++14 support
if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

include_directories(.)

# Main entry point
file(GLOB FILES ./*.h | ./*.cc)

add_executable(${PROJECT_NAME} ${FILES})

# Postfix <PROJECT_NAME>[d]<.exe>
set_property(TARGET ${PROJECT_NAME} PROPERTY DEBUG_POSTFIX d)

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)