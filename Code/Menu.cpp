#include "Menu.h"

bool Menu::selectButton(int newSelection) {
	if (buttons.size() == 0) { return false; }
	newSelection = newSelection % buttons.size();
	while (newSelection < 0) { newSelection += buttons.size(); }
	buttons[selectedButton]->deselect();
	if (buttons[newSelection]->select()) {
		selectedButton = newSelection;
		return true;
	}
	buttons[selectedButton]->select();
	return false;
}
void Menu::selectNext(int direction) {
	if (buttons.size() == 0 || selectedButton == -1) { return; }
	int currSelection = selectedButton + direction;
	while (!selectButton(currSelection)) {
		currSelection += direction;
	}
}

void Menu::createButton(std::string _text, Button::UseFunc useFunc, glm::vec2 offset, glm::vec2 scaling, float rotation, TextAlignH _hAlign, TextAlignV _vAlign) {
	std::unique_ptr<Button> b = std::make_unique<Button>(_text, useFunc, glm::vec3(scaling, 1.0f), glm::vec3(offset, 0.0f), rotation, _hAlign, _vAlign);
	if (buttons.size() == 0 || selectedButton == -1) { 
		selectedButton = buttons.size(); 
		b->select(); 
	}
	
	buttons.push_back(std::move(b));
}
