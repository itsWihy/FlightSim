#include <ranges>

#include "../include/FlightSimulatorHopefully/rendering/Mesh.h"

#include "../include/FlightSimulatorHopefully/ThirdPartyLibsInitializer.h"
#include "../include/FlightSimulatorHopefully/YokeSystemInputs.h"
#include "../include/FlightSimulatorHopefully/chunk/ChunkManager.h"
#include "../include/FlightSimulatorHopefully/terrain/ChunkGenerator.h"
#include "../include/FlightSimulatorHopefully/text/TextDisplay.h"

inline void resizingCallback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

const std::vector<Vertex> vertices{
    {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // bottom-left, red
    {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}}, // top-left, green
    {{1.0f, -1.0f, 0.0f}, {0.0f, 0.2f, 1.0f}}, // bottom-right, blue
    {{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}, // top-right, white
};

const std::vector<GLuint> indices{
    2, 0, 1,
    3, 2, 1
};


constexpr float width = 800;
constexpr float height = 800;

int main() {
    initializeGLFW();

    GLFWwindow *window = glfwCreateWindow(width, height, "Flight simuutor", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, resizingCallback);

    // glFrontFace(GL_CW);
    // glCullFace(GL_FRONT);
    // glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const Shader shaderProgram(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.frag");

    const Shader textShader(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/text.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/text.frag");


    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 90.0f, 0.1f, 100.0f);
    YokeSystem yokeInputs{};

    TextDisplay textDisplay(textShader);

    const Mesh chunkMesh {vertices, indices};

    ChunkManager chunkManager {chunkMesh};

    ChunkGenerator chunkGenerator {};

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    double fpsCount = 0;

    while (!glfwWindowShouldClose(window)) {
        const double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;

        nbFrames++;
        if ( delta >= 1.0 ){
            fpsCount = static_cast<double>(nbFrames) / delta;

            nbFrames = 0;
            lastTime = currentTime;
        }

        yokeInputs.refreshData();

        glClearColor(0.52f, 0.807f, 0.95f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.activateShaders();

        camera.inputs(window, yokeInputs);

        // chunkManager.renderNearChunks(shaderProgram, camera);
        chunkGenerator.drawChunk(shaderProgram, camera);

        std::string pos = std::format("Pos({}, {}, {})", camera.Position.x, camera.Position.y, camera.Position.z);
        std::string speed = std::format("Speed({})", camera.speed);
        std::string fps = std::format("Fps({})", fpsCount);
        std::string thrust2 = std::format("Thrust({})", yokeInputs.getDataNormalized(AxisTypes::WORKING_THRUST));

        textDisplay.renderText(speed, 25.0f, 25.0f, 0.5f, glm::vec3(1, 1, 1));
        textDisplay.renderText(pos , 25.0f, 125.0f, 0.5f,glm::vec3(0.2, 1, 0.2));
        textDisplay.renderText(thrust2 , 350.0f, 25.0f, 0.5f,glm::vec3(1, 1, 1));

        textDisplay.renderText(fps, 25.0f, 750.0f, 0.5f, glm::vec3(1, 1, 1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.deleteShaders();

    glfwTerminate();
    return 0;
}



//TODO:
// more sophisticated movement support
// infinite terrain! add some blocks here and there!
// add Pilot HUD like thing with current level and rotation and all!
// add special joystick support
// add shooting
// add targets
// add a counter
// ask someone who did yarpa b what the tasks are, and continue the proj!
