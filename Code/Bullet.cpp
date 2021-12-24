#include "Bullet.h"
#include "Enemy.h"
Bullet::Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) : CollidableObject(collisionbox, initialPos, textureID, scaling) {
    //never use this, it screws with shared pointers! use makeBullet instead
    currTime = 0.0f;
	updatefunc = func;
    destroyTime = 10000.0f;
}

std::shared_ptr<Bullet> Bullet::makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling) {
    std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(collisionbox, initialPos, textureID, func, scaling);
    bullets.push_back(bullet);
    return bullet;
}

void Bullet::update() {
	currTime += 1.0f;
	updatefunc(this);
    if (currTime >= destroyTime) {
        destroy();
    }
}

void Bullet::destroy() {
    destroyed = true;
    collisionEnabled = false;
    renderEnabled = false;
}

void Bullet::directionalBullet(Bullet* bullet) {
    //bullet with constant speed in a direction
    //customFloats: speed, x, y
    switch (bullet->customFloats.size()) {
    case 0:
        bullet->customFloats.push_back(20.0f);
    case 1:
        bullet->customFloats.push_back(0.0f);
    case 2:
        bullet->customFloats.push_back(1.0f);
    }
    bullet->dir = glm::vec2(bullet->customFloats[1], bullet->customFloats[2]);
    bullet->move(bullet->customFloats[0] * bullet->dir);
    bullet->setRotation(bullet->dir);
}

void Bullet::homingBullet(Bullet* bullet) {
    //bullet that follows the nearest enemy
    //speed
    if (bullet->customFloats.size() == 0) {
        bullet->customFloats.push_back(20.0f);
    }
    std::shared_ptr<Enemy> enemy = Enemy::findNearestEnemy(bullet->getPos());
    if (!enemy) {
        bullet->move(glm::vec2(0.0f, bullet->customFloats[0]));
    }
    else {
        bullet->dir = glm::normalize(enemy->getPos() - bullet->getPos());
        bullet->move(bullet->customFloats[0] * bullet->dir);
        bullet->setRotation(bullet->dir);
    }
}

//note: make sure that the center is not the same as the current position!
void Bullet::spinningDirectionalBullet(Bullet* b) {
    //centerX, centerY, radiusChange, angleChange, acceleration, spin acceleration
    switch (b->customFloats.size()) {
    case 0:
        b->customFloats.push_back(b->getX());
    case 1:
        b->customFloats.push_back(b->getY());
    case 2:
        b->customFloats.push_back(10.0f);
    case 3:
        b->customFloats.push_back(3.0f);
    case 4:
        b->customFloats.push_back(0.02f);
    case 5:
        b->customFloats.push_back(0.0f);
    }
    glm::vec2 center = glm::vec2(b->customFloats[0], b->customFloats[1]);
    glm::vec2 radius = center - b->getPos();
    float angle = 180 - glm::degrees(glm::orientedAngle(glm::normalize(radius), glm::vec2(1, 0)));

    float incrAngle = angle + b->customFloats[3];
    float incrRadius = glm::length(radius) + b->customFloats[2] * (1 + b->currTime * b->customFloats[4]);
    glm::vec2 radiusEx = glm::vec2(incrRadius * cos(glm::radians(incrAngle)), incrRadius * sin(glm::radians(incrAngle)));
    b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[5]));
}

void Bullet::spinningDirectionalBullet2(Bullet* b) {
    //centerX, centerY, radiusChange, startingAngle, angleChange, acceleration, spin acceleration
    switch (b->customFloats.size()) {
    case 0:
        b->customFloats.push_back(b->getX());
    case 1:
        b->customFloats.push_back(b->getY());
    case 2:
        b->customFloats.push_back(10.0f);
    case 3:
        b->customFloats.push_back(0.0f);
    case 4:
        b->customFloats.push_back(3.0f);
    case 5:
        b->customFloats.push_back(0.02f);
    case 6:
        b->customFloats.push_back(0.0f);
    }
    glm::vec2 center = glm::vec2(b->customFloats[0], b->customFloats[1]);
    glm::vec2 radius = center - b->getPos();

    float incrAngle = b->customFloats[3] + b->customFloats[4] * b->currTime;
    float incrRadius = glm::length(radius) + b->customFloats[2] * (1 + b->currTime * b->customFloats[5]);
    glm::vec2 radiusEx = glm::vec2(incrRadius * cos(glm::radians(incrAngle)), incrRadius * sin(glm::radians(incrAngle)));
    b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[6]));
}