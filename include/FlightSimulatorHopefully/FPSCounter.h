//
// Created by Wihy on 6/24/25.
//

#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H
#include <GLFW/glfw3.h>

class FPSCounter {
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    double fpsCount = 0;

public:
    void refreshFPSCounter() {
        const double currentTime = glfwGetTime();
        const double delta = currentTime - lastTime;

        nbFrames++;
        if ( delta >= 1.0 ){
            fpsCount = static_cast<double>(nbFrames) / delta;

            nbFrames = 0;
            lastTime = currentTime;
        }
    }

    double getFPS() const {
        return fpsCount;
    }
};

#endif //FPSCOUNTER_H
