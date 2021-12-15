# Set minimum CMake version, this number may change depending on features used! (We should really change this to the absolute minimum to get this file to build)
cmake_minimum_required (VERSION 3.6)
project(swm_project DESCRIPTION "swm (swim) is a simple dynamic window manager.")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# We need the XCB version of Xinerama, set this to off as this feature isn't truly implemented
option(XINERAMA "Allow multimonitor support via the common x extension xinerama." OFF)

add_executable(swm src/main.cpp)

find_package(xcb REQUIRED)
find_package(toml11 REQUIRED)

# Link headers and source files.
file(GLOB_RECURSE source_list src/*.cpp)
target_sources(swm PRIVATE ${source_list})
target_include_directories(swm PUBLIC include)

# Link depends
target_link_libraries(swm PUBLIC ${XCB_LIBRARIES})
target_link_libraries(swm PUBLIC toml11::toml11)

# TODO: Link the XCB-Xinerama library to our project, but since we aren't using it I'm leaving it out for now. 
if (XINERAMA) 
    # define this so we can use ifdef for this feature.
    add_compile_definitions(XINERAMA)
endif()

# Set standard to C++20
set_target_properties(swm PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF)