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

void Bullet::directionalBullet(Bullet* bullet) {
    //bullet with constant speed in a direction
    //speed, x, y
    if (bullet->customFloats.size() == 0) {
        bullet->customFloats.push_back(0.02f);
        bullet->customFloats.push_back(0.0f);
        bullet->customFloats.push_back(1.0f);
    }
    bullet->move(bullet->customFloats[0] * glm::vec2(bullet->customFloats[1], bullet->customFloats[2]));
}