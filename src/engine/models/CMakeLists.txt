set(models_src_files
        Material.cc Material.hh

        Mesh.cc Mesh.hh
        Shape.cc Shape.hh

        BaseScene.cc BaseScene.hh
        Scene.cc Scene.hh
        )
add_library(models ${models_src_files})