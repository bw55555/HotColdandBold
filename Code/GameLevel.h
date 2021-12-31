#pragma once

#include "Sprite.h"
#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "UpdateTime.h"

class GameLevel : public UpdateTime<GameLevel>
{
public:
	GameLevel(void (*func)(GameLevel*));
	void update();
	
	//void setCheckpoint();
};

namespace Level {
	typedef BulletSpawner* BSp;
	typedef Bullet* Bp;
	typedef Enemy* Ep;
	typedef std::shared_ptr<Enemy> Esp;
	typedef std::shared_ptr<Bullet> Bsp;
	typedef std::shared_ptr<BulletSpawner> BSsp;
}