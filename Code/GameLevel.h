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


class GameLevel
{
public:
	typedef void (*UpdateFunc)(GameLevel*);
	UpdateFunc updatefunc;
	std::vector<float> customFloats;

	GameLevel(void (*func)(GameLevel*));
	float currTime;

	void update();
	void setCurrentTime(float time);
	//void setCheckpoint();
};