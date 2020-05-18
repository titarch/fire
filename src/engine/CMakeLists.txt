set(engine_src_files
        WinHandler.hh
        WinHandler.cc
        BufHandler.hh
        BufHandler.cc
        Program.hh
        Program.cc
        program.hh)
add_library(engine ${engine_src_files})
#target_link_libraries(engine PUBLIC)