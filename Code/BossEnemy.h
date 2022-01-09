#pragma once

#include "Enemy.h"
class BossEnemy :
    public Enemy
{
public:
    static std::shared_ptr<Enemy> makeBossEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));

    BossEnemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*), glm::vec3 scaling = glm::vec3(100.0f));
    ~BossEnemy();

    std::unique_ptr<Sprite> bossHealthBar;
    void createBossHealthBar();

    int numPhases = 1;
    int currPhase = 1;
    int countedPhases = 0;
    void startNextPhase();
    int countPhases();
    bool onNextPhase();

    void destroy();
    void update();
    
};

