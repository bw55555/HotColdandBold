#include "Scene.h"
#include "UIRect.h"

std::shared_ptr<Text> Scene::makeText(std::string _text, glm::vec3 _color, glm::vec2 offset, glm::vec2 scaling, float rotation, TextAlignH _hAlign, TextAlignV _vAlign) {
	std::shared_ptr<Text> t =  std::make_shared<Text>(_text, glm::vec4(_color, 1.0f), glm::vec3(scaling, 1.0f), glm::vec3(offset, 0.0f), rotation, _hAlign, _vAlign);
	texts.push_back(t);
	return t;
}

std::shared_ptr<Text> Scene::makeText(std::string _text, glm::vec4 _color, glm::vec2 offset, glm::vec2 scaling, float rotation, TextAlignH _hAlign, TextAlignV _vAlign) {
	std::shared_ptr<Text> t = std::make_shared<Text>(_text, _color, glm::vec3(scaling, 1.0f), glm::vec3(offset, 0.0f), rotation, _hAlign, _vAlign);
	texts.push_back(t);
	return t;
}

std::shared_ptr<Sprite> Scene::makeSprite(unsigned int textureID, glm::vec2 offset, glm::vec2 scaling, float rotation) {
	std::shared_ptr<Sprite> s = std::make_shared<Sprite>(textureID, glm::vec3(scaling, 1.0f), glm::vec3(offset, 0.0f), rotation);
	sprites.push_back(s);
	return s;
}

std::shared_ptr<Sprite> Scene::makeRect(glm::vec4 color, glm::vec2 offset, glm::vec2 scaling, float rotation) {
	std::shared_ptr<Sprite> s = std::make_shared<UIRect>(color, glm::vec3(scaling, 1.0f), glm::vec3(offset, 0.0f), rotation);
	sprites.push_back(s);
	return s;
}