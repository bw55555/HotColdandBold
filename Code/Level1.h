#pragma once
#include "GameLevel.h"
#include "Movement.h"

namespace Level {

    

    void Level1(GLp l);
    
    void L1Part1(GLp l);
    void L1P1EnemyFunc(Ep e);
    void L1P1EnemyFunc2(Ep e);
    void L1P1EnemyBSFunc(BSp b);

    void L1Part2(GLp l);
    void L1P2EnemyFunc(Ep e);
    void L1P2EnemyBSFunc(BSp s);

    void bossUFunc(Enemy* e);
    void bossPattern1(BSp s);
    void bossPattern2(BSp s);
    void bossPattern3(BSp s);
    void bossPattern4(BSp s);
    void bossPattern5(BSp s);
    void bossPattern6(BSp s);
    void bossPattern7Fail(BSp s);
    void bossPattern7(BSp s);

    void macroExample(BSp s);
    

    void bs1(BulletSpawner* spawner);
    void bs2(BulletSpawner* spawner);
    void bs_1(BulletSpawner* spawner);

    void enemyTestFunc(Enemy* enemy);
    void bulletSpawnerTestFunc(BulletSpawner* spawner);
    

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