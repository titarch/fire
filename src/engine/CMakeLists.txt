add_subdirectory(buffers)
add_subdirectory(textures)
add_subdirectory(models)
add_subdirectory(particles)

set(engine_src_files
        Event.hh
        Event.cc
        WinRender.hh
        WinRender.cc
        shaders.hh
        Program.hh
        Program.cc
        program.hh)
add_library(engine ${engine_src_files})
target_link_libraries(engine PRIVATE models textures buffers particles)
