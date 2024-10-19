cmake_minimum_required(VERSION 3.20)

project(IRISE_CLIENT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(IRISE_Client 
    main.cpp
    Client.hpp
    Client.cpp
    ../Messages.hpp
    ../Messages.cpp
)