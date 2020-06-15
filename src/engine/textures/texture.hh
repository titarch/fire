#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <string>

class Texture
{
    public :
        Texture(std::string);
        ~Texture();
        // can add slot as param
        void bind();
        void unbind();
    private : 
        std::string file_path;
        int width;
        int height;
        unsigned char* local_buffer;
        int bytes_per_pixels;
        GLuint render_id;
};
