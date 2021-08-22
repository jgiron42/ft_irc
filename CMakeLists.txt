cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

file(GLOB SOURCES srcs/*.cpp)

add_executable(ft_irc ${SOURCES} includes/parse_struct.hpp)
