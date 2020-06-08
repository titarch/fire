add_subdirectory(buffers)
add_subdirectory(models)

set(engine_src_files
        WinRender.hh
        WinRender.cc
        shaders.hh
        Program.hh
        Program.cc
        program.hh)
add_library(engine ${engine_src_files})
target_link_libraries(engine PRIVATE models buffers)