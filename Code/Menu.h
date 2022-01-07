#pragma once
#include "Sprite.h"
#include "Scene.h"
#include "Button.h"
class Menu: public Scene {
public:
	typedef Text::HTA HTA;
	typedef Text::VTA VTA;
	std::vector<std::unique_ptr<Button>> buttons;
	int selectedButton = -1;
	bool selectButton(int newSelection);
	void selectNext(int direction = 1);
	inline void selectPrev() { return selectNext(-1); };
	void createButton(std::string _text, Button::UseFunc useFunc, glm::vec3 scaling = glm::vec3(1.0f), glm::vec3 offset = glm::vec3(0.0f), float rotation = 0.0f, TextAlignH _hAlign = HTA::Left, TextAlignV _vAlign = VTA::Bottom);
	//annoying... void createButton(std::string _text, glm::vec3 scaling = glm::vec3(1.0f), glm::vec3 offset = glm::vec3(0.0f), TextAlignH _hAlign = HTA::Left, TextAlignV _vAlign = VTA::Bottom) { return createButton(_text, scaling, offset, 0.0f, _hAlign, _vAlign); }
	virtual void initialize() = 0;
	virtual void render() = 0;
	virtual void update() = 0;
	virtual ~Menu() {};
};