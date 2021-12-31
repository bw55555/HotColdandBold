#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "BulletMovement.h"
#include "CollidableObject.h"
#include "UpdateTime.h"

class BulletSpawner;

struct DestroyFlags {
    bool offScreen = true;
    float destroyTime = -1;
};

class Bullet :
    public CollidableObject, public UpdateTime<Bullet>, public std::enable_shared_from_this<Bullet>
{
public:
    static std::vector<std::shared_ptr<Bullet>> bullets;
    static std::shared_ptr<Bullet> makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling = glm::vec3(50.0f));

    bool firedByPlayer = false;
    bool destroyed = false;
    Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling = glm::vec3(50.0f));
    void update();
    void destroy();
    bool checkDestruction();
    DestroyFlags destroyFlags;

    std::vector<std::unique_ptr<BulletSpawner>> spawners;
    void createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*));
};

