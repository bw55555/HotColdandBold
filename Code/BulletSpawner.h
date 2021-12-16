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

	glm::vec3 localPos;
	glm::vec3 pos;
	float currTime;
	Enemy* parent;
	std::vector<Bullet*> bullets;

	BulletSpawner(Enemy* parentPointer, glm::vec2 initialPos, void (*func)(BulletSpawner*));
	BulletSpawner(Enemy* parentPointer, glm::vec3 initialPos, void (*func)(BulletSpawner*));
	void update();

	void spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*));
	Bullet* spawnPreset(unsigned int type, glm::vec2 pos, void (*func)(Bullet*));
};

