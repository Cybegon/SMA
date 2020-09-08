cmake_minimum_required(VERSION 3.0.2)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

macro(sma_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

project(SMA C)

set(CMAKE_C_STANDARD 11)

include(GNUInstallDirs)
include(${CMAKE_SOURCE_DIR}/cmake/Config.cmake)

sma_set_option(SMA_STATIC TRUE  BOOL "compile a static library")
sma_set_option(SMA_SHARED TRUE  BOOL "compile a shared library")

file(GLOB_RECURSE SMA_HEADERS   "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SMA_SOURCE    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

set(${PROJECT_NAME}_FILES ${SMA_SOURCE} ${SMA_HEADERS})

if(${SMA_STATIC} AND ${SMA_SHARED})
    add_library(objlib OBJECT ${${PROJECT_NAME}_FILES})
    add_library(${PROJECT_NAME}-s   STATIC $<TARGET_OBJECTS:objlib>)
    add_library(${PROJECT_NAME}     SHARED $<TARGET_OBJECTS:objlib>)
elseif(${SMA_STATIC})
    add_library(${PROJECT_NAME}-s   STATIC ${${PROJECT_NAME}_FILES})
elseif(${SMA_SHARED})
    add_library(${PROJECT_NAME}     SHARED ${${PROJECT_NAME}_FILES})
endif()