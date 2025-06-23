cmake_minimum_required(VERSION 3.31)

project(FlightSimulatorHopefully)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 23)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

set(OpenGL_GL_PREFERENCE GLVND)

link_directories(/usr/local/lib/glad)

add_executable(FlightSimulatorHopefully
        src/main.cpp
        src/rendering/Shader.cpp
        src/rendering/VBO.cpp
        src/rendering/VAO.cpp
        src/rendering/EBO.cpp
        src/rendering/Camera.cpp
        src/rendering/Texture.cpp
        include/FlightSimulatorHopefully/rendering/Mesh.h
        src/rendering/Mesh.cpp
        src/text/TextDisplay.cpp
        src/chunks/Chunk.cpp
        src/chunks/ChunkManager.cpp
        src/inputs/YokeSystemInputs.cpp
        include/libs/stb/stb.cpp
)

target_include_directories(FlightSimulatorHopefully PRIVATE /usr/local/include /usr/include/freetype2)
target_link_libraries(FlightSimulatorHopefully ${OPENGL_LIBRARIES} glfw glad freetype)


