#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../include/FlightSimulatorHopefully/ThirdPartyLibsInitializer.h"
#include "../include/FlightSimulatorHopefully/Callbacks.h"
#include "../include/FlightSimulatorHopefully/rendering/RenderingUtilities.h"

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        std::cout << "ayo chill" << std::endl;
}

int main() {
    initializeGLFW();

    GLFWwindow *window = glfwCreateWindow(800, 600, "Flight simuutor", NULL, NULL);
    glfwMakeContextCurrent(window);

    initializeGLAD();

    glfwSetFramebufferSizeCallback(window, resizingCallback);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //render here.
        setFrameColour(1,0,0,1);

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
