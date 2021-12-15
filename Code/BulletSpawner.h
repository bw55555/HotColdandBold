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

class BulletSpawner
{
public:
	static unsigned int bulletPresetTextures[];

	typedef void (*UpdateFunc)(BulletSpawner*);
	UpdateFunc updatefunc;

	glm::vec3 pos;
	float currTime;

	BulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*));
	void update();

	void spawnBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*));
	Bullet* spawnPreset(unsigned int type, glm::vec2 pos, void (*func)(Bullet*));
};

