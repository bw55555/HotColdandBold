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

//set direction and speed, no customFloats
void Bullet::directionalBullet(Bullet* bullet) {
    //bullet with constant speed in a direction
    //intentional fallthrough
    bullet->move(bullet->speed * bullet->dir);
    bullet->setRotation(bullet->dir);
}

//set speed, no customFloats
void Bullet::homingBullet(Bullet* bullet) {
    //bullet that follows the nearest enemy
    //speed
    std::shared_ptr<Enemy> enemy = Enemy::findNearestEnemy(bullet->getPos());
    if (!enemy) {
        bullet->move(glm::vec2(0.0f, bullet->speed));
    }
    else {
        bullet->dir = glm::normalize(enemy->getPos() - bullet->getPos());
        bullet->move(bullet->speed * bullet->dir);
        bullet->setRotation(bullet->dir);
    }
}

//note: make sure that the center is not the same as the current position!
//centerX, centerY, radiusChange, angleChange, acceleration, spin acceleration
void Bullet::spinningDirectionalBullet(Bullet* b) {
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
    b->setRotation(glm::normalize(radius + radiusEx));
    b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[5]));
}

//centerX, centerY, radiusChange, startingAngle, angleChange, acceleration, spin acceleration
void Bullet::spinningDirectionalBullet2(Bullet* b) {
    //intentional fallthrough on switch statement
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
    b->setRotation(glm::normalize(radius + radiusEx));
    b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[6]));
}