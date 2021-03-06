#include "Menu.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

bool Menu::selectButton(int newSelection) {
	if (buttons.size() == 0) { return false; }
	newSelection = newSelection % static_cast<int>(buttons.size());
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

void Menu::render() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& s : sprites) {
		s->draw();
	}
	for (auto& t : texts) {
		t->draw();
	}
	for (auto& b : buttons) {
		b->draw();
	}
}
void Menu::update() {
	if (KeyInput::isPressed("Z", 1000000) || KeyInput::isPressed("ENTER", 1000000)) {
		if (selectedButton != -1) { buttons[selectedButton]->use(); }
		
	}
	if (KeyInput::isPressed("DOWN", 10, 5)) {
		selectNext();
	}
	if (KeyInput::isPressed("UP", 10, 5)) {
		selectPrev();
	}
}

void Menu::deactivateButton(int buttonPos) {
	buttonPos = buttonPos % static_cast<int>(buttons.size());
	while (buttonPos < 0) { buttonPos += buttons.size(); }
	if (buttonPos == selectedButton) {
		selectNext();
		if (selectedButton == buttonPos) {
			selectedButton = -1;
		}
	}
	buttons[buttonPos]->deactivate();
}