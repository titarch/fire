add_subdirectory(3rdparty)

set(utils_src_files
        colors.hh
        colors.cc
        transform.hh
        stb_image.h)
add_library(utils ${utils_src_files})
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(utils PRIVATE 3rdparty)
