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

	GameWindow(GLFWwindow* w, Shader* s);
	void render();
	void update();
	void initialize();
	static void loadTexture(const char* filePath, unsigned int* texturePointer);
	void clearScreen();
	void checkCollisions();
};

void enemyTestFunc(Enemy* enemy);
void bulletSpawnerTestFunc(BulletSpawner* spawner);

class EnemyBuilderInterface // An abstract enemy specification. Extend this in a subclass, and remember to implement all methods!
	// If you aren't sure, check FairyBuilder or ping @KD on discord
{
private: // For consistency, all variables that should be implemented have been defined here
	Hitbox enemyHitbox; // The hitbox to give the enemy
	glm::vec2 position = glm::vec2(0.0f, 500.0f); // Where they begin. By default, x = 0 y = 500
	unsigned int enemyTexture = 0; // Important for the loadTexture function
	void (*func)(Enemy*) = enemyTestFunc; // The movement function for the enemy. By default, enemyTestFunc
public:
	virtual ~EnemyBuilderInterface() {}

	// The following four functions have a default implementation but can be overwritten in subclasses
	void setHitboxInfo(HitboxType type, double radius) {
		// Provides a way to set the two most important properties of Hitbox
		// Other properties are welcome to be set in createEnemy()
		this->enemyHitbox.type = type;
		this->enemyHitbox.radius = radius;
	}

	void loadTexture(const char* filePath, unsigned int* texturePointer) {
		// Simply calls GameWindow's loadTexture function
		GameWindow::loadTexture(filePath, texturePointer);
	}

	void setPosition(glm::vec2 dir) {
		// Sets the starting position for the enemy
		// Remember, if you call this from checkEnemy it may override any passed in parameters!
		this->position = dir;
	}

	void setMovement(void (*func)(Enemy*)) {
		// Sets the movement function for the enemy
		// Remember, if you call this from checkEnemy it may override any passed in parameters!
		this->func = func;
	}

	// Must be implemented!
	virtual std::shared_ptr<Enemy> createEnemy() = 0;
};

class FairyBuilder : public EnemyBuilderInterface { //Builds the Touhou fairy enemy
	// A useful sample implementation
private:
	Hitbox enemyHitbox;
	glm::vec2 position = glm::vec2(0.0f, 500.0f); 
	unsigned int enemyTexture = 0; 
	void (*func)(Enemy*) = enemyTestFunc;
public:
	std::shared_ptr<Enemy> createEnemy() override {
		setHitboxInfo(HitboxType::Circle, 50.0f);

		// TODO: Add a function where you can pass in the img name and get a complete filepath back
		loadTexture("../../resources/textures/TouhouFairy.png", &enemyTexture);

		std::shared_ptr<Enemy> e = Enemy::makeEnemy(enemyHitbox, this->position, enemyTexture, this->func);
		e->customFloats.push_back(1.0f);
		e->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestFunc);
		return e;
	}
};

class DoppleBuilder : public EnemyBuilderInterface { //Builds a scary Doppleganger!
	// A useful sample implementation
private:
	Hitbox enemyHitbox;
	glm::vec2 position = glm::vec2(0.0f, 500.0f);
	unsigned int enemyTexture = 0;
	void (*func)(Enemy*) = enemyTestFunc;
public:
	std::shared_ptr<Enemy> createEnemy() override {
		setHitboxInfo(HitboxType::Circle, 5.0f);

		// TODO: Add a function where you can pass in the img name and get a complete filepath back
		loadTexture("../../resources/textures/scaryface.png", &enemyTexture);

		std::shared_ptr<Enemy> e = Enemy::makeEnemy(enemyHitbox, this->position, enemyTexture, this->func);
		e->customFloats.push_back(1.0f);
		e->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestFunc);
		return e;
	}
};

class EnemyBuildDirector // Called in .cpp, provides information to correct builder
{
public:
	std::shared_ptr<Enemy> buildEnemy(class EnemyBuilderInterface* builder, glm::vec2 dir = glm::vec2(0.0f, 500.0f), void (*func)(Enemy*) = enemyTestFunc) {
		// First parameter is the builder implementation to pass in
		// Second is a vec2 that defaults to a location in the top/center of the screen
		builder->setPosition(dir);
		builder->setMovement(func);
		return builder->createEnemy();
	}
};