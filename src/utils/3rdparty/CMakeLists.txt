set(3rdparty_src_files
        stb_image.h
        tiny_obj_loader.h)
add_library(3rdparty ${3rdparty_src_files})
set_target_properties(3rdparty PROPERTIES LINKER_LANGUAGE CXX)