#include "BulletSpawner.h"
#include "Enemy.h"


BulletSpawner::BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*)) : UpdateTime<BulletSpawner>(func){
	parent = std::weak_ptr<Enemy>(parentPointer);
	localPos = initialPos;

	pos = localPos + parentPointer->getPos();
}
void BulletSpawner::update() {
	auto p = parent.lock();
	if (p) {
		pos = localPos + p->getPos();
	}
	else {
		pos = localPos;
	}
	frameUpdate(this);
}

std::shared_ptr<Bullet> BulletSpawner::spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*)) {
	return Bullet::makeBullet(collisionbox, initialPos, textureID, func);
}

std::shared_ptr<Bullet> BulletSpawner::spawnPreset(BulletType type, glm::vec2 pos, void (*func)(Bullet*)) {
	if (type == BulletType::RoundBlue) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 15.0f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[0], func);
	}
	if (type == BulletType::KnifeBlue) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 15.0f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[1], func);
	}
	if (type == BulletType::RoundRed) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 25.0f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[2], func);
	}
	if (type == BulletType::KnifeRed) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 15.0f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[3], func);
	}
	return std::shared_ptr<Bullet>(nullptr);
}