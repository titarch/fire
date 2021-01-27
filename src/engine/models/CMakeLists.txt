set(models_src_files
        Material.cc Material.hh

        Mesh.cc Mesh.hh
        Shape.cc Shape.hh

        BaseScene.cc BaseScene.hh
        ClassicScene.cc ClassicScene.hh
        QuickScene.cc QuickScene.hh
        Terrain.cc Terrain.hh
        )
add_library(models ${models_src_files})