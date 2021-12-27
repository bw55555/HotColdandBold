#include "Bullet.h"
Bullet::Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling) {
    //never use this, it screws with shared pointers! use makeBullet instead
    currTime = 0.0f;
	updatefunc = func;
}

std::shared_ptr<Bullet> Bullet::makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) {
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(collisionbox, initialPos, textureID, func, scaling);
    bullets.push_back(bullet);
    return bullet;
}

void Bullet::update() {
    if (checkDestruction()) { return; }
	currTime += 1.0f;
	updatefunc(this);
}

bool Bullet::checkDestruction() {
    if (destroyFlags.destroyTime != -1 && currTime >= destroyFlags.destroyTime) {
        destroy();
        return true;
    }

    if (destroyFlags.offScreen && !isOnScreen()) {
        destroy();
        return true;
    }
    return false;
}

void Bullet::destroy() {
    destroyed = true;
    collisionEnabled = false;
    renderEnabled = false;
}