//
// Created by Wihy on 6/9/25.
//

#include "../../include/FlightSimulatorHopefully/rendering/Shader.h"

#include <fstream>
#include <ios>
#include <iostream>

std::string getFileContents(const char *filename) {
    std::ifstream in(filename, std::ios::binary | std::ios::ate);

    if (!in) {
        std::cout << "Something wrong with file " << filename << std::endl;
        throw errno;
    }

    std::string contents(in.tellg(), '\0');

    in.seekg(0, std::ios::beg);
    in.read(&contents[0], static_cast<std::streamsize>(contents.size()));

    return contents;
}

Shader::Shader(const char *vertexFile, const char *fragmentFile) {
    const std::string vertexCode = getFileContents(vertexFile);
    const std::string fragmentCode = getFileContents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::activateShaders() const {
    glUseProgram(ID);
}

void Shader::deleteShaders() const {
    glDeleteProgram(ID);
}


