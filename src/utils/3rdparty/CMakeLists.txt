set(3rdparty_src_files
        OBJ_Loader.h)
add_library(3rdparty ${3rdparty_src_files})
set_target_properties(3rdparty PROPERTIES LINKER_LANGUAGE CXX)