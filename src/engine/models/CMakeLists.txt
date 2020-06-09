set(models_src_files
        Material.hh
        Material.cc
        Mesh.hh
        Mesh.cc
        Shape.hh
        Shape.cc
        Scene.hh
        Scene.cc)
add_library(models ${models_src_files})