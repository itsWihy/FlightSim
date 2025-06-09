//
// Created by Wihy on 6/3/25.
//

#ifndef GLFWINITIALIZER_H
#define GLFWINITIALIZER_H

#include <GLFW/glfw3.h>

inline void initializeGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

inline void initializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

#endif //GLFWINITIALIZER_H
