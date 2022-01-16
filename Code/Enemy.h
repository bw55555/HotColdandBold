#pragma once

#include <memory>
#include "BulletSpawner.h"

#include "CollidableObject.h"
#include "UpdateTime.h"
#include "DropItem.h"

inline void doNothingFunc(Enemy* e) {}

enum class EnemyType { WeakFairy, Fairy, Doppel };

class Enemy :
    public CollidableObject, public UpdateTime<Enemy>, public std::enable_shared_from_this<Enemy>
{
public:
    static std::vector<std::shared_ptr<Enemy>> enemies;
    static std::shared_ptr<Enemy> makeEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    static std::shared_ptr<Enemy> findNearestEnemy(glm::vec2 pos);
    static std::shared_ptr<Enemy> makePresetEnemy(EnemyType type, glm::vec2 initialPos, void (*func)(Enemy*));
    
    float health;
    float invTimer;
    bool destroyed = false;

    std::vector<std::unique_ptr<BulletSpawner>> spawners;
    Enemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    virtual void update();
    virtual void destroy();
    virtual void takeDamage(float damage = 1.0f);
    ~Enemy();
    void createBulletSpawner(glm::vec2 initialPos, void (*func)(BulletSpawner*));
    void createBulletSpawner(void (*func)(BulletSpawner*)) { return createBulletSpawner(glm::vec2(0, 0), func); }

    virtual void startNextPhase() {};
    virtual bool onNextPhase() { return false; };

    typedef void (*DestroyFunc)(Enemy*);

    DestroyFunc dfunc = doNothingFunc;
    void setDFunc(DestroyFunc d) { dfunc = d; }
    static DestroyFunc spawnDropOnDeath(DropItemType d);
};

