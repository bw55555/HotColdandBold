#include "Bullet.h"
#include "Enemy.h"
Bullet::Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling) {
    //never use this, it screws with shared pointers! use makeBullet instead
    currTime = 0.0f;
	updatefunc = func;
    isBullet = true;
}

std::shared_ptr<Bullet> Bullet::makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) {
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(collisionbox, initialPos, textureID, func, scaling);
    bullets.push_back(bullet);
    return bullet;
}

void Bullet::update(){
	currTime += 1.0f;
	updatefunc(this);
}

void Bullet::directionalBullet(Bullet* bullet) {
    //bullet with constant speed in a direction
    //customFloats: speed, x, y
    if (bullet->customFloats.size() == 0) {
        bullet->customFloats.push_back(0.02f);
        bullet->customFloats.push_back(0.0f);
        bullet->customFloats.push_back(1.0f);
    }
    bullet->move(bullet->customFloats[0] * glm::vec2(bullet->customFloats[1], bullet->customFloats[2]));
}

void Bullet::homingBullet(Bullet* bullet) {
    //bullet that follows the nearest enemy
    //speed
    if (bullet->customFloats.size() == 0) {
        bullet->customFloats.push_back(0.02f);
    }
    std::shared_ptr<Enemy> enemy = Enemy::findNearestEnemy(bullet->getPos());
    if (!enemy) {
        bullet->move(glm::vec2(0.0f, 0.02f));
    }
    else {
        glm::vec2 dir = glm::normalize(bullet->getPos() - enemy->getPos());
        bullet->move(bullet->customFloats[0] * glm::vec2(bullet->customFloats[1], bullet->customFloats[2]));
    }
}

Bullet::~Bullet() {
    //bullets.erase(std::begin(bullets));
}