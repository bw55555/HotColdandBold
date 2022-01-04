#pragma once
#include "GameLevel.h"
#include "Movement.h"

namespace Level {

    void bs1(BulletSpawner* spawner);
    void bs2(BulletSpawner* spawner);
    void bs_1(BulletSpawner* spawner);
    
    void bossPattern1(BulletSpawner* s);
    void bossPattern2(BulletSpawner* s);
    void bossPattern3(BulletSpawner* s);
    void bossPattern4(BulletSpawner* s);
    void bossPattern5(BulletSpawner* s);

    void macroExample(BulletSpawner* s);
    void enemyTestFunc(Enemy* enemy);
    void bulletSpawnerTestFunc(BulletSpawner* spawner);
    void Level1(GameLevel* level);

    void bulletSpawnerTestFunc2(BulletSpawner* spawner);
    void testFunc2(Bullet* b);

    void bulletSpawnerTestFuncDisplay(BulletSpawner* spawner);
    void spinningDirectionalBulletDisplay(Bullet* b);

    void bulletSpawnerTestSpinning(BulletSpawner* spawner);

    void bulletSpawnerTest3(BulletSpawner* spawner);
    void testFunc3(Bullet* b);

    void bulletSpawnerTest4(BulletSpawner* spawner);
    void testFunc4(Bullet* b);
}