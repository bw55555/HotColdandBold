#pragma once

#include "Enemy.h"

class Text;

class BossEnemy :
    public Enemy
{
public:
    static std::shared_ptr<Enemy> makeBossEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));

    BossEnemy(float _health, Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    ~BossEnemy();

    static std::unique_ptr<Sprite> bossHealthBar;
    static std::unique_ptr<Text> bossTimerSprite;
    void createBossHealthBar();

    float maxHealth = 0.0f;

    float maxBossTimer = 3600.0f;
    float bossTimer;

    int numPhases = 1;
    int currPhase = 1;
    int countedPhases = 0;
    void startNextPhase();
    int countPhases();
    bool onNextPhase();

    void destroy(DestroyReason reason = DestroyReason::Timeout);
    void update();
    void draw() override;

    void setMaxHealth(float _maxHealth);

    float getBossTimer() override { return maxBossTimer - bossTimer; };

};

