#include "BulletMovement.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CollidableObject.h"
#include "GameWindow.h"

using namespace Movement;

//set direction and speed, no customFloats
void BulletMovement::directionalBullet(Bullet* bullet) {
    //bullet with constant speed in a direction
    //intentional fallthrough
    bullet->move(bullet->speed * bullet->dir);
    bullet->setRotation(bullet->dir);
}

//set speed, no customFloats
void BulletMovement::homingBullet(Bullet* bullet) {
    //bullet that follows the nearest enemy
    //speed
    std::shared_ptr<Enemy> enemy = Enemy::findNearestEnemy(bullet->getPos());
    if (!enemy) {
        bullet->move(glm::vec2(0.0f, bullet->speed));
    }
    else {
        bullet->dir = normalizeSafe(enemy->getPos() - bullet->getPos());
        bullet->move(bullet->speed * bullet->dir);
        bullet->setRotation(bullet->dir);
    }
}

//note: make sure that the center is not the same as the current position!
//centerX, centerY, radiusChange, angleChange, acceleration, spin acceleration
void BulletMovement::spinningDirectionalBullet(Bullet* b) {
    
    switch (b->customFloats.size()) {
    case 0:
        b->customFloats.push_back(b->getX());
        [[fallthrough]];
    case 1:
        b->customFloats.push_back(b->getY());
        [[fallthrough]];
    case 2:
        b->customFloats.push_back(10.0f);
        [[fallthrough]];
    case 3:
        b->customFloats.push_back(3.0f);
        [[fallthrough]];
    case 4:
        b->customFloats.push_back(0.02f);
        [[fallthrough]];
    case 5:
        b->customFloats.push_back(0.0f);
    }
    glm::vec2 center = glm::vec2(b->customFloats[0], b->customFloats[1]);
    glm::vec2 radius = center - b->getPos();
    float angle = isZeroVec(radius) ? 0 : 180 - glm::degrees(glm::orientedAngle(glm::normalize(radius), glm::vec2(1, 0)));

    float incrAngle = angle + b->customFloats[3];
    float incrRadius = glm::length(radius) + b->customFloats[2] * (1 + b->currTime * b->customFloats[4]);
    glm::vec2 radiusEx = glm::vec2(incrRadius * cos(glm::radians(incrAngle)), incrRadius * sin(glm::radians(incrAngle)));
    
    b->setRotation(normalizeSafe(radius + radiusEx));
    b->dir = normalizeSafe(radius + radiusEx);
    b->speed = glm::length(radius + radiusEx);
    b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[5]));
}

//centerX, centerY, radiusChange, startingAngle, angleChange, acceleration, spin acceleration
void BulletMovement::spinningDirectionalBullet2(Bullet* b) {
    //intentional fallthrough on switch statement
    switch (b->customFloats.size()) {
    case 0:
        b->customFloats.push_back(b->getX());
        [[fallthrough]];
    case 1:
        b->customFloats.push_back(b->getY());
        [[fallthrough]];
    case 2:
        b->customFloats.push_back(10.0f);
        [[fallthrough]];
    case 3:
        b->customFloats.push_back(0.0f);
        [[fallthrough]];
    case 4:
        b->customFloats.push_back(3.0f);
        [[fallthrough]];
    case 5:
        b->customFloats.push_back(0.02f);
        [[fallthrough]];
    case 6:
        b->customFloats.push_back(0.0f);
    }
    glm::vec2 center = glm::vec2(b->customFloats[0], b->customFloats[1]);
    glm::vec2 radius = center - b->getPos();

    float incrAngle = b->customFloats[3] + b->customFloats[4] * b->currTime;
    float incrRadius = glm::length(radius) + b->customFloats[2] * (1 + b->currTime * b->customFloats[5]);
    glm::vec2 radiusEx = glm::vec2(incrRadius * cos(glm::radians(incrAngle)), incrRadius * sin(glm::radians(incrAngle)));
    b->setRotation(normalizeSafe(radius + radiusEx));
    b->dir = normalizeSafe(radius + radiusEx);
    b->speed = glm::length(radius + radiusEx);
    b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[6]));
}

void BulletMovement::switchDirectionalBullet(Bullet* b) {
    if (b->wait(b->customFloats[0])) {
        b->dir = glm::vec2(b->customFloats[1], b->customFloats[2]);
        b->speed = b->customFloats[3];
    }
    BulletMovement::directionalBullet(b);
}

void BulletMovement::DirectionalBullet::init(std::shared_ptr<Bullet> b) {
    b->initializeCustomVars(Speed{ spd }, Direction{ dir });
}

void BulletMovement::SpinningDirectionalBullet::init(std::shared_ptr<Bullet> b) {
    b->initializeCustomVars(center.x, center.y, radiusChange, angleChange, acceleration, spinAcceleration);
}

glm::vec2 BulletMovement::targetPlayer(glm::vec2 initialPos, glm::vec2 playerOffset) {
    return normalizeSafe(GameWindow::player->getPos() + playerOffset - initialPos);
}

glm::vec2 BulletMovement::targetPlayer(Bullet* b, glm::vec2 playerOffset) {
    return normalizeSafe(GameWindow::player->getPos() + playerOffset - b->getPos());
}

void BulletMovement::TargetedBullet::init(std::shared_ptr<Bullet> b) {
    glm::vec2 dir = BulletMovement::targetPlayer(b.get());
    b->initializeCustomVars(Speed{ spd }, Direction{dir});
}

void BulletMovement::SwitchDirectionalBullet::init(std::shared_ptr<Bullet> b) {
    glm::vec2 dir = BulletMovement::targetPlayer(b.get());
    b->initializeCustomVars(Speed{ s1 }, Direction{ d1 }, time, d2, s2);
}