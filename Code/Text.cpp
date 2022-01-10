#include "Text.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "GameWindow.h"
#include <Shader.h>

unsigned int Text::textVAO;
std::unordered_map<char, Character> Character::Characters;

Text::Text(std::string _text, glm::vec4 _color, glm::vec3 scaling, glm::vec3 offset, float rotation, TextAlignH _hAlign, TextAlignV _vAlign) : Sprite(0, scaling, offset, rotation) {
    text = _text;
    color = _color;
    setAlignment(_hAlign, _vAlign);
}


int Text::initializeFT() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "resources/fonts/arial.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return -1;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    //note: definitely try to only use 1 texture!
    for (unsigned char c = 32; c <= 122; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Character::Characters.insert(std::pair<char, Character>(c, character));
        
    }
    int texture_units;
    //glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texture_units);
    //std::cout << "\n" << texture_units;
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    /*
    float vertices[4][4] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
        { -0.5f, 0.5f, 0.0f, 0.0f },    
        { 0.5f, -0.5f, 1.0f, 1.0f },
        { 0.5f, 0.5f, 1.0f, 0.0f }
    };
    */
    float vertices[4][4] = {
        { 0.0f, 0.0f, 0.0f, 1.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f, 1.0f },
        { 1.0f, 1.0f, 1.0f, 0.0f }
    };
    unsigned int textVBO;
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    return 0;
}

void Text::draw() {
    return draw(UI::UIprojection);
}

void Text::draw(glm::mat4 customProjection) {
    Shader* s = GameWindow::textShader;
    s->use();
    s->setVec4("textColor", color);
    
    //glm::mat4 projection = glm::ortho(0.0f, GameWindow::screenSize.x, 0.0f, GameWindow::screenSize.y);
    //glm::mat4 projection = 
    s->setMat4("projection", customProjection);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    // iterate through all characters
    int x = trans.x;
    for (auto c = text.begin(); c != text.end(); c++)
    {
        Character ch = Character::Characters[*c];

        float xpos = x + ch.Bearing.x * scale.x;
        float ypos = trans.y - (ch.Size.y - ch.Bearing.y) * scale.y;

        float w = ch.Size.x * scale.x;
        float h = ch.Size.y * scale.y;

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(xpos, ypos, 0.0f));
        transform = glm::rotate(transform, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(w, h, 1.0f));
        
        s->setMat4("transform", transform);
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        //glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //do this to forget about EBO
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}



void Text::setPos(TextAlignH _hAlign, TextAlignV _vAlign, glm::vec2 pos) {
    float x = 0;
    for (auto c = text.begin(); c != text.end(); c++)
    {
        Character ch = Character::Characters[*c];
        x += (ch.Advance >> 6) * scale.x;
    }
    trans.x = pos.x + (static_cast<int>(hAlign) - static_cast<int>(_hAlign)) * x / 2;
    trans.y = pos.y + (static_cast<int>(vAlign) - static_cast<int>(_vAlign)) * scale.y / 2 * 35;
    hAlign = _hAlign;
    vAlign = _vAlign;
}