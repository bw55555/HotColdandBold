#include "BulletSpawner.h"
#include "Enemy.h"


BulletSpawner::BulletSpawner(Enemy* parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*)) {
	parent = parentPointer;
	currTime = 0.0f;
	updatefunc = func;
	localPos = glm::vec3(initialPos, 0.0f);
	pos = localPos + parent->getPos();
}

BulletSpawner::BulletSpawner(Enemy* parentPointer, glm::vec3 initialPos, void (*func)(BulletSpawner*)) {
	parent = parentPointer;
	currTime = 0.0f;
	updatefunc = func;
	localPos = initialPos;
	pos = localPos + parent->getPos();
}

void BulletSpawner::update() {
	currTime += 1.0f;
	if (parent != nullptr) {
		pos = localPos + parent->getPos();
	}
	else {
		pos = localPos;
	}
	updatefunc(this);
}

void BulletSpawner::spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*)) {
	
}

Bullet* BulletSpawner::spawnPreset(unsigned int type, glm::vec2 pos, void (*func)(Bullet*)) {
	if (type == 0) {
		Hitbox h;
		h.center = 0;
		//hitbox whatevers
		return new Bullet(h, pos, bulletPresetTextures[0], func);
	}
	return nullptr;
}