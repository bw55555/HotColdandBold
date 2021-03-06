#include "Bullet.h"
#include "BulletSpawner.h"
Bullet::Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling), UpdateTime<Bullet>(func) {
    //never use this, it screws with shared pointers! use makeBullet instead
}

std::shared_ptr<Bullet> Bullet::makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) {
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(collisionbox, initialPos, textureID, func, scaling);
    bullets.push_back(bullet);
    return bullet;
}

void Bullet::update() {
    if (checkDestruction()) { return; }
    frameUpdate(this);
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

BulletSpawner* Bullet::createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*)) {
    std::unique_ptr<BulletSpawner> s = std::make_unique<BulletSpawner>(shared_from_this(), initialPos, func);
    spawners.push_back(std::move(s));
    return spawners[spawners.size() - 1].get();
}

Bullet::~Bullet() {
    spawners.clear();
}