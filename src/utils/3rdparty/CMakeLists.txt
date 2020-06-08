set(3rdparty_src_files
        tiny_obj_loader.h)
add_library(3rdparty ${3rdparty_src_files})
set_target_properties(3rdparty PROPERTIES LINKER_LANGUAGE CXX)