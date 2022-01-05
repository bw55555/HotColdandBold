#include "BossEnemy.h"
#include "GameWindow.h"

BossEnemy::BossEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) : Enemy(collisionbox, initialPos, textureID, func, scaling) {
	//never use this, use makeEnemy instead. Ever. It screws with shared pointers. 
	createBossHealthBar();
	numPhases = countPhases();
}

std::shared_ptr<Enemy> BossEnemy::makeBossEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) {
	std::shared_ptr<Enemy> e = static_cast<std::shared_ptr<Enemy>>(std::make_shared<BossEnemy>(collisionbox, initialPos, textureID, func, scaling));
	Enemy::enemies.push_back(e);
	return e;
}

void BossEnemy::update() {
	//update the health bar here.
	countedPhases = 0;
	frameUpdate(this);
}

void BossEnemy::destroy() {
	if (currPhase >= numPhases) {
		destroyed = true;
		collisionEnabled = false;
		renderEnabled = false;
	}
	else {
		startNextPhase();
		GameWindow::clearBullets();
	}
}

BossEnemy::~BossEnemy() {
	//should delete the pointers in the spawners vector
	spawners.clear();
}

void BossEnemy::createBossHealthBar() {
	bossHealthBar = std::unique_ptr<Sprite>(nullptr);
	//create the health bar... somehow
	//well, we definitely don't need textures for this, just an expanding square
}

void BossEnemy::startNextPhase() {
	currPhase += 1;
	currTime = 0;
	reInitializeTime();
	spawners.clear();
	//remember to reset health and stuff... or set to a default and let 
}

int BossEnemy::countPhases() {
	numPhases = 0;
	shouldRun = false;
	updatefunc(static_cast<Enemy*>(this));
	shouldRun = true;
	return countedPhases;
}

bool BossEnemy::onNextPhase() {
	countedPhases += 1;
	if (countedPhases == currPhase) {
		return shouldRun;
	}
	return false;
}