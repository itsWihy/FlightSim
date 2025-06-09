#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 cameraMatrix;
uniform mat4 modelMatrix;


void main() {
    gl_Position = cameraMatrix * modelMatrix * vec4(aPos, 1.0);
    color = aColor;
}