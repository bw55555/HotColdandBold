#include "KeyInput.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "GameWindow.h"

KeyInput::KeyInput(int _key, int _inputDelay) {
	key = _key;
	inputDelay = _inputDelay;
}

void KeyInput::track(std::string keyName, int key, int inputDelay) {
	keys.try_emplace(keyName, std::make_unique<KeyInput>(key, inputDelay));
}

void KeyInput::checkEvents() {
	currFrame += 1;
	for (auto& keypair : keys) {
		keypair.second->update();
	}
}

void KeyInput::update() {
	if (glfwGetKey(GameWindow::Instance->window, key) == GLFW_PRESS) {
		if (!currentlyPressed) {
			currentlyPressed = true;
			lastPress = currFrame;
		}
	}
	else {
		if (currentlyPressed) {
			currentlyPressed = false;
			lastRelease = currFrame;
		}
	}
}

bool KeyInput::isPressed(std::string keyName, int _inputDelay, int repeatDelay) {
	/*
	try {
		if (!keys.at(keyName)) { std::cout << "Error"; }
	}
	catch(...) {
		std::cout << "Trying to access an untracked key!";
		return false;
	}
	*/

	if (keys[keyName]->currentlyPressed) {
		int lp = keys[keyName]->lastPress;
		if (currFrame == lp) { return true; }
		
		if (currFrame - lp <= _inputDelay) {
			return false;
		}
		return (currFrame - lp) % repeatDelay == 0;
	}
	return false;
}

