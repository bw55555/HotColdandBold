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
#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "GameLevel.h"

class GameWindow
{
private:
	GLFWwindow* window;
	Shader* shader;
public:
	static Player* player;
	static unsigned int enemyTextures[10];
	static const glm::vec2 normalized_coordinate_axes; //set in main.cpp
	
	static float halfWidth;
	static float halfHeight;

	glm::mat4 projectionMatrix;
	GameLevel* level = nullptr;
	GameWindow(GLFWwindow* w, Shader* s);
	void render();
	void update();
	void initialize();
	void loadTexture(std::string filePath, unsigned int* texturePointer);
	void loadTexture(const char* filePath, unsigned int* texturePointer);
	void clearScreen();
	void checkCollisions();
};

void enemyTestFunc(Enemy* enemy);
void bulletSpawnerTestFunc(BulletSpawner* spawner);
void Level1(GameLevel* level);