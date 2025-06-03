#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void error_callback(const int error, const char *description) {
    std::cout << "ERROR! " << error << "DESCRIPTION: " << &description;
}

static void key_callback(GLFWwindow *window, const int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    GLFWwindow *window = glfwCreateWindow(640, 480, "e", nullptr, nullptr);
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {
        int width;
        int height;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//plan:
// get simple 1 block working
// get camera working
// get infinite grid working
// add acceleration and deceleration
// add rotating left and right
// add going up and down
// improve world, add mountains and stuff
// add targets
// add stick support
