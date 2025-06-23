//
// Created by Wihy on 6/24/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>

#include "Shader.h"

class Texture {
public:
    GLuint id;
    GLenum type;

    Texture(const char* filepath, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

    void textureUnit(const Shader& shader, const char* uniform, GLuint unit);
    void bind() const;
    void unbind() const;
    void deleteTexture() const;
};

#endif //TEXTURE_H
