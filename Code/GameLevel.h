#pragma once

#include "Enemy.h"
#include "BulletSpawner.h"
#include "DropItem.h"
#include "UpdateTime.h"
#include "Scene.h"
#include "UI.h"

class GameLevel : public UpdateTime<GameLevel>, public Scene
{
public:
	GameLevel(void (*func)(GameLevel*));
	void initialize() override;
	void update() override;
	void render() override;

	std::unique_ptr<UI> ui;
	//void setCheckpoint();
};

namespace Level {
	typedef GameLevel* GLp;
	typedef BulletSpawner* BSp;
	typedef Bullet* Bp;
	typedef Enemy* Ep;
	typedef std::shared_ptr<Enemy> Esp;
	typedef std::shared_ptr<Bullet> Bsp;
	typedef std::shared_ptr<BulletSpawner> BSsp;
}