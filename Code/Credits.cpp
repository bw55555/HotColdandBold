#include "Credits.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void Credits::initialize() {
	credTimer = 1680;
	makeRect(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), Pos(0.0f, 0.0f), Scale(UI::UIsize));
	makeText("CREDITS", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -1000.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Created by Brian Wang", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -1300.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Made in OpenGL", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -1600.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Art Direction by Nealon Soltanpour", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -1900.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Main Programming by Brian Wang", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -2200.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Secondary Programming by Nealon Soltanpour", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -2500.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Gameplay by Brian Wang and Nealon Soltanpour", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -2800.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("UI by Brian Wang and Nealon Soltanpour", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -3100.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("QA Testing by Nealon Soltanpour", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -3400.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Helpers: Yassin Mostafa and Kevin Portinger", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -3700.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Music by ZUN and danmaq", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -4000.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Phoenix Sprite by Ki-Shine", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -4300.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Ice Dragon Art from Final Fantasy Dimensions II", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -4600.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Santa Claus Art from Christmas Pixel Art", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -4900.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Level 1 Art by Animefox52", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -5200.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Icicle Art from Super Mario Maker 2", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -5500.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("SPECIAL THANKS TO ZUN FOR TOUHOU", glm::vec3(0.6f, 1.0f, 1.0f), glm::vec2(0.0f, -5800.0f), glm::vec2(2.0f), 0, HTA::Center, VTA::Center);
	makeText("Thanks for Playing!", glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, -6100.0f), glm::vec2(4.0f), 0, HTA::Center, VTA::Center);
	
}


void Credits::update() {
	Menu::update();
	int amt = 1;
	if (KeyInput::isPressed("Z", -1)) {
		amt = 3;
	}
	if (credTimer > 0) {
		for (auto& t : texts) {
			t->trans.y += 5 * amt;
		}
		credTimer -= amt;
	}
	else {
		GameWindow::Instance->mainMenu();
	}
}

void Credits::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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