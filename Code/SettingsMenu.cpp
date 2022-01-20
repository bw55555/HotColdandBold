#include "SettingsMenu.h"
#include "GameWindow.h"
#include "SoundEffect.h"


void SettingsMenu::initialize() {

	//in full...
	createButton("BG Volume", []() {}, glm::vec2(0.0f, 100.0f), glm::vec2(2.0f), 0, HTA::Right, VTA::Center);
	createButton("SFX Volume", []() {}, glm::vec2(0.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Right);
	createButton("Return to Main Menu", []() {GameWindow::Instance->loadScene(SceneName::MainMenu); }, glm::vec2(0.0f, -500.0f), glm::vec2(2.0f), 0, HTA::Center);
	
	makeText("", glm::vec3(0.0f), glm::vec2(50.0f, 100.0f), glm::vec2(2.0f), 0, HTA::Left, VTA::Center);
	makeText("", glm::vec3(0.0f), glm::vec2(50.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Left);
	
	makeSprite(Sprite::backgroundTextures[0], glm::vec2(0.0f, 0.0f), UI::UIsize);
	//createButton("Settings", doNothingFunc, glm::vec2(0.0f, -200.0f), glm::vec2(2.0f));
	//createButton("Quit", GameWindow::quit, glm::vec2(0.0f, -300.0f), glm::vec2(2.0f));
	//createButton("X", doNothingFunc, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
}

void SettingsMenu::update() {
	texts[0]->text = std::to_string(static_cast<int>(std::round(100 * Audio::bgVolume))) + "%";
	texts[1]->text = std::to_string(static_cast<int>(std::round(100 * Audio::sfxVolume))) + "%";
	if (KeyInput::isPressed("LEFT", 10000)) {
		if (selectedButton == 0) {
			Audio::bgVolume -= 0.05f;
			Audio::bgVolume = std::clamp(Audio::bgVolume, 0.0f, 1.0f);
			GameWindow::Instance->mainLoopMusic->setVolume(Audio::bgVolume);
		}
		else if (selectedButton == 1) {
			Audio::sfxVolume -= 0.05f;
			Audio::sfxVolume = std::clamp(Audio::sfxVolume, 0.0f, 1.0f);
			SoundEffect::play(SFXType::Shot);
		}
	}
	if (KeyInput::isPressed("RIGHT", 10000)) {
		if (selectedButton == 0) {
			Audio::bgVolume += 0.05f;
			Audio::bgVolume = std::clamp(Audio::bgVolume, 0.0f, 1.0f);
			GameWindow::Instance->mainLoopMusic->setVolume(Audio::bgVolume);
		}
		else if (selectedButton == 1) {
			Audio::sfxVolume += 0.05f;
			Audio::sfxVolume = std::clamp(Audio::sfxVolume, 0.0f, 1.0f);
			SoundEffect::play(SFXType::Shot);
		}
		
		
	}

	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->loadScene(SceneName::MainMenu);
	}
	Menu::update();
}