#include "MainMenu.h"
#include "GameWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

void MainMenu::initialize() {
	createButton("Play", []() {GameWindow::Instance->loadScene(SceneName::Level1); }, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
	//createButton("X", doNothingFunc, glm::vec3(1.0f), glm::vec3(0.0f), 0, HTA::Center, VTA::Center);
}

void MainMenu::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& b : buttons) {
		b->draw(GameWindow::Instance->textShader);
	}
}

void MainMenu::update() {
	GLFWwindow* w = GameWindow::Instance->window;
	if (glfwGetKey(w, GLFW_KEY_ENTER) == GLFW_PRESS) {
		buttons[selectedButton]->use();
	}
}
