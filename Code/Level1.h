#pragma once
#include "GameLevel.h"

/*
class Level1 :
    public GameLevel
{
};
*/

namespace Level {
    void bs1(BulletSpawner* spawner);
    void bs2(BulletSpawner* spawner);
    void bs_1(BulletSpawner* spawner);
    void stackingTest(BulletSpawner* s);

    void enemyTestFunc(Enemy* enemy);
    void bulletSpawnerTestFunc(BulletSpawner* spawner);
    void Level1(GameLevel* level);

    void bulletSpawnerTestFunc2(BulletSpawner* spawner);
    void testFunc2(Bullet* b);

    void bulletSpawnerTestFuncDisplay(BulletSpawner* spawner);
    void spinningDirectionalBulletDisplay(Bullet* b);

    void bulletSpawnerTestSpinning(BulletSpawner* spawner);
    void spinningDirectionalBullet(Bullet* b);

    void bulletSpawnerTest3(BulletSpawner* spawner);
    void testFunc3(Bullet* b);

    void bulletSpawnerTest4(BulletSpawner* spawner);
    void testFunc4(Bullet* b);
}