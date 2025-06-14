//
// Created by Wihy on 6/10/25.
//

#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <map>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <freetype2/freetype/freetype.h>
#include "../rendering/Shader.h"
#include "../rendering/VAO.h"


struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size; // Size of glyph
    glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
    FT_Pos Advance; // Offset to advance to next glyph
};


class TextDisplay {
public:
    const Shader& shader;

    VAO VAO1;
    VBO VBO1;

    std::map<char, Character> Characters;

    explicit TextDisplay(const Shader& shader);

    void renderText(const std::string &text, float x, float y, float scale, glm::vec3 color);
};


#endif //TEXTDISPLAY_H
