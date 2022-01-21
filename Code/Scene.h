#pragma once
#include <vector>
#include "Text.h"

enum class SceneName { MainMenu, DifficultyMenu, SettingsMenu, Level1, Level2, Level3, Credits };

class Scene {
public:
	typedef TextAlignH HTA;
	typedef TextAlignV VTA;
	virtual void initialize() {};
	virtual void render() = 0;
	virtual void update() = 0;
	virtual ~Scene() {};

	std::vector<std::shared_ptr<Text>> texts;
	std::shared_ptr<Text> makeText(std::string _text, glm::vec3 _color, glm::vec2 offset = glm::vec2(0.0f), glm::vec2 scaling = glm::vec2(1.0f), float rotation = 0.0f, TextAlignH _hAlign = HTA::Center, TextAlignV _vAlign = VTA::Center);
	std::shared_ptr<Text> makeText(std::string _text, glm::vec4 _color, glm::vec2 offset = glm::vec2(0.0f), glm::vec2 scaling = glm::vec2(1.0f), float rotation = 0.0f, TextAlignH _hAlign = HTA::Center, TextAlignV _vAlign = VTA::Center);
	std::vector<std::shared_ptr<Sprite>> sprites;
	std::shared_ptr<Sprite> makeSprite(unsigned int textureID, glm::vec2 offset = glm::vec2(0.0f), glm::vec2 scaling = glm::vec2(100.0f), float rotation = 0.0f);
	std::shared_ptr<Sprite> makeRect(glm::vec4 color, glm::vec2 offset = glm::vec2(0.0f), glm::vec2 scaling = glm::vec2(100.0f), float rotation = 0.0f);
};