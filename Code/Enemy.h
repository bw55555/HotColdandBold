#pragma once

#include <memory>
#include "BulletSpawner.h"

#include "CollidableObject.h"
#include "UpdateTime.h"

class Enemy :
    public CollidableObject, public UpdateTime<Enemy>, public std::enable_shared_from_this<Enemy>
{
public:
    static std::vector<std::shared_ptr<Enemy>> enemies;
    static std::shared_ptr<Enemy> makeEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    static std::shared_ptr<Enemy> findNearestEnemy(glm::vec2 pos);
    float health;
    float invTimer;
    bool destroyed = false;

    std::vector<std::unique_ptr<BulletSpawner>> spawners;
    Enemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    virtual void update();
    virtual void destroy();
    ~Enemy();
    void createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*));
    void createBulletSpawner(void (*func)(BulletSpawner*)) { return createBulletSpawner(glm::vec2(0, 0), func); }

    virtual void startNextPhase() {};
    virtual bool onNextPhase() { return false; };
};

