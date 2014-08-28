project(cucs_demo)
cmake_minimum_required(VERSION 2.8)

# Supported build types:
#  Debug
#  Release
#  RelWithDebInfo
#
# to set build type: -DCMAKE_BUILD_TYPE=...

find_package(PkgConfig)

set(PROJECT_SOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src")

pkg_check_modules(CUCS REQUIRED cucs)
link_directories(${CUCS_LIBRARY_DIRS})

find_package(Boost COMPONENTS regex)
if (Boost_FOUND)
    set(INCLUDEDIRS ${INCLUDEDIRS} ${Boost_INCLUDE_DIRS})
    set(PROJECTLIBS ${PROJECTLIBS} ${Boost_LIBRARIES} )
endif()

set(INCLUDEDIRS ${INCLUDEDIRS} ${CUCS_INCLUDE_DIRS})
set(PROJECTLIBS ${PROJECTLIBS} ${CUCS_LIBRARIES})

#Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${INCLUDEDIRS})

##Project sources
file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCES_PATH}/*)
set(SRC_LIST ${SRC_LIST} )

#Library
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${PROJECTLIBS})

