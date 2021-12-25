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
	
	static float halfWidth;
	static float halfHeight;

	glm::mat4 projectionMatrix;
	std::shared_ptr<GameLevel> level = nullptr;
	GameWindow(GLFWwindow* w, Shader* s);
	void render();
	void update();
	void initialize();
	static void loadTexture(const char* filePath, unsigned int* texturePointer);
	static void loadTexture(std::string filePath, unsigned int* texturePointer);
	void clearScreen();
	void checkCollisions();
};

void enemyTestFunc(Enemy* enemy);
void bulletSpawnerTestFunc(BulletSpawner* spawner);
void Level1(GameLevel* level);

void bulletSpawnerTestFunc2(BulletSpawner* spawner);
void testFunc2(Bullet* b);

void bulletSpawnerTestFuncDisplay(BulletSpawner* spawner);
void spinningDirectionalBulletDisplay(Bullet* b);

void bulletSpawnerTestSpinning(BulletSpawner* spawner);
void spinningDirectionalBullet(Bullet* b);

void bulletSpawnerTest3(BulletSpawner* spawner);
void testFunc3(Bullet* b);

void bulletSpawnerTest4(BulletSpawner* spawner);
void testFunc4(Bullet* b);