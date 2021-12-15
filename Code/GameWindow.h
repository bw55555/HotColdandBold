#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sprite.h"
#include "Player.h"

class GameWindow
{
private:
	unsigned int playerTexture;
	GLFWwindow* window;
	Shader* shader;
	Player* player;
public:
	GameWindow(GLFWwindow* w, Shader* s);
	void render();
	void update();
	void initialize();
	void loadTexture(const char* filePath, unsigned int* texturePointer);
};

