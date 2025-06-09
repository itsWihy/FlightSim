#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float scale;

float scaleFunc(float num);

void main() {
    gl_Position = vec4(scaleFunc(aPos.x), scaleFunc(aPos.y), scaleFunc(aPos.z), 1.0);
    color = aColor;
}

float scaleFunc(float num) {
    return num + num * scale;
}