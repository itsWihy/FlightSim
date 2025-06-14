//
// Created by Wihy on 6/14/25.
//

#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <glm/vec3.hpp>

class Aircraft {
public:
    constexpr double gravity = 9.81;
    constexpr double mass = 6800;

    glm::vec3 position {};
    glm::vec3 yawPitchRoll {};
};
//WIP
#endif //AIRCRAFT_H
