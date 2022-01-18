#include "GameOver.h"
#include "GameWindow.h"

void GameOver::initialize() {

	createButton("Continue", []() {GameWindow::Instance->loadScene(SceneName::Level1); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("GAME OVER", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	makeText("You have become one with the cold...", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 800.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	makeSprite(Sprite::backgroundTextures[1], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -300.0f), glm::vec2(2.0f));
}

void GameOver::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->quit();
	}
	Menu::update();
}