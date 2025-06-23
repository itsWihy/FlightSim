#include <ranges>

#include "../include/FlightSimulatorHopefully/rendering/Mesh.h"

#include "../include/FlightSimulatorHopefully/ThirdPartyLibsInitializer.h"
#include "../include/FlightSimulatorHopefully/YokeSystemInputs.h"
#include "../include/FlightSimulatorHopefully/rendering/Texture.h"
#include "../include/FlightSimulatorHopefully/terrain/ChunkManager.h"
#include "../include/FlightSimulatorHopefully/text/TextDisplay.h"
#include "../include/FlightSimulatorHopefully/FPSCounter.h"


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


constexpr float width = 800.0f;
constexpr float height = 800.0f;

int main() {
    initializeGLFW();

    GLFWwindow *window = glfwCreateWindow(width, height, "Flight simuutor", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    gladLoadGL();
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, resizingCallback);

    // glFrontFace(GL_CW);
    // glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const Shader shaderProgram(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/default.frag");

    const Shader textShader(
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/text.vert",
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/shaders/text.frag");


    TextDisplay textDisplay(textShader);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), 90.0f, 0.1f, 500.0f);
    YokeSystem yokeInputs{};

    Texture dirt{
        "/home/Wihy/Projects/CPP/FlightSimulatorHopefully/resources/textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE};
    dirt.textureUnit(shaderProgram, "tex0",0);

    ChunkManager chunkManager {};
    FPSCounter fpsCounter{};

    while (!glfwWindowShouldClose(window)) {
        fpsCounter.refreshFPSCounter();

        yokeInputs.refreshData();

        glClearColor(0.32f, 0.607f, 0.75f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.activateShaders();

        dirt.bind();

        camera.inputs(window, yokeInputs);

        chunkManager.renderNearChunks(shaderProgram, camera);

        std::string pos = std::format("Pos({}, {}, {})", camera.Position.x, camera.Position.y, camera.Position.z);
        std::string orientation = std::format("Orientation({}, {}, {})", camera.Orientation.x, camera.Orientation.y, camera.Orientation.z);

        std::string speed = std::format("Speed({})", camera.speed);
        std::string fps = std::format("Fps({})", fpsCounter.getFPS());
        std::string thrust = std::format("Thrust({})", yokeInputs.getDataNormalized(AxisTypes::WORKING_THRUST));

        textDisplay.renderText(pos , 25.0f, 125.0f, 0.5f,glm::vec3(0.2, 1, 0.2));
        textDisplay.renderText(orientation, 25.0f, 175.0f, 0.5f, glm::vec3(0.2, 1, 0.2));

        textDisplay.renderText(speed, 25.0f, 25.0f, 0.5f, glm::vec3(1, 1, 1));
        textDisplay.renderText(thrust , 350.0f, 25.0f, 0.5f,glm::vec3(1, 1, 1));

        textDisplay.renderText(fps, 25.0f, 750.0f, 0.5f, glm::vec3(1, 1, 1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    dirt.deleteTexture();
    shaderProgram.deleteShaders();

    glfwTerminate();
    return 0;
}


//TODO: Terrian
// textures support
// lod
// back-face culling
// occlusion culling
// legitamate face culling - you do be a bit goofing with that
// greedy meshing :skull:
// beautifuler generation. Mountains. BuildingS?


//TODO: Flight sim
// add Pilot HUD like thing with current level and rotation and all!
// add special joystick support
// add shooting
// add targets
// add a counter
// ask someone who did yarpa b what the tasks are, and continue the proj!

//TODO GAMIFICATION.
// DIFFICULTY: GOD TIER
// CRASH AND MINE!!!!