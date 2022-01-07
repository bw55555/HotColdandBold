#pragma once
#include "GameLevel.h"
#include "Movement.h"

namespace Level {

    void bossUFunc(Enemy* e);

    void bs1(BulletSpawner* spawner);
    void bs2(BulletSpawner* spawner);
    void bs_1(BulletSpawner* spawner);
    
    void bossPattern1(BSp s);
    void bossPattern2(BSp s);
    void bossPattern3(BSp s);
    void bossPattern4(BSp s);
    void bossPattern5(BSp s);
    void bossPattern6(BSp s);
    void bossPattern7Fail(BSp s);
    void bossPattern7(BSp s);

    void macroExample(BSp s);
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