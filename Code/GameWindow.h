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
#include "SoundEffect.h"
#include "AnimatedSprite.h"

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
	bool over = false;
	bool won = false;
	bool shouldLoadNextScene = false;
	bool credit = false;
	int winTimer = 0;
	std::shared_ptr<Scene> pauseMenu = nullptr;
	std::shared_ptr<Scene> overMenu = nullptr;
	std::shared_ptr<Scene> winMenu = nullptr;
	std::shared_ptr<Scene> credits = nullptr;

	std::shared_ptr<Audio> mainLoopMusic;

	static Settings settings;

	static std::shared_ptr<Player> player;
	static unsigned int playerTexture;
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

	void initializePlayer();
	void loadScene(SceneName name);

	void startGame(Difficulty d) {
		return startGame(d, settings.mode);
	}
	void startGame(Difficulty, GameMode);

	void checkCollisions();
	void createEnemyTextures();

	void setPause(bool _pause);
	void setLost(bool dead);
	void setWin(bool win);
	void setCredits(bool cred);
	void undeadify();
	void mainMenu();
	void restart();

};

