#include "GameOver.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void GameOver::initialize() {
	makeRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f), Pos(-600.0f, 0.0f), Scale(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight));
	createButton("Continue", []() {GameWindow::Instance->undeadify(); }, glm::vec2(-600.0f, 0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	
	
	makeText("GAME OVER", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-600.0f, 700.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	makeText("You have become one with the cold...", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-600.0f, 550.0f), glm::vec2(1.4f), 0, HTA::Center, VTA::Center);
	createButton("Restart Game", []() {GameWindow::Instance->restart(); }, glm::vec2(-600.0f, -100.0f), glm::vec2(2.0f));
	createButton("Main Menu", []() {GameWindow::Instance->mainMenu(); }, glm::vec2(-600.0f, -200.0f), glm::vec2(2.0f));
	makeRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f), Pos(-600.0f, 0.0f), Scale(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight));

	if (GameWindow::Instance->player->continues <= 0) { deactivateButton(0); }
}

void GameOver::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->quit();
	}
	Menu::update();
}

void GameOver::render() {

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
//[]() {GameWindow::Instance->loadScene(SceneName::MainMenu); }