#include "../../include/FlightSimulatorHopefully/rendering/Texture.h"
#include "../../include/libs/stb/stb_image.h"

Texture::Texture(const char *filepath, const GLenum textureType, const GLenum slot, const GLenum format, const GLenum pixelType) {
    type = textureType;

    int widthImg, heightImg, numColorChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(filepath, &widthImg, &heightImg, &numColorChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(type, id);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(type);

    stbi_image_free(bytes);

    glBindTexture(type, 0);
}

void Texture::textureUnit(const Shader &shader, const char *uniform, const GLuint unit) {
    const GLuint textureUnit = glGetUniformLocation(shader.ID, uniform);

    shader.activateShaders();

    glUniform1i(textureUnit, unit);
}

void Texture::bind() const {
    glBindTexture(type, id);
}

void Texture::unbind() const {
    glBindTexture(type, 0);
}

void Texture::deleteTexture() const {
    glDeleteTextures(1, &id);
}

