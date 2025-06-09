#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../include/FlightSimulatorHopefully/ThirdPartyLibsInitializer.h"
#include "../include/FlightSimulatorHopefully/Callbacks.h"
#include "../include/FlightSimulatorHopefully/rendering/EBO.h"
#include "../include/FlightSimulatorHopefully/rendering/Shader.h"
#include "../include/FlightSimulatorHopefully/rendering/VAO.h"
#include "../include/FlightSimulatorHopefully/rendering/VBO.h"


const GLfloat vertices[] = {
    //               COORDINATES                  /     COLORS           //
    -0.5, -0.5, 0.0f,             1.0f, 0.0f, 0.0f,
    -0.5f, 0.5, 0.0f,             0.0f, 1.0f, 0.0f,
    0.5f, -0.5, 0.0f,             0.0f, 0.0f, 1.0f,
    0.5f, 0.5, 0.0f,              1.0f, 1.0f, 1.0f,
};

// Indices for vertices order
const GLuint indices[] = {
    0, 1, 2,
    3, 2, 1
};

int main() {
    initializeGLFW();

    GLFWwindow *window = glfwCreateWindow(800, 600, "Flight simuutor", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, resizingCallback);

    const Shader shaderProgram(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.frag");

    VAO VAO{};
    VAO.bind();

    VBO VBO(vertices, sizeof(vertices));
    EBO EBO(indices, sizeof(indices));

    VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *) nullptr);
    VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *) (3 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.activateShaders();
        glUniform1f(uniID, 0.75);
        VAO.bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAO.deleteVAO();
    VBO.deleteVBO();
    EBO.deleteEBO();

    shaderProgram.deleteShaders();

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
