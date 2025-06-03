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

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    GLFWwindow *window = glfwCreateWindow(800, 600, "e", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwSwapInterval(1);
    glViewport(0, 0, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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
