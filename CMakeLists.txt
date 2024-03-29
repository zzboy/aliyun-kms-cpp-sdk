cmake_minimum_required(VERSION 3.1)

cmake_policy(SET CMP0048 NEW)

file(STRINGS "VERSION" version)

project(alibabacloud-sdk VERSION ${version})

message(STATUS "Project version: ${PROJECT_VERSION}")

set(TARGET_OUTPUT_NAME_PREFIX "alibabacloud-sdk-" CACHE STRING "The target's output name prefix")
option(BUILD_SHARED_LIBS  "Enable shared library" ON)
option(BUILD_UNIT_TESTS "Enable unit tests" OFF)
option(BUILD_FUNCTION_TESTS "Enable function test" OFF)

set(LIB_TYPE STATIC)
if(BUILD_SHARED_LIBS)
	set(LIB_TYPE SHARED)
	add_definitions(-DALIBABACLOUD_SHARED)
endif()

set_property(GLOBAL
	PROPERTY
	USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 11)

include(ExternalProject)
include(GNUInstallDirs)

add_subdirectory(3rdparty)
add_subdirectory(core)

add_subdirectory(kms)
