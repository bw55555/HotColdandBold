#include "BulletSpawner.h"
#include "Enemy.h"
#include "SoundEffect.h"

BulletSpawner::BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*)) : UpdateTime<BulletSpawner>(func){
	parent = std::weak_ptr<Enemy>(parentPointer);
	localPos = initialPos;

	pos = localPos + parentPointer->getPos();
}

BulletSpawner::BulletSpawner(std::shared_ptr<Bullet> parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*)) : UpdateTime<BulletSpawner>(func) {
	parent = std::weak_ptr<Bullet>(parentPointer);
	localPos = initialPos;

	pos = localPos + parentPointer->getPos();
}
void BulletSpawner::update() {

	pos = localPos + std::visit([](auto&& arg) -> glm::vec2 {
		if (auto p = arg.lock(); p) {
			return p->getPos();
		}
		else {
			return glm::vec2(0);
		}
	}, parent);
	
	frameUpdate(this);
}

std::shared_ptr<Bullet> BulletSpawner::spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*)) {
	return Bullet::makeBullet(collisionbox, initialPos, textureID, func);
}

std::shared_ptr<Bullet> BulletSpawner::spawnPreset(BulletType type, glm::vec2 pos, void (*func)(Bullet*)) {
	SoundEffect::play(SFXType::Shot);
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
	if (type == BulletType::BallBlackBorder) {
		Hitbox h;
		h.type = HitboxType::Circle;
		h.radius = 40.0f;
		//hitbox whatevers
		return Bullet::makeBullet(h, pos, bulletPresetTextures[4], func, glm::vec3(100.0f));
	}
	if (type == BulletType::DotWhite) {
		//hitbox whatevers
		return Bullet::makeBullet(Hitbox::Circle(10.0f), pos, bulletPresetTextures[5], func, glm::vec3(20.0f));
	}
	return std::shared_ptr<Bullet>(nullptr);
}