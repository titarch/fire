cmake_minimum_required(VERSION 3.10)
project(fire)

set(CMAKE_CXX_STANDARD 20)

set(EXECUTABLE_NAME fire)

set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG    "-g  -Wall -Wextra -Werror -pedantic -DDEBUG_OPENGL")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(src)

