cmake_minimum_required(VERSION 3.10)
project(fire)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME fire)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG    "-g  -Wall -Wextra -Werror -pedantic")

add_subdirectory(src)

