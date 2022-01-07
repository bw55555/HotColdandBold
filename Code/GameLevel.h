#pragma once

#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "UpdateTime.h"
#include "Scene.h"

class GameLevel : public UpdateTime<GameLevel>, public Scene
{
public:
	GameLevel(void (*func)(GameLevel*));
	void initialize() override;
	void update() override;
	void render() override;
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