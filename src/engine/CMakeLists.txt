add_subdirectory(buffers)

set(engine_src_files
        WinHandler.hh
        WinHandler.cc
        Program.hh
        Program.cc
        program.hh)
add_library(engine ${engine_src_files})
target_link_libraries(engine PRIVATE buffers)