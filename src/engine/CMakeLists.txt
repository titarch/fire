set(engine_src_files
        Program.hh
        Program.cc
        BufHandler.hh
        BufHandler.cc
        WinHandler.hh
        WinHandler.cc)
add_library(engine ${engine_src_files})
#target_link_libraries(engine PUBLIC)