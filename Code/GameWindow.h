#pragma once
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "GameLevel.h"
#include "KeyInput.h"
#include "Settings.h"
#include "WindowVar.h"

typedef struct GLFWwindow GLFWwindow;

extern std::string PATH_START;

class GameWindow
{
private:
	
public:
	//static unsigned int screenFBO;
	//static unsigned int screenFBOTexture;

	GLFWwindow* window;

	float frameRate;
	bool paused = false;
	std::shared_ptr<Scene> pauseMenu = nullptr;

	static Settings settings;

	static std::shared_ptr<Player> player;
	static unsigned int enemyTextures[10];
	static glm::vec2 screenSize; //set in main.cpp
	
	static const float halfWidth;
	static const float halfHeight;

	static std::shared_ptr<GameWindow> Instance;

	static void quit();
	
	static Shader* shader;
	static Shader* rectShader;
	static Shader* screenShader;
	static Shader* textShader;
	
	std::shared_ptr<Scene> scene = nullptr;
	SceneName currScene;

	GameWindow(GLFWwindow* w);
	
	void render();
	void update();
	void initialize();
	static void loadTexture(const char* filePath, unsigned int* texturePointer);
	static void loadTexture(std::string filePath, unsigned int* texturePointer);
	static void clearBullets();
	static void clearEnemies();
	static void clearScreen();

	void loadScene(SceneName name);
	void startGame(Difficulty, GameMode);

	void checkCollisions();
	void createEnemyTextures();

	void setPause(bool _pause);

};

