cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ft_irc
        client.cpp
        client.hpp
        Server.cpp
        Server.hpp
        channel.cpp
        channel.hpp
        main.cpp
        )
