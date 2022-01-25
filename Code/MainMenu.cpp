#include "MainMenu.h"
#include "GameWindow.h"

void MainMenu::initialize() {

	//in full...
	makeText("Play", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, 0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Play", []() {GameWindow::settings.mode = GameMode::All; GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("HOT, COLD, & BOLD", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.1f, 3.2f), 0, HTA::Center, VTA::Center);
	makeText("HOT, COLD, & BOLD", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	
	//you can omit the last 4 parameters...
	makeText("Practice", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Practice", []() {GameWindow::Instance->loadScene(SceneName::LevelSelectMenu); }, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	makeText("Instructions", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -200.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Instructions", []() {GameWindow::Instance->loadScene(SceneName::InstructionsMenu); }, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
	makeText("Settings", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -300.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Settings", []() {GameWindow::Instance->loadScene(SceneName::SettingsMenu); }, glm::vec2(0.0f, -300.0f), glm::vec2(2.0f));
	makeText("Credits", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -400.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Credits", []() {GameWindow::Instance->loadScene(SceneName::Credits); }, glm::vec2(0.0f, -400.0f), glm::vec2(2.0f));
	makeText("Quit", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -500.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -500.0f), glm::vec2(2.0f));
	
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
	makeSprite(Sprite::backgroundTextures[1], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	//in full...
	makeText("Easy", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, 0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Easy", []() {GameWindow::Instance->startGame(Difficulty::Easy); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);

	//you can omit the last 4 parameters...
	makeText("Medium", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Normal", []() {GameWindow::Instance->startGame(Difficulty::Normal); }, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f));
	makeText("Hard", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -200.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
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
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	//in full...
	makeText("Level 1", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, 0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	createButton("Level 1", []() {GameWindow::settings.mode = GameMode::Prac1; GameWindow::Instance->loadScene(SceneName::DifficultyMenu); }, glm::vec2(0.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Level 2", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-10.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
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

void InstructionsMenu::initialize() {
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), glm::vec2(2000.0f, 2000.0f));
	makeText("INSTRUCTIONS", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.1f, 3.2f), 0, HTA::Center, VTA::Center);
	makeText("INSTRUCTIONS", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 700.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);

	makeText("WASD to control your Phoenix.", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, 500.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Hold Z to fire fireballs and homing fireballs.", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, 300.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Hold shift to move slowly for maneuvering, sacrificing your homing fireballs.", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, 100.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("X to use bombs that destroy all normal enemies on screen while significantly damaging bosses.", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, -100.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("The less heat you have, the slower you move, so pick up heat dropped from enemies!", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, -300.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Collecting enough heat will SUPERCHARGE you, briefly granting you invincibility, an extra life, and improved damage.", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, -500.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Beware the many deadly phases of the minibosses and bosses!", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(-1405.0f, -700.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	
	makeText("WASD to control your Phoenix.", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, 500.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Hold Z to fire fireballs and homing fireballs.", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, 300.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Hold shift to move slowly for maneuvering, sacrificing your homing fireballs.", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, 100.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("X to use bombs that destroy all normal enemies on screen while significantly damaging bosses.", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, -100.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("The less heat you have, the slower you move, so pick up heat dropped from enemies!", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, -300.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Collecting enough heat will SUPERCHARGE you, briefly granting you invincibility, an extra life, and improved damage.", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, -500.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
	makeText("Beware the many deadly phases of the minibosses and bosses!", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(-1400.0f, -700.0f), glm::vec2(1.0f), 0, HTA::Left, VTA::Center);
}

void InstructionsMenu::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->loadScene(SceneName::MainMenu);
	}
	Menu::update();
}

