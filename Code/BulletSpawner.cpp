#include "BulletSpawner.h"
#include "Enemy.h"


BulletSpawner::BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*)) {
	parent = std::weak_ptr<Enemy>(parentPointer);
	currTime = 0.0f;
	updatefunc = func;
	localPos = initialPos;

	pos = localPos + parentPointer->getPos();
}

BulletSpawner::BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec3 initialPos, void (*func)(BulletSpawner*)) {
	parent = parentPointer;
	currTime = 0.0f;
	updatefunc = func;
	localPos = glm::vec2(initialPos);
	pos = localPos + parentPointer->getPos();
}

void BulletSpawner::update() {
	currTime += 1.0f;
	auto p = parent.lock();
	if (p) {
		pos = localPos + p->getPos();
	}
	else {
		pos = localPos;
	}
	updatefunc(this);
}

void BulletSpawner::spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*)) {
	
}

std::shared_ptr<Bullet> BulletSpawner::spawnPreset(unsigned int type, glm::vec2 pos, void (*func)(Bullet*)) {
	if (type == 0) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 0.025f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[0], func);
	}
	if (type == 1) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 0.025f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[1], func);
	}
	if (type == 2) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 0.05f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[1], func, glm::vec3(0.1f));
	}
	return std::shared_ptr<Bullet>(nullptr);
}