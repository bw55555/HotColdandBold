#include "Bullet.h"
Bullet::Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling) {
	currTime = 0.0f;
	updatefunc = func;
	bullets.push_back(this);
}

void Bullet::update(){
	currTime += 1.0f;
	updatefunc(this);
}