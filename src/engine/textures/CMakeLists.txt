set(textures_src_files
        Texture.cc
        Texture.hh
        Sprite.cc
        Sprite.hh
        CubeMap.cc
        CubeMap.hh
        TileMap.cc
        TileMap.hh
        HeightMap.cc
        HeightMap.hh)
add_library(textures ${textures_src_files})
