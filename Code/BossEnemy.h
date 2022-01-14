#pragma once

#include "Enemy.h"
class BossEnemy :
    public Enemy
{
public:
    static std::shared_ptr<Enemy> makeBossEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));

    BossEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    ~BossEnemy();

    static std::unique_ptr<Sprite> bossHealthBar;
    void createBossHealthBar();

    float maxHealth = 0.0f;

    int numPhases = 1;
    int currPhase = 1;
    int countedPhases = 0;
    void startNextPhase();
    int countPhases();
    bool onNextPhase();

    void destroy();
    void update();
    void draw() override;

    void setMaxHealth(float _maxHealth);
};

