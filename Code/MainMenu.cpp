#include "MainMenu.h"
#include "GameWindow.h"

void MainMenu::initialize() {

	//in full...
	createButton("Play", []() {GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("HOT, COLD, & BOLD", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	
	//you can omit the last 4 parameters...
	createButton("Practice", doNothingFunc, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	createButton("Settings", doNothingFunc, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
	createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -300.0f), glm::vec2(2.0f));
	//createButton("X", doNothingFunc, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
}

/*
void MainMenu::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& b : buttons) {
		b->draw(GameWindow::textShader);
	}
}
*/

void MainMenu::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->quit();
	}
	Menu::update();
}

void DifficultyMenu::initialize() {
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	//in full...
	createButton("Easy", []() {GameWindow::Instance->startGame(Difficulty::Easy, GameMode::All); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);

	//you can omit the last 4 parameters...
	createButton("Normal", []() {GameWindow::Instance->startGame(Difficulty::Normal, GameMode::All); }, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	createButton("Hard", []() {GameWindow::Instance->startGame(Difficulty::Hard, GameMode::All); }, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
	//createButton("X", doNothingFunc, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
}

/*
void DifficultyMenu::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& b : buttons) {
		b->draw(GameWindow::textShader);
	}
}
*/

void DifficultyMenu::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->loadScene(SceneName::MainMenu);
	}
	Menu::update();
}
