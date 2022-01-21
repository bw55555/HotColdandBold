#include "WinMenu.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void WinMenu::initialize() {
	makeRect(glm::vec4(0.0f, 0.0f, 0.0f, 0.7f), Pos(-600.0f, 0.0f), Scale(2 * GameWindow::halfWidth, 2 * GameWindow::halfHeight));
	makeText("LEVEL COMPLETE", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-600.0f, 200.0f), glm::vec2(3.0f), 0, HTA::Center, VTA::Center);
	makeText("Damage Taken", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-800.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("0", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-200.0f, -100.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Bombs Used", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-800.0f, -200.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("0", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-200.0f, -200.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Continues Used", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-800.0f, -300.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("0", glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-200.0f, -300.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
}

void WinMenu::update() {
	if (KeyInput::isPressed("ESC", 1000000)) {
		GameWindow::Instance->quit();
	}
	int damage = 3 - GameWindow::Instance->player->health;
	int bombsUsed = 100 - GameWindow::Instance->player->bombs;
	int contUsed = 3 - GameWindow::Instance->player->continues;
	texts[2]->text = std::to_string(static_cast<int>(damage));
	texts[4]->text = std::to_string(static_cast<int>(bombsUsed));
	texts[6]->text = std::to_string(static_cast<int>(contUsed));

	Menu::update();
}

void WinMenu::render() {

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