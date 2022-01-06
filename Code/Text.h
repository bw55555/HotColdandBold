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

class Text : public Sprite {
public:
    static unsigned int textVAO;
	static int initializeFT();
    std::string text;
    glm::vec3 color;
	Text(std::string _text, glm::vec3 _color, glm::vec3 scaling = glm::vec3(1000.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f);
	void draw(Shader* s);
};