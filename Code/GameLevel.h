#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sprite.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "UpdateTime.h"

class GameLevel : public UpdateTime<GameLevel>
{
public:
	GameLevel(void (*func)(GameLevel*));
	
	bool runLevel = true;
	void update();
	
	//void setCheckpoint();
};