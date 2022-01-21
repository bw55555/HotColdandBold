#pragma once
#include "GameLevel.h"
#include "Movement.h"

namespace Level {

    void Level2(GLp l);

    void L2Part1(GLp l);
    void L2P1EnemyFunc(Ep e);
    void L2P1EnemyFunc2(Ep e);
    void L2P1EnemyBSFunc(BSp b);

    void L2Part2(GLp l);
    void L2P2EnemyFunc(Ep e);
    void L2P2EnemyBSFunc(BSp s);
    void L2P2EnemyFunc2(Ep e);
    void L2P2EnemyBSFunc2(BSp s);

    void L2Part3(GLp l);
    void L2P3EnemyFunc(Ep e);
    void L2P3EnemyBSFunc(BSp s);

    void miniboss2UFunc(Ep e);
    void miniboss2Pattern1(BSp s);
    void miniboss2Pattern1Sub(BSp s);
    void miniboss2Pattern2(BSp s);
    void miniboss2Pattern2Sub(BSp s);

    void L2Part4(GLp l);
    void L2P4EnemyFunc(Ep e);
    void L2P4EnemyBSFunc(BSp s);
    void L2P4EnemyFunc2(Ep e);
    void L2P4EnemyBSFunc2(BSp s);

    void L2Part5(GLp l);
    void L2P5EnemyBSFunc(BSp s);
    void L2P5EnemyBSFunc2(BSp s);
    void L2P5EnemyBSFunc3(BSp s);

    void boss2UFunc(Enemy* e);
    void boss2Pattern1(BSp s);
    void boss2Pattern2(BSp s);
    void boss2Pattern3(BSp s);
    void boss2Pattern4(BSp s);
    void boss2Pattern5(BSp s);
    void boss2Pattern6(BSp s);
    void boss2Pattern7(BSp s);

}