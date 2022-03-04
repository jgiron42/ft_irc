cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_COMPILER "clang++")

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -Wall -Werror -Wextra -Ofast")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -Wall -Werror -Wextra -Ofast")

include_directories(includes srcs/commands)

file(GLOB SOURCES srcs/*.cpp includes/*.hpp)

add_executable(ft_irc ${SOURCES})
