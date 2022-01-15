#include "BossEnemy.h"
#include "GameWindow.h"
#include "UIRect.h"

glm::vec3 hbInitScale = glm::vec3(1400.0f, 32.0f, 0.0f);

BossEnemy::BossEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) : Enemy(_health, collisionbox, initialPos, textureID, func, scaling) {
	//never use this, use makeEnemy instead. Ever. It screws with shared pointers. 
	maxHealth = _health;
	createBossHealthBar();
	numPhases = countPhases();
	setDFunc([](Enemy* e) {
		for (int i = 0; i < 20; i++) {
			DropItem::makeDropItem(DropItemType::Heat, e->getPos() + Movement::randomDir() * Movement::randomFloat(0.0f, 300.0f), DropItem::gravityDropFunc);
		}
	});
}

std::shared_ptr<Enemy> BossEnemy::makeBossEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) {
	std::shared_ptr<Enemy> e = static_cast<std::shared_ptr<Enemy>>(std::make_shared<BossEnemy>(_health, collisionbox, initialPos, textureID, func, scaling));
	Enemy::enemies.push_back(e);
	return e;
}

void BossEnemy::update() {
	//update the health bar here.
	countedPhases = 0;
	frameUpdate(this);

	bossHealthBar->scale.x = hbInitScale.x * health/maxHealth;
	//bossHealthBar->scale = glm::vec3(WindowVar::wvar4, 1.0f);
	//bossHealthBar->trans = glm::vec3(WindowVar::wvar3, 1.0f);

}

void BossEnemy::destroy() {
	dfunc(static_cast<Enemy*>(this));
	if (currPhase >= numPhases) {
		//bossHealthBar = nullptr;
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
	bossHealthBar = nullptr;
}

void BossEnemy::createBossHealthBar() {
	bossHealthBar = std::make_unique<UIRect>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), hbInitScale, glm::vec3(-600.0f, 920.0f, 1.0f));
	//create the health bar... somehow
	//well, we definitely don't need textures for this, just an expanding square
}

void BossEnemy::startNextPhase() {
	currPhase += 1;
	health = maxHealth;
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

void BossEnemy::draw() {
	Sprite::draw();
}

void BossEnemy::setMaxHealth(float _maxHealth) {
	maxHealth = _maxHealth;
	health = _maxHealth;
}