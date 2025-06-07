//
// Created by Wihy on 6/7/25.
//

#include "../../include/FlightSimulatorHopefully/rendering/RenderingUtilities.h"

#include <glad/glad.h>

void setFrameColour(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}
