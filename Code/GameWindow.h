#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "GameLevel.h"

typedef struct GLFWwindow GLFWwindow;

extern std::string PATH_START;

class GameWindow
{
private:
	
public:
	GLFWwindow* window;
	
	static std::shared_ptr<Player> player;
	static unsigned int enemyTextures[10];
	static glm::vec2 screenSize; //set in main.cpp
	
	static const float halfWidth;
	static const float halfHeight;

	static std::shared_ptr<GameWindow> Instance;
	
	Shader* shader;
	Shader* screenShader;
	Shader* textShader;

	unsigned int fbo = 0;
	unsigned int textureColorbuffer = 0;

	glm::mat4 projectionMatrix;
	std::shared_ptr<Scene> scene = nullptr;
	GameWindow(GLFWwindow* w, Shader* s);
	
	void render();
	void update();
	void initialize();
	static void loadTexture(const char* filePath, unsigned int* texturePointer);
	static void loadTexture(std::string filePath, unsigned int* texturePointer);
	static void clearBullets();
	static void clearEnemies();
	static void clearScreen();

	void loadScene(SceneName name);

	void checkCollisions();
	void createEnemyTextures();
};

