#include "MainMenu.h"
#include "GameWindow.h"

void MainMenu::initialize() {

	//in full...
	createButton("Play", []() {GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f), glm::vec2(1.0f), 0, HTA::Center, VTA::Center);
	
	//you can omit the last 4 parameters...
	createButton("Practice", doNothingFunc, glm::vec2(0.0f, -60.0f));
	createButton("Settings", doNothingFunc, glm::vec2(0.0f, -120.0f));
	createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -180.0f));
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
	if (KeyInput::isPressed("ESC")) {
		GameWindow::Instance->quit();
	}

	if (KeyInput::isPressed("Z") || KeyInput::isPressed("ENTER")) {
		buttons[selectedButton]->use();
	}
	if (KeyInput::isPressed("DOWN", 10)) {
		selectNext();
	}
	if (KeyInput::isPressed("UP", 10)) {
		selectPrev();
	}
}

void DifficultyMenu::initialize() {

	//in full...
	createButton("Easy", []() {GameWindow::Instance->startGame(Difficulty::Easy, GameMode::All); }, glm::vec2(0.0f), glm::vec2(1.0f), 0, HTA::Center, VTA::Center);

	//you can omit the last 4 parameters...
	createButton("Normal", []() {GameWindow::Instance->startGame(Difficulty::Normal, GameMode::All); }, glm::vec2(0.0f, -60.0f));
	createButton("Hard", []() {GameWindow::Instance->startGame(Difficulty::Hard, GameMode::All); }, glm::vec2(0.0f, -120.0f));
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
	if (KeyInput::isPressed("ESC")) {
		GameWindow::Instance->loadScene(SceneName::MainMenu);
	}
	if (KeyInput::isPressed("Z") || KeyInput::isPressed("ENTER")) {
		buttons[selectedButton]->use();
	}
	if (KeyInput::isPressed("DOWN", 10)) {
		selectNext();
	}
	if (KeyInput::isPressed("UP", 10)) {
		selectPrev();
	}
}
