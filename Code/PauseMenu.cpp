#include "PauseMenu.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void PauseMenu::initialize() {
	//note: the pause menu only affects the game area, centered at (-600, 0)!
	makeRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f), Pos(-600.0f, 0.0f), Scale(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight));
	//in full...
	createButton("Resume", []() {GameWindow::Instance->setPause(false); }, glm::vec2(-600.0f, 0.0f), glm::vec2(1.0f), 0, HTA::Center, VTA::Center);
	//createButton("Restart", []() {GameWindow::Instance->setPause(false); GameWindow::restart(); }, glm::vec2(-600.0f, -120.0f));
	createButton("Return to Main Menu", []() {GameWindow::Instance->setPause(false); GameWindow::Instance->loadScene(SceneName::MainMenu); }, glm::vec2(-600.0f, -120.0f));
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