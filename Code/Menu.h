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
	void createButton(std::string _text, Button::UseFunc useFunc, glm::vec2 offset, glm::vec2 scaling = glm::vec2(1.0f), float rotation = 0.0f, TextAlignH _hAlign = HTA::Center, TextAlignV _vAlign = VTA::Center);
	
	virtual void initialize() = 0;
	virtual void render();
	virtual void update();
	virtual ~Menu() {};
};