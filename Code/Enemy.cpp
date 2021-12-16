#include "Enemy.h"

Enemy::Enemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*)) : CollidableObject(collisionbox, initialPos, textureID, glm::vec3(0.1f, 0.1f, 0.1f)) {
	currTime = 0.0f;
	updatefunc = func;
	enemies.push_back(this);
}

void Enemy::update() {
	currTime += 1.0f;
	updatefunc(this);
}

Enemy::~Enemy() {
	//should delete the pointer in the enemies vector
	for (auto p : spawners)
	{
		delete p;
	}
	spawners.clear();
}

void Enemy::createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*)) {
	BulletSpawner* s = new BulletSpawner(this, initialPos, func);
	spawners.push_back(s);
}