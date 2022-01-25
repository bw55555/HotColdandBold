#include "MainMenu.h"
#include "GameWindow.h"

void MainMenu::initialize() {

	//in full...
	createButton("Play", []() {GameWindow::settings.mode = GameMode::All; GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("HOT, COLD, & BOLD", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), UI::UIsize);
	
	//you can omit the last 4 parameters...
	createButton("Practice", []() {GameWindow::Instance->loadScene(SceneName::LevelSelectMenu); }, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	createButton("Settings", []() {GameWindow::Instance->loadScene(SceneName::SettingsMenu); }, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
	createButton("Credits", []() {GameWindow::Instance->loadScene(SceneName::Credits); }, glm::vec2(0.0f, -300.0f), glm::vec2(2.0f));
	createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -400.0f), glm::vec2(2.0f));
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
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), UI::UIsize);
	//in full...
	createButton("Easy", []() {GameWindow::Instance->startGame(Difficulty::Easy); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);

	//you can omit the last 4 parameters...
	createButton("Normal", []() {GameWindow::Instance->startGame(Difficulty::Normal); }, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	createButton("Hard", []() {GameWindow::Instance->startGame(Difficulty::Hard); }, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
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

void LevelSelectMenu::initialize() {
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), UI::UIsize);
	//in full...
	createButton("Level 1", []() {GameWindow::settings.mode = GameMode::Prac1; GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);

	//you can omit the last 4 parameters...
	createButton("Level 2", []() {GameWindow::settings.mode = GameMode::Prac2; GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	//createButton("Hard", []() {GameWindow::Instance->startGame(Difficulty::Hard, GameMode::All); }, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
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

void LevelSelectMenu::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->loadScene(SceneName::MainMenu);
	}
	Menu::update();
}

