add_subdirectory(utils)
add_subdirectory(engine)

add_executable(${EXECUTABLE_NAME} main.cc utils/colors.hh)
set(EXECUTABLE_OUTPUT_PATH ..)

target_link_libraries(${EXECUTABLE_NAME} engine)
target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL glfw GLEW::GLEW)
