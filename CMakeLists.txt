cmake_minimum_required (VERSION 2.6)
project(optitrack-depack C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON) 
find_package(Boost REQUIRED)
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Boost_LIBRARY_PATH})
include_directories(${Boost_INCLUDE_DIRS})
if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0501)
endif(WIN32)

add_library(optitrack-depack SHARED depack.cc)
TARGET_LINK_LIBRARIES(optitrack-depack ${Boost_LIBRARIES})
