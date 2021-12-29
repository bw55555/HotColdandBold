#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Bullet.h"
#include "UpdateTime.h"

class Enemy;

enum class BulletType { RoundBlue, Knife, RoundRed };

class BulletSpawner : public UpdateTime<BulletSpawner>
{
public:
	static unsigned int bulletPresetTextures[];

	glm::vec2 localPos;
	glm::vec2 pos;
	std::weak_ptr<Enemy> parent;

	BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*));
	void update();

	std::shared_ptr<Bullet> spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*));
	std::shared_ptr<Bullet> spawnPreset(BulletType type, glm::vec2 pos, void (*func)(Bullet*));
	inline std::shared_ptr<Bullet> spawnPresetwLambda(BulletType type, glm::vec2 pos, void (*func)(Bullet*)) { return spawnPreset(type, pos, func); };
	
	template<class T>
	std::shared_ptr<Bullet> spawnPreset(BulletType type, glm::vec2 pos, T iFunc) {
		//static_assert(std::is_base_of<Bullet::BulletInitializer, T>::value, "template type must be a derived class of BulletInitializer");
		std::shared_ptr<Bullet> b = spawnPreset(type, pos, iFunc.f);
		iFunc.init(b);
		return b;
	}
};

