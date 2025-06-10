#include "../include/FlightSimulatorHopefully/Mesh.h"

#include "../include/FlightSimulatorHopefully/ThirdPartyLibsInitializer.h"
#include "../include/FlightSimulatorHopefully/chunk/Chunk.h"
#include "../include/FlightSimulatorHopefully/text/TextDisplay.h"

inline void resizingCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

const std::vector<Vertex> &vertices{
    {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}, // bottom-left, red
    {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}}, // top-left, green
    {{1.0f, -1.0f, 0.0f}, {0.0f, 0.2f, 1.0f}}, // bottom-right, blue
    {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}, // top-right, white
};

std::vector<GLuint> indices{
    2, 0, 1,
    3, 2, 1
};


const float width = 800;
const float height = 800;

int main() {
    initializeGLFW();

    GLFWwindow *window = glfwCreateWindow(width, height, "Flight simuutor", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, resizingCallback);

    Shader shaderProgram(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.frag");


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    Shader textShader(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/text.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/text.frag");

    TextDisplay textDisplay(textShader);

    std::vector<Mesh> cubes;

    //Idea: Chunk, composed of many cubes. Then, generate chunks around player. As he moves, generate more chunks.
    const Chunk chunk {{0,0,0}, vertices, indices};

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.52f, 0.807f, 0.95f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.activateShaders();

        camera.inputs(window);

        chunk.renderChunk(shaderProgram, camera);

        textDisplay.renderText("Position: " + std::to_string(camera.Position.z ), 175.0f, 25.0f, 0.5f, glm::vec3(1,1,1));
        textDisplay.renderText("Speed: " + std::to_string(camera.speed), 25.0f, 25.0f, 0.5f, glm::vec3(1, 1, 1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.deleteShaders();

    glfwTerminate();
    return 0;
}

//TODO:
// SHOW text on SCREEN! (fps, current speed, etc)
// inifnite grid!
// more sophisticated movement support
// infinite terrain! add some blocks here and there!
// add Pilot HUD like thing with current level and rotation and all!
// add special joystick support
// add shooting
// add targets
// add a counter
// ask someone who did yarpa b what the tasks are, and continue the proj!
