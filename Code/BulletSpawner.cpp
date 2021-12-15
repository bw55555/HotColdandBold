#include "BulletSpawner.h"

BulletSpawner::BulletSpawner(glm::vec2 initialPos, void (*updatefunction)(BulletSpawner*)) {
	currTime = 0.0f;
	updatefunc = updatefunction;
	pos = glm::vec3(initialPos, 0.0f);
}

void BulletSpawner::update() {
	currTime += 1.0f;
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