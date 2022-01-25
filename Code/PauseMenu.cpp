#include "PauseMenu.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void PauseMenu::initialize() {
	//note: the pause menu only affects the game area, centered at (-600, 0)!
	makeRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f), Pos(-600.0f, 0.0f), Scale(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight));
	//in full...
	makeText("Resume", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-610.0f, 0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Resume", []() {GameWindow::Instance->setPause(false); }, glm::vec2(-600.0f, 0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Restart", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-610.0f, -120.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Restart", []() {GameWindow::Instance->restart(); }, glm::vec2(-600.0f, -120.0f), glm::vec2(2.0f));
	makeText("Return to Main Menu", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-610.0f, -240.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Return to Main Menu", []() {GameWindow::Instance->setPause(false); GameWindow::Instance->loadScene(SceneName::MainMenu); }, glm::vec2(-600.0f, -240.0f), glm::vec2(2.0f));
	buttons[0]->setActiveColor(glm::vec4(1.0f));
	buttons[1]->setActiveColor(glm::vec4(1.0f));
	buttons[2]->setActiveColor(glm::vec4(1.0f));
	//createButton("X", doNothingFunc, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
}


void PauseMenu::update() {
	Menu::update();
}

void PauseMenu::render() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	for (auto& s : sprites) {
		s->draw();
	}
	for (auto& b : buttons) {
		b->draw();
	}
	for (auto& t : texts) {
		t->draw();
	}
}