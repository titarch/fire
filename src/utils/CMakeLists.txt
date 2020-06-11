set(utils_src_files
        colors.hh
        stb_image.h)
add_library(utils ${utils_src_files})
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)