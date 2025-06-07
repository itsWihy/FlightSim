//
// Created by Wihy on 6/7/25.
//

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

inline void resizingCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

#endif //CALLBACKS_H
