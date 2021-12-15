#include "Bullet.h"
Bullet::Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*)) : CollidableObject(collisionbox, initialPos, textureID) {
	currTime = 0.0f;
	updatefunc = func;
}

void Bullet::update(){
	currTime += 1.0f;
	updatefunc(this);
}