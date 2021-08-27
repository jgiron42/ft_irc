cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes srcs/commands)

file(GLOB SOURCES srcs/*.cpp includes/*.hpp)

add_executable(ft_irc ${SOURCES} srcs/numerics.cpp)
