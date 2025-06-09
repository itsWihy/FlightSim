#ifndef SHADERCLASS_H
#define SHADERCLASS_H
#include <iostream>
#include <string>
#include <glad/glad.h>

class Shader {
    void checkCompileErrors(const GLuint shader, const std::string &type) {
        GLint success;
        GLchar infoLog[1024];

        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (success) return;

            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                    << infoLog << "\n -- ------------------------------------------ -- " << std::endl;

            return;
        }

        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (success) return;

        glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                << infoLog << "\n -- ------------------------------------------ -- " << std::endl;
    }

public:
    GLuint ID{};

    Shader(const char *vertexFile, const char *fragmentFile);

    void activateShaders() const;

    void deleteShaders() const;
};

std::string getFileContents(const char *filename);

#endif //SHADERCLASS_H
