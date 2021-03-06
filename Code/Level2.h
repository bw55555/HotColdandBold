#pragma once
#include "GameLevel.h"
#include "Movement.h"

namespace Level {

    void Level2(GLp l);

    void L2Part1(GLp l);
    void L2P1EnemyFunc(Ep e);
    void L2P1EnemyBSFunc(BSp b);

    void miniboss2UFunc(Ep e);
    void miniboss2Pattern1(BSp s);
    void miniboss2Pattern1BFunc(Bp b);
    void miniboss2Pattern1Sub(BSp s);
    void miniboss2Pattern2(BSp s);
    void miniboss2Pattern2BFunc(Bp b);

    void boss2UFunc(Enemy* e);
    void boss2Pattern1MinionFunc(Enemy* e);
    void boss2Pattern1MinionBSFunc(BSp s);
    void boss2Pattern1(BSp s);
    void boss2Pattern2(BSp s);
    void boss2Pattern3(BSp s);
    void boss2Pattern3BFunc(Bp b);
    void boss2Pattern5(BSp s);
    void boss2Pattern6(BSp s);
    void boss2Pattern7(BSp s);

}