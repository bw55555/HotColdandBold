#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Shader.h>
#include "stb_image.h"
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "GameLevel.h"


extern std::string PATH_START;

class GameWindow
{
private:
	GLFWwindow* window;
	Shader* shader;
public:
	static std::shared_ptr<Player> player;
	static unsigned int enemyTextures[10];
	static const glm::vec2 normalized_coordinate_axes; //set in main.cpp
	
	static const float halfWidth;
	static const float halfHeight;

	glm::mat4 projectionMatrix;
	std::shared_ptr<GameLevel> level = nullptr;
	GameWindow(GLFWwindow* w, Shader* s);

	void render();
	void update();
	void initialize();
	static void loadTexture(const char* filePath, unsigned int* texturePointer);
	static void loadTexture(std::string filePath, unsigned int* texturePointer);
	void clearBullets();
	void clearEnemies();
	void clearScreen();
	void checkCollisions();
	void createEnemyTextures();
};

