#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Bullet.h"

class Enemy;

class BulletSpawner
{
public:
	static unsigned int bulletPresetTextures[];

	typedef void (*UpdateFunc)(BulletSpawner*);
	UpdateFunc updatefunc;
	std::vector<float> customFloats;

	glm::vec2 localPos;
	glm::vec2 pos;
	float currTime;
	std::weak_ptr<Enemy> parent;

	BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*));
	BulletSpawner(std::shared_ptr<Enemy> parentPointer, glm::vec3 initialPos, void (*func)(BulletSpawner*));
	void update();

	void spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*));
	std::shared_ptr<Bullet> spawnPreset(unsigned int type, glm::vec2 pos, void (*func)(Bullet*));
	
	template<class T>
	std::shared_ptr<Bullet> spawnPreset(unsigned int type, glm::vec2 pos, T iFunc) {
		//static_assert(std::is_base_of<Bullet::BulletInitializer, T>::value, "template type must be a derived class of BulletInitializer");
		std::shared_ptr<Bullet> b = spawnPreset(type, pos, iFunc.f);
		iFunc.init(b);
		return b;
	}
};

