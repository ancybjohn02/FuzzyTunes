cmake_minimum_required(VERSION 3.10)
project(PLAYWISE)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
set(SOURCES ${SOURCES} main.cpp)  # Add this line

add_executable(PLAYWISE ${SOURCES})
