cmake_minimum_required(VERSION 3.31)

project(FlightSimulatorHopefully)

find_package ( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 23)

set (GLFW_SOURCE_DIR "/usr/lib/")

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

set (OpenGL_GL_PREFERENCE GLVND)

include_directories(/usr/local/include)
link_directories(/usr/local/lib/glad)

add_executable(FlightSimulatorHopefully src/main.cpp
        include/FlightSimulatorHopefully/ThirdPartyLibsInitializer.h
        include/FlightSimulatorHopefully/Callbacks.h
        src/rendering/RenderingUtilities.cpp
        include/FlightSimulatorHopefully/rendering/RenderingUtilities.h
        src/TestTriangle.h)
target_link_libraries( FlightSimulatorHopefully ${OPENGL_LIBRARIES} glfw glad )

#
