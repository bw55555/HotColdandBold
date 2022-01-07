#include "MainMenu.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void MainMenu::initialize() {
	createButton("Play", []() {GameWindow::Instance->loadScene(SceneName::Level1); }, glm::vec2(0.0f), glm::vec2(1.0f), 0, HTA::Center, VTA::Center);
	createButton("Settings", doNothingFunc, glm::vec2(0.0f, -60.0f), glm::vec2(1.0f) , 0, HTA::Center, VTA::Center);
	createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -120.0f), glm::vec2(1.0f), 0, HTA::Center, VTA::Center);
	//createButton("X", doNothingFunc, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
}

void MainMenu::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& b : buttons) {
		b->draw(GameWindow::Instance->textShader);
	}
}

void MainMenu::update() {
	GLFWwindow* w = GameWindow::Instance->window;
	if (KeyInput::isPressed("ENTER")) {
		buttons[selectedButton]->use();
	}
	if (KeyInput::isPressed("DOWN", 10)) {
		std::cout << "D";
		selectNext();
	}
	if (KeyInput::isPressed("UP", 10)) {
		selectPrev();
	}
}
