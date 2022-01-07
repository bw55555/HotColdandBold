#pragma once

#include "Sprite.h"
#include <unordered_map>
#include <string>
struct Character {
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
    static std::unordered_map<char, Character> Characters;
};

enum class TextAlignH { Left, Center, Right };
enum class TextAlignV { Bottom, Center, Top };

class Text : public Sprite {
public:
    typedef TextAlignH HTA;
    typedef TextAlignV VTA;
    static unsigned int textVAO;
	static int initializeFT();
    HTA hAlign = HTA::Left;
    VTA vAlign = VTA::Bottom;
    std::string text;
    glm::vec3 color;
	Text(std::string _text, glm::vec3 _color, glm::vec3 scaling = glm::vec3(1.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f, TextAlignH _hAlign = HTA::Left, TextAlignV _vAlign = VTA::Bottom);
	void draw(Shader* s);
    void setAlignment(TextAlignV _vAlign) {
        return setPos(hAlign, _vAlign, glm::vec2(trans));
    }
    void setAlignment(TextAlignH _hAlign) {
        return setPos(_hAlign, vAlign, glm::vec2(trans));
    }
    void setAlignment(TextAlignH _hAlign, TextAlignV _vAlign) {
        return setPos(_hAlign, _vAlign, glm::vec2(trans));
    }
    void setPos(TextAlignH _hAlign, TextAlignV _vAlign, glm::vec2 pos);
    void setPos(glm::vec2 pos) {
        return setPos(hAlign, vAlign, pos);
    }
    virtual ~Text() {};
};