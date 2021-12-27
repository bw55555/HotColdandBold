#include "Enemy.h"

Enemy::Enemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling) {
	//never use this, use makeEnemy instead. Ever. It screws with shared pointers. 
	currTime = 0.0f;
	updatefunc = func;
}

std::shared_ptr<Enemy> Enemy::makeEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling) {
	std::shared_ptr<Enemy> e = std::make_shared<Enemy>(collisionbox, initialPos, textureID, func, scaling);
	enemies.push_back(e);
	return e;
}

std::shared_ptr<Enemy> Enemy::findNearestEnemy(glm::vec2 pos) {
	float minDistance = -1.0f;
	std::shared_ptr<Enemy> minDistEnemy = std::shared_ptr<Enemy>(nullptr);
	for (std::shared_ptr<Enemy> e : Enemy::enemies) {
		float dist = glm::distance(pos, e->getPos());
		if (minDistance < 0 || dist < minDistance) {
			minDistance = dist;
			minDistEnemy = e;
		}
	}
	return minDistEnemy;
}

void Enemy::update() {
	currTime += 1.0f;
	updatefunc(this);
}

void Enemy::destroy() {
	destroyed = true;
	collisionEnabled = false;
	renderEnabled = false;
}

Enemy::~Enemy() {
	//should delete the pointer in the enemies vector
	spawners.clear();
}

void Enemy::createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*)) {
	std::unique_ptr<BulletSpawner> s = std::make_unique<BulletSpawner>(shared_from_this(), initialPos, func);
	spawners.push_back(std::move(s));
}