#include "Level2.h"
#include "LevelMacros.h"
#include "GameWindow.h"
#include "EnemyBuilder.h"
#include "BossEnemy.h"

namespace Level {

    using namespace Movement;
    using namespace BulletMovement;
    void Level2(GLp l) {
        //FairyBuilder* fairy = new FairyBuilder(); // Creates the FairyBuilder
        //DoppleBuilder* dopple = new DoppleBuilder(); // Creates the DoppleBuilder
        //EnemyBuildDirector director; //Creates the director
        //std::cout << "Running Level Update\n";
        L2Part1(l);
        L2Part2(l);
        L2Part3(l);
        wf(l, 120.0f) { GameWindow::Instance->clearScreen(); }
        once(l) {
            std::shared_ptr<Enemy> e = BossEnemy::makeBossEnemy(300.0f, Hitbox::Circle(10), glm::vec2(0.0f, 500.0f), GameWindow::enemyTextures[0], miniboss2UFunc);
        }
        delayClear(l, 30.0f, 10000.0f);
        L2Part4(l);
        L2Part5(l);
        wf(l, 120.0f) { GameWindow::Instance->clearScreen(); }
        once(l) {
            std::shared_ptr<Enemy> e = BossEnemy::makeBossEnemy(400.0f, Hitbox::Circle(10), glm::vec2(0.0f, 500.0f), GameWindow::enemyTextures[0], boss2UFunc);
        }
        delayClear(l, 30.0f, 10000.0f);
        wf(l, 30) {
            GameWindow::Instance->setWin(true);
        }


        /*
        wf(l, 0.5_s) {

            //Esp e = director.buildEnemy(fairy, glm::vec2(0.0f, 500.0f), enemyTestFunc); // Make a fairy at 0, 500
            //e->createBulletSpawner(glm::vec2(0, 0), macroExample);

            Esp e = Enemy::makePresetEnemy(EnemyType::Doppel, glm::vec2(0.0f, 500.0f), [](Ep e) {
                delay(e, 30);
                every(e, 180) e->dir = glm::vec2(randomFloat(-1.0f, 1.0f), 0.0f);
                //fyexo(e, 180, 30, 30) e->move(linearBurst(rt(e, 180) - 30, 8.0f, 0.5f, 30) * e->dir, glm::vec4(-400.0f, 400.0f, 400.0f, 800.0f));
            });

            //e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern2);

            //e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern6);


        }
        wf(l, 1.5_s) {
            //force you to unfocus, must keep player at the bottom of the screen

            Esp e2 = director.buildEnemy(fairy, glm::vec2(0.0f, 100.0f), enemyTestFunc);
            e2->createBulletSpawner(glm::vec2(0, 0), [](BSp s) {
                every(s, 4) s->spawnPreset(BulletType::RoundBlue, s->pos, TargetedBullet{ 10.0f });
            });

        }
        wu(l, 4.0_s) {
            //std::shared_ptr<Enemy> e3 = director.buildEnemy(dopple, glm::vec2(500.0f, 500.0f), enemyTestFunc);
        }
        */
        //delete fairy;
        //delete dopple;
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * --------------
    * Level 1 Part 1
    * --------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void L2Part1(GLp l) {
        during(l, 360) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(850.0f, 900.0f), L2P1EnemyFunc);
                e->createBulletSpawner(L2P1EnemyBSFunc);
            }
        }
        delayClear(l, 360, 900);
        delay(l, 60);
        during(l, 360) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(850.0f, 900.0f), L2P1EnemyFunc2);
                e->createBulletSpawner(L2P1EnemyBSFunc);
            }
        }
        delayMinTrigger(l, Enemy::enemies.size() == 0, 360, 900); // same as delayClear(l, 360, 900)
        delay(l, 60);
    }

    void L2P1EnemyFunc(Ep e) {
        float mT = 600.0f;
        during(e, mT) {
            float cbct = cubic_bezier_time(t(e), mT, 0, .89, 1, .57);
            e->moveTo(followBezierCurve(cbct, glm::vec2(850.0f, 900.0f), glm::vec2(-850.0f, 400.0f), glm::vec2(566.0f, 504.0f)));
        }
        wf(e, mT) {
            e->destroy();
        }
    }

    void L2P1EnemyFunc2(Ep e) {
        float mT = 600.0f;
        during(e, mT) {
            float cbct = cubic_bezier_time(t(e), mT, 0, .89, 1, .57);
            e->moveTo(followBezierCurve(cbct, glm::vec2(-850.0f, 900.0f), glm::vec2(850.0f, 400.0f), glm::vec2(-566.0f, 504.0f)));
        }
        wf(e, mT) {
            e->destroy();
        }
    }

    void L2P1EnemyBSFunc(BSp s) {
        delay(s, 60);
        forever(s) {
            every(s, 60) {
                nspread(o, getAngle(targetPlayer(s->pos)), dchoice(30, 30, 60), dchoice(1, 3, 5)) {
                    nstack(spd, 6.0f, 2.0f, dchoice(1, 2, 3)) {
                        s->spawnPreset(BulletType::DotWhite, DirectionalBullet(avecd(o), spd));
                    }
                }
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * --------------
    * Level 1 Part 2
    * --------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void L2Part2(GLp l) {
        wf(l, 120) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L2P2EnemyFunc);
            }
        }
        during(l, 360) {
            every(l, 30) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(-900.0f, 700.0f), L2P2EnemyFunc2);
                e->createBulletSpawner(L2P2EnemyBSFunc2);
                e->initializeCustomVars(Speed{ 10.0f });
            }
        }
        delayClear(l, 360, 660);
        wf(l, 120) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L2P2EnemyFunc);
            }
        }
        during(l, 360) {
            every(l, 30) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(900.0f, 700.0f), L2P2EnemyFunc2);
                e->createBulletSpawner(L2P2EnemyBSFunc2);
                e->initializeCustomVars(Speed{ -10.0f });
            }
        }
        delayClear(l, 360, 660);
        wf(l, 120) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L2P2EnemyFunc);
            }
        }
        during(l, 360) {
            every(l, 30) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(900.0f, 800.0f), L2P2EnemyFunc2);
                e->createBulletSpawner(L2P2EnemyBSFunc2);
                e->initializeCustomVars(Speed{ -10.0f });
            }
        }
        during(l, 375) {
            everyo(l, 30, 15) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(-900.0f, 700.0f), L2P2EnemyFunc2);
                e->createBulletSpawner(L2P2EnemyBSFunc2);
                e->initializeCustomVars(Speed{ 10.0f });
            }
        }
        delayClear(l, 375, 660);
    }

    void L2P2EnemyFunc(Ep e) {
        during(e, 30) {
            e->move(glm::vec2(0.0f, 1.0f) * linearBurst(t(e), -20.0f, 0.5f, 30));
        } delay(e, 30);
        once(e) { e->createBulletSpawner(L2P2EnemyBSFunc); }
        delay(e, 600);
        during(e, 30) {
            float accel = 0.5f;
            e->move(glm::vec2(0.0f, 1.0f) * std::max(e->getNestedTime() * accel, 20.0f));
        }
        wf(e, 30) { e->destroy(); };

    }

    void L2P2EnemyBSFunc(BSp s) {
        every(s, 120) {
            nstack(spd, dchoice(6, 7, 8), 2.0f, dchoice(3, 4, 6)) {
                s->spawnPreset(BulletType::RoundBlue, DirectionalBullet(glm::vec2(0.0f, -1.0f), spd));
            }
        }
        /*
        everyo(s, 120, 60) {
            nring(o, 16) {
                s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(o), dchoice(5.0f, 6.0f, 8.0f)));
            }
        }
        */
    }

    void L2P2EnemyFunc2(Ep e) {
        forever(e) {
            e->move(glm::vec2(1.0f, 0.0f) * e->speed);
        }
        wfmt(e, !e->isOnScreen(), 60.0f, 1200.0f) {
            e->destroy();
        }
    }

    void L2P2EnemyBSFunc2(BSp s) {
        everyo(s, dchoice(60, 40, 20), 10) {
            nstack(spd, dchoice(8, 9, 10), 2.0f, dchoice(1, 2, 3)) {
                s->spawnPreset(BulletType::KnifeRed, TargetedBullet(spd));
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * --------------
    * Level 1 Part 3
    * --------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void L2Part3(GLp l) {
        once(l) {
            Enemy::makePresetEnemy(EnemyType::StrongFairy, glm::vec2(0.0f, 1100.0f), L2P3EnemyFunc);
        }
        delayClear(l, 30.0f, 960.0f);
        delay(l, 300.0f);
        once(l) {
            Enemy::makePresetEnemy(EnemyType::StrongFairy, glm::vec2(-500.0f, 1100.0f), L2P3EnemyFunc);
            Enemy::makePresetEnemy(EnemyType::StrongFairy, glm::vec2(500.0f, 1100.0f), L2P3EnemyFunc);
        }
        delayClear(l, 30.0f, 960.0f);
        delay(l, 300.0f);

    }

    void L2P3EnemyFunc(Ep e) {
        during(e, 30) {
            e->move(glm::vec2(0.0f, 1.0f) * linearBurst(t(e), -20.0f, 0.5f, 30));
        } delay(e, 30);
        once(e) { e->createBulletSpawner(L2P3EnemyBSFunc); }
        delay(e, 900);
        during(e, 30) {
            float accel = 0.5f;
            e->move(glm::vec2(0.0f, 1.0f) * std::max(e->getNestedTime() * accel, 20.0f));
        }
        wf(e, 30) { e->destroy(); };
    }

    void L2P3EnemyBSFunc(BSp s) {
        every(s, dchoice(7, 5, 5)) {
            nring(o, 2) {
                nstack(spd, 4.0f, 2.0f, dchoice(2, 3, 4)) {
                    s->spawnPreset(BulletType::RoundRed, DirectionalBullet(avecd(-45 + o + 2.03314 * t(s)), spd));
                    s->spawnPreset(BulletType::RoundBlue, DirectionalBullet(avecd(-45 + o + 90 - 2.03314 * t(s)), spd));
                }
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * ------------
    * Level 1 Miniboss2
    * ------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void miniboss2UFunc(Ep e) {
        float destroyTime = 3600.0f;
        if (e->onNextPhase()) {
            wf(e, 90.0f) {
                e->createBulletSpawner(miniboss2Pattern1);
                BSp s1 = e->createBulletSpawner(glm::vec2(0.0f, 100.0f), miniboss2Pattern1Sub);
                s1->initializeCustomVars(static_cast<int>(BulletType::RoundBlue));
                BSp s2 = e->createBulletSpawner(glm::vec2(0.0f, -100.0f), miniboss2Pattern1Sub);
                s2->initializeCustomVars(static_cast<int>(BulletType::RoundRed));
            }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            wf(e, 90.0f) {
                e->createBulletSpawner(miniboss2Pattern2);
            }
            wf(e, destroyTime) { e->destroy(); }
        }
    }

    void miniboss2Pattern1(BSp s) {
        rtfyex(s, rtv, 300, 240) {
            every(s, dchoice(40, 30, 20)) {
                nspread(o, -90.0f, std::abs(106 - dchoice(9.0f, 8.5f, 7.5f) * rtv / 10), 2) {
                    nstack(spd, 6.0f, 2.0f, dchoice(5, 5, 6)) {
                        Bsp b = s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(o), spd));
                    }
                }
            }
        }
    }

    void miniboss2Pattern1Sub(BSp s) {
        s->localPos = s->localPos + rotateAround(s->localPos, glm::vec2(0.0f, 0.0f), 1.0f);
        delay(s, 240);
        forever(s) {
            every(s, dchoice(16, 12, 9)) {
                nring(o, dchoice(8, 8, 12)) {
                    s->spawnPreset(static_cast<BulletType>(static_cast<int>(cf(s, 0))), DirectionalBullet(avecd(o + t(s)), dchoice(6.0f, 8.0f, 10.0f)));
                }
            }
        }
    }

    void miniboss2Pattern2(BSp s) {
        every(s, 300) {
            float rf = randomFloat(0.0f, 45.0f);
            nringi(o, i, 4) {
                BulletType spawnType = BulletType::RoundBlue;
                if (i % 2 == 0) {
                    spawnType = BulletType::RoundBlue;
                }
                else {
                    spawnType = BulletType::RoundRed;
                }
                Bsp b = s->spawnPreset(BulletType::BallBlackBorder, s->pos + avecd(o + 90 * t(s) / 300 + rf), SpinningDirectionalBullet(s->pos, 7.0f, 2.0f, -0.001f, 0.0f));
                BSp s = b->createBulletSpawner(miniboss2Pattern2Sub);
                s->initializeCustomVars(static_cast<int>(spawnType));
            }
        }
    }

    void miniboss2Pattern2Sub(BSp s) {
        delay(s, 20.0f);
        forever(s) {
            every(s, dchoice(20, 16, 12)) {
                nring(o, dchoice(6, 8, 10)) {
                    Bsp b = s->spawnPreset(static_cast<BulletType>(static_cast<int>(cf(s, 0))), DirectionalBullet(avecd(o + t(s)), dchoice(5.0f, 6.0f, 8.0f)));
                }
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * --------------
    * Level 1 Part 4
    * --------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void L2Part4(GLp l) {
        during(l, 1500) {
            every(l, 30) {
                float xpos = (static_cast<int>(nt(l) / 30) % 5) - 2;
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos * 300.0f + randomFloat(-100.0f, 100.0f), 1100.0f), L2P4EnemyFunc);
                e->createBulletSpawner(L2P4EnemyBSFunc);
            }
        }
        when(l, 600) {
            Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(0.0f, 1100.0f), L2P4EnemyFunc2);
        }
        when(l, 1200) {
            Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(-600.0f, 1100.0f), L2P4EnemyFunc2);
            Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(600.0f, 1100.0f), L2P4EnemyFunc2);
        }
        delayClear(l, 1500, 2200);
        delay(l, 180.0f);
    }

    void L2P4EnemyFunc(Ep e) {
        e->move(3.0f * glm::vec2(sin(glm::radians(3.234f * t(e))), -1.0f));
        wfmt(e, !e->isOnScreen(), 60.0f, 10000.0f) { e->destroy(); }
    }

    void L2P4EnemyBSFunc(BSp s) {
        every(s, dchoice(60, 40, 30)) {
            nstack(spd, 5.0f, 2.0f, dchoice(3, 4, 5)) {
                s->spawnPreset(BulletType::RoundBlue, TargetedBullet(spd));
            }
        }
    }

    void L2P4EnemyFunc2(Ep e) {
        constexpr float accel = 0.5f;
        constexpr float maxVel = 20.0f;
        constexpr float moveTime = 30.0f;;
        during(e, moveTime) {
            e->move(glm::vec2(0.0f, 1.0f) * linearBurst(t(e), -1 * maxVel, accel, moveTime));
        } delay(e, moveTime);
        once(e) { e->createBulletSpawner(L2P4EnemyBSFunc2); }
        delay(e, 900);
        during(e, moveTime) {
            e->move(glm::vec2(0.0f, 1.0f) * std::max(e->getNestedTime() * accel, maxVel));
        }
        wf(e, moveTime) { e->destroy(); };
    }

    void L2P4EnemyBSFunc2(BSp s) {
        float o = 0.0f;
        int interval = 15;
        after(s, 180) {
            o += t(s) * 2;
            interval -= floor(std::min(nt(s) / 30, 10.0f));
        }
        every(s, interval) {
            nring(a, 8) {
                s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(a + o), 10.0f));
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * --------------
    * Level 1 Part 5
    * --------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void L2Part5(GLp l) {
        once(l) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L2P2EnemyFunc);
            }
        }
        during(l, 1500) {
            every(l, 90) {
                float xpos = (static_cast<int>(nt(l) / 90) % 5) - 2;
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos * 300.0f + randomFloat(-100.0f, 100.0f), 1100.0f), L2P4EnemyFunc);
                e->createBulletSpawner(L2P5EnemyBSFunc);
            }
        }
        delay(l, 300);
        during(l, 1200) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(900.0f, 800.0f), L2P2EnemyFunc2);
                e->createBulletSpawner(L2P5EnemyBSFunc2);
                e->initializeCustomVars(Speed{ -10.0f });
            }
        }
        during(l, 1230) {
            everyo(l, 60, 30) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(-900.0f, 700.0f), L2P2EnemyFunc2);
                e->createBulletSpawner(L2P5EnemyBSFunc2);
                e->initializeCustomVars(Speed{ 10.0f });
            }
        }
        wf(l, 300) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L2P2EnemyFunc);
            }
        }
        during(l, 360) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(850.0f, 900.0f), L2P1EnemyFunc);
                e->createBulletSpawner(L2P5EnemyBSFunc3);
            }
        }
        during(l, 360) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(-850.0f, 900.0f), L2P1EnemyFunc2);
                e->createBulletSpawner(L2P5EnemyBSFunc3);
            }
        }
        wf(l, 300) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L2P2EnemyFunc);
            }
        }
        delayClear(l, 1200, 2400);
    }
    void L2P5EnemyBSFunc(BSp s) {
        every(s, dchoice(120, 80, 60)) {
            nstack(spd, 5.0f, 2.0f, dchoice(1, 2, 3)) {
                s->spawnPreset(BulletType::RoundBlue, TargetedBullet(spd));
            }
        }
    }
    void L2P5EnemyBSFunc2(BSp s) {
        everyo(s, dchoice(120, 90, 60), 10) {
            nstack(spd, dchoice(6, 7, 8), 2.0f, dchoice(1, 2, 3)) {
                s->spawnPreset(BulletType::KnifeRed, TargetedBullet(spd));
            }
        }
    }
    void L2P5EnemyBSFunc3(BSp s) {
        delay(s, 60);
        forever(s) {
            every(s, dchoice(240, 180, 120)) {
                nspread(o, getAngle(targetPlayer(s->pos)), dchoice(30, 30, 60), dchoice(3, 3, 5)) {
                    nstack(spd, 6.0f, 2.0f, dchoice(1, 2, 3)) {
                        s->spawnPreset(BulletType::DotWhite, DirectionalBullet(avecd(o), spd));
                    }
                }
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * ------------
    * Level 1 Boss
    * ------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void boss2UFunc(Enemy* e) {
        float destroyTime = 3600.0f;
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern7); }
            wf(e, destroyTime) {
                e->destroy();
            }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) {
                e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern6);
            }
            forever(e) {
                every(e, 60) e->dir = randomDir();
                fyexo(e, 60, 30, 30) e->move(linearBurst(rt(e, 180) - 30, 8.0f, 0.5f, 30) * e->dir, glm::vec4(-400.0f, 400.0f, 400.0f, 800.0f));
            }
            wf(e, destroyTime) {
                e->destroy();
            }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern1); }
            forever(e) {
                every(e, 180) e->dir = glm::vec2(randomFloat(-1.0f, 1.0f), 0.0f);
                fyexo(e, 180, 30, 30) e->move(linearBurst(rt(e, 180) - 30, 8.0f, 0.5f, 30) * e->dir, glm::vec4(-400.0f, 400.0f, 400.0f, 800.0f));
            }
            wf(e, destroyTime) {
                e->destroy();
            }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern2); }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern3); }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern4); }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern5); }
            wf(e, destroyTime) { e->destroy(); }
        }
    }

    void boss2Pattern1(BSp s) {
        every(s, 7) {
            nring(o, 4) {
                nspread(a, o, 10, 2)
                    s->spawnPreset(BulletType::KnifeBlue, s->pos, DirectionalBullet{ avecd(a), 10.0f });
            }
        }
        every(s, 5) {
            nring(o, 4) {
                s->spawnPreset(BulletType::RoundBlue, s->pos, DirectionalBullet{ avecd(o + 45 + oscillate(t(s), -40, 40, 0.6)), 10.0f });
                s->spawnPreset(BulletType::RoundBlue, s->pos, DirectionalBullet{ avecd(o - 45 - oscillate(t(s), -40, 40, 0.6)), 10.0f });
                s->spawnPreset(BulletType::RoundRed, s->pos, DirectionalBullet{ avecd(o + 45 + oscillate(t(s), -40, 40, 0.6, -40)), 10.0f });
                s->spawnPreset(BulletType::RoundRed, s->pos, DirectionalBullet{ avecd(o - 45 - oscillate(t(s), -40, 40, 0.6, -40)), 10.0f });
            }
        }
        every(s, 60) {
            nring(o, 16) {
                avec(dir, o + t(s) / 10);
                //s->spawnPreset(BulletType::KnifeBlue, s->pos + dir, SpinningDirectionalBullet(s->pos, 3.0f, 0.5f, 0.02f, 0.0f));
            }
        }
    }

    void boss2Pattern2(BSp s) {
        int spawnInterval = 90; //probably too hard
        spawnInterval = 120; //this is a lot easier...
        fyex(s, spawnInterval, 18) { //executes 18 frames in a row every spawnInterval frames
            every(s, 2) { //every 2 frames
                nring(o, 6) { //6 bullets in a ring
                    nstacki(spd, i, 4, 2, 5) { //5 bullets in a stack with varying speed
                        BulletType bt = rt(s, spawnInterval * 2) < spawnInterval ? BulletType::KnifeBlue : BulletType::KnifeRed; //alternate bullet type
                        Bsp b = s->spawnPresetwLambda(bt, s->pos + avecd(1.2f * o + 3.7385f * t(s) + 26.0f * i + randomFloat(0.0f, 2.0f)), [](Bp b) { //choose a starting direction
                            //the time system I created is pretty complicated... but basically you should put everything in a time block like this
                            during(b, 29) {
                                spinningDirectionalBullet(b); //creates that spinning effect at the beginning
                            }
                            wf(b, 60) { //do this at 60 frames (wf stands for waitfor)
                                b->rotateDir(90 * b->customFloats[6]); //rotate the bullets and shoot them out, but slower
                                b->speed *= 0.8f;
                            }
                            forever(b) { //do this forever after 60 frames
                                directionalBullet(b);
                            }
                            });
                        b->initializeCustomVars(s->pos, spd, 3.0f, 0.0f, 0.0f, (int)(t(s) / 120)); //intialize the values for spinningDirectionalBullet
                    }
                }
            }
        }
    }

    void boss2Pattern3(BSp s) {
        every(s, 60) {
            nspread(o, getAngle(targetPlayer(s->pos)), 40, 2) {
                Bsp b = s->spawnPreset(BulletType::BallBlackBorder, s->pos, DirectionalBullet(avecd(o), 5.0f));
                b->createBulletSpawner(glm::vec2(0, 0), [](BSp s2) {
                    every(s2, 1) if (s2->getParent<Bullet>()->touchingWall(WallDirection::Any)) {
                        nspread(o, 90, 20, 4) {
                            nstack(spd, 4.0f, 3.0f, 4) {
                                //s2->spawnPreset(BulletType::KnifeBlue, s2->pos, DirectionalBullet(avecd(a), 10.0f));
                                Bsp b = s2->spawnPresetwLambda(BulletType::RoundBlue, s2->pos, [](Bp b) {
                                    glm::vec2 accel = glm::vec2(cf(b, 0), cf(b, 1));
                                    b->setVelocity(b->getVelocity() + accel);
                                    b->move();
                                    });
                                b->initializeCustomVars(Direction(avecd(o)), Speed(spd), glm::vec2(0, -0.1f));
                            }
                        }
                        s2->getParent<Bullet>()->destroy();
                    }
                    });
            }
        }
        every(s, 180) {
            nspread(a, getAngle(targetPlayer(s->pos)), 4, 3) {
                nstack(spd, 9.0f, 0.5f, 3) {
                    s->spawnPreset(BulletType::KnifeBlue, s->pos, DirectionalBullet(avecd(a), spd));
                }
            }
        }
    }

    void boss2Pattern4(BSp s) {
        every(s, 40) {
            float rf = randomFloat(0.0f, 15.0f);
            rf = 0;
            nring(a, 12) {
                nstack(spd, 5, 0.3, 7) {
                    s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(rf + a + 15 * t(s) / 40), spd));
                }
            }
        }
        every(s, 60) {
            s->dir = targetPlayer(s->pos);
        }
        fyex(s, 60, 18) {
            every(s, 3) {
                float a = rt(s, 60) + 1;
                nspread(o, getAngle(s->dir), a, 2) {
                    s->spawnPreset(BulletType::KnifeRed, DirectionalBullet(avecd(o), 10.0f));
                }
            }
        }
    }

    void boss2Pattern5(BSp s) {
        int spawnTimeA = 4;
        every(s, spawnTimeA) {
            nring(a, 6) {
                float angle = a + linearAcceleration(t(s) / spawnTimeA, 0.5f, 10.31274f, 30.0f, true);
                s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(angle), 8.0f));
            }
        }
        every(s, spawnTimeA) {
            nring(a, 6) {
                float angle = a - linearAcceleration(t(s) / spawnTimeA, 0.5f, 10.31274f, 30.0f, true);
                s->spawnPreset(BulletType::KnifeRed, DirectionalBullet(avecd(angle), 8.0f));
            }
        }
        /*
        every(s, 10) {
            nring(a, 16) {
                float wave = oscillate(t(s) / 10, -15, 15, 3);
                s->spawnPreset(BulletType::RoundBlue, DirectionalBullet(avecd(a + wave), 10.0f));
            }
        }
        every(s, 10) {
            nring(a, 16) {
                float wave = oscillate(t(s) / 10, -15, 15, 3);
                s->spawnPreset(BulletType::RoundRed, DirectionalBullet(avecd(a - wave), 10.0f));
            }
        }
        */

    }

    void boss2Pattern6(BSp s) {
        float sI = dchoice(60.0f, 40.0f, 20.0f);
        float finalSpeed = dchoice(6.0f, 8.0f, 10.0f);
        float numBullets = dchoice(20, 30, 40);
        float waveChange = dchoice(1.0f, 0.66666666f, 0.5f);
        float initialSpeed = dchoice(4.0f, 7.0f, 7.0f);
        every(s, sI) {
            nringi(a, i, numBullets) {
                float wave = initialSpeed * oscillate(i + 1, -1, 1, waveChange, 0);
                s->spawnPreset(BulletType::KnifeBlue, SwitchDirectionalBullet(avecd(a + 2.34653 * t(s) / sI * 1.03321), 1.0f + 2.0f * initialSpeed + wave, 15.0f, finalSpeed + randomFloat(0.0f, 1.0f)));
            }
        }
        everyo(s, sI, sI / 2) {
            nringi(a, i, numBullets) {
                float wave = initialSpeed * oscillate(i + 1, -1, 1, waveChange, 0);
                s->spawnPreset(BulletType::KnifeRed, SwitchDirectionalBullet(avecd(a - 2.34653 * t(s) / sI + 360 / 5 / 2), 1.0f + 2.0f * initialSpeed + wave, 15.0f, finalSpeed + randomFloat(0.0f, 1.0f)));
            }
        }
    }

    //spawns stars and throws them at you!
    void boss2Pattern7(BSp s) {
        every(s, 40.0f) {
            float ringMoveSpeed = dchoice(10.0f, 15.0f, 20.0f);
            float ro = randomFloat(0.0f, 360.0f);
            nring(o, 32) {
                s->spawnPreset(BulletType::KnifeBlue, s->pos, DirectionalBullet(avecd(o + ro), ringMoveSpeed));
            }
        }
        float starspawnInt = dchoice(180.0f, 150.0f, 120.0f);
        every(s, starspawnInt) {
            nring(o, 5) {
                glm::vec2 dir = targetPlayer(s->pos);
                float numBullets = 8.0f;
                float radius = dchoice(350.0f, 400.0f, 450.0f);
                float height = cos(glm::radians(72.0f)) * radius;

                float angle = glm::degrees(acos(height / radius));
                glm::vec2 firstPos = s->pos + radius * avecd(o + 90 + angle);
                glm::vec2 secondPos = s->pos + radius * avecd(o + 90 - angle);
                glm::vec2 diff = (secondPos - firstPos) / (numBullets);
                nrep(i, numBullets) {
                    glm::vec2 dest = firstPos + i * diff;
                    Bsp b = s->spawnPresetwLambda(BulletType::RoundBlue, s->pos, [](Bp b) {
                        motw(b, glm::vec2(cf(b, 0), cf(b, 1)), 30);
                        forever(b) {
                            b->move(b->dir * b->speed);
                            glm::vec2 centerDest = glm::vec2(cf(b, 2), cf(b, 3)) + b->dir * b->speed;
                            cf(b, 2) = centerDest.x;
                            cf(b, 3) = centerDest.y;
                            b->rotateAround(centerDest, 2);
                            float x = oscillate(b->currTime - 30, -1, 1, 0.02);
                            float sign = static_cast<float>((x > 0) - (x < 0));
                            //b->move(glm::normalize(centerDest - b->getPos()) * sign * 1.0f);
                        }
                        });
                    b->initializeCustomVars(dest, s->pos, Direction{ dir }, Speed{ 10.0f });
                }
            }
        }
    }
}