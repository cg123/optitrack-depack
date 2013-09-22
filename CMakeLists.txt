cmake_minimum_required (VERSION 2.6)
project(optitrack-depack C CXX)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0501)
endif(WIN32)

add_library(optitrack-depack SHARED depack.cc client.cc)
target_link_libraries(optitrack-depack ${Boost_LIBRARIES})
