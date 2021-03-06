#include "Level2.h"
#include "LevelMacros.h"
#include "GameWindow.h"
#include "EnemyBuilder.h"
#include "BossEnemy.h"

namespace Level {

    using namespace Movement;
    using namespace BulletMovement;
    void Level2(GLp l) {
        
        L2Part1(l);
        
        wf(l, 120.0f) { GameWindow::Instance->clearScreen(); }
        once(l) {
            std::shared_ptr<Enemy> e = BossEnemy::makeBossEnemy(300.0f, Hitbox::Circle(200.0f), glm::vec2(0.0f, 500.0f), GameWindow::enemyTextures[8], miniboss2UFunc, glm::vec3(400.0f));
        }
        delayClear(l, 30.0f, 30.0f + 60.0f * 60 * 2);
        delay(l, 180.0f);
        
        wf(l, 120.0f) { GameWindow::Instance->clearScreen(); }
        
        once(l) {
            std::shared_ptr<Enemy> e = BossEnemy::makeBossEnemy(400.0f, Hitbox::Circle(200.0f), glm::vec2(0.0f, 500.0f), GameWindow::enemyTextures[9], boss2UFunc, glm::vec3(400.0f));
        }
        delayClear(l, 30.0f, 300.0f + 60.0f * 60 * 6);
        
        wf(l, 300) {
            GameWindow::Instance->setWin(true);
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * --------------
    * Level 2 Part 1
    * --------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void L2Part1(GLp l) {
        during(l, 1200) {
            every(l, 60) {
                float x = 2 * ((randomFloat(-1, 1) > 0) - 0.5f);
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(x * randomFloat(300, 700), 1100.0f), L2P1EnemyFunc);
                e->initializeCustomVars(glm::vec2(-x, randomFloat(-0.5f, -0.2f)));
                e->createBulletSpawner(L2P1EnemyBSFunc);
            }
        }
        delay(l, 600);
        during(l, 600) {
            every(l, dchoice(60, 70, 80)) {
                float x = 2 * ((randomFloat(-1, 1) > 0) - 0.5f);
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(x * randomFloat(300, 700), 1100.0f), L2P1EnemyFunc);
                e->initializeCustomVars(glm::vec2(-x, randomFloat(-0.5f, -0.2f)));
                e->createBulletSpawner(L2P1EnemyBSFunc);
            }
        }
        delay(l, 300);
        during(l, 300) {
            every(l, dchoice(60, 90, 120)) {
                float x = 2 * ((randomFloat(-1, 1) > 0) - 0.5f);
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(x * randomFloat(300, 700), 1100.0f), L2P1EnemyFunc);
                e->initializeCustomVars(glm::vec2(-x, randomFloat(-0.5f, -0.2f)));
                e->createBulletSpawner(L2P1EnemyBSFunc);
            }
        }
        delayClear(l, 300, 1800);
    }

    void L2P1EnemyFunc(Ep e) {
        during(e, 30) {
            e->move(glm::vec2(0.0f, 1.0f) * linearBurst(t(e), -20.0f, 0.5f, 30));
        } delay(e, 30);
        once(e) { e->createBulletSpawner(L2P1EnemyBSFunc); }
        delay(e, 120);
        forever(e) {
            e->move(glm::vec2(cf(e, 0), cf(e, 1)) * std::max(e->getNestedTime() * 0.05f, 20.0f));
        }
        wft(e, !e->isOnScreen(), 600.0f) { e->destroy(); };
    }

    void L2P1EnemyBSFunc(BSp s) {
        every(s, 60) {
            nstack(spd, 8.0f, 2.0f, dchoice(2, 3, 3)) {
                float rf = randomFloat(0, 360);
                nring(o, dchoice(8, 8, 12)) {
                    s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet{ avecd(rf + o), spd });
                }
            }
        }
    }

    /*
    * -----------------------------------------------------------------------------------------------------------------
    * ------------
    * Level 2 Miniboss
    * ------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void miniboss2UFunc(Ep e) {
        
        if (e->onNextPhase()) {
            wf(e, 90.0f) {
                e->createBulletSpawner(miniboss2Pattern1);
            }
        }
        
        if (e->onNextPhase()) {
            wf(e, 90.0f) {
                e->createBulletSpawner(miniboss2Pattern2);
            }
        }
    }

    void miniboss2Pattern1(BSp s) {
        forever(s) {
            every(s, dchoice(240, 240, 120)) {
                Bsp b = s->spawnPreset(BulletType::BallBlackBorder, miniboss2Pattern1BFunc);
                b->initializeCustomVars(Speed{ dchoice(6.0f, 8.0f, 10.0f) });
                b->createBulletSpawner(miniboss2Pattern1Sub);
            }
        }
    }

    void miniboss2Pattern1BFunc(Bp b) {
        float maxAngleTurn = dchoice(1.0f, 2.0f, 4.0f);
        every(b, 120) {
            b->dir = targetPlayer(b);
        }
        fyex(b, 120, 90) {
            float anglediff = getAngle(targetPlayer(b)) - getAngle(b->dir);
            if (anglediff > 180) { anglediff -= 360; }
            if (anglediff < -180) { anglediff += 360; }
            b->rotateDir(std::clamp(anglediff, -maxAngleTurn, maxAngleTurn));
            b->move(b->dir * b->speed);
        }
    }

    void miniboss2Pattern1Sub(BSp s) {
        forever(s) {
            everyo(s, 120, 105) {
                nring(o, dchoice(6, 8, 12)) {
                    s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(o + t(s)), dchoice(6.0f, 8.0f, 10.0f)));
                }
            }
        }
    }

    void miniboss2Pattern2(BSp s) {
        rtfyex(s, rtx, dchoice(390, 330, 270), dchoice(40, 50, 60)) {
            every(s, 2) {
                nringi(o, i, 8) {
                    nstacki(spd, j, dchoice(6.0f, 6.0f, 8.0f), dchoice(2.0f, 4.0f, 2.0f), dchoice(1, 2, 3)) {
                        Bsp b = s->spawnPreset(BulletType::RoundRed, miniboss2Pattern2BFunc);
                        glm::vec2 bdir = avecd(o + t(s) * 7);
                        b->initializeCustomVars(Direction{ bdir }, Speed{ 7.0f - 3.0f * bdir.y }, 170 - rtx, spd);
                    }
                }
            }
        }
    }

    void miniboss2Pattern2BFunc(Bp b) {
        during(b, cf(b, 0)) {
            directionalBullet(b);
        }
        delay(b, cf(b, 0));
        once(b) {
            b->dir = targetPlayer(b);
            b->speed = cf(b, 1);
            b->texture = BulletSpawner::bulletPresetTextures[1];
            b->setRotation(b->dir);
        }
        after(b, 60) {
            directionalBullet(b);
        }
    }

    
    /*
    * -----------------------------------------------------------------------------------------------------------------
    * ------------
    * Level 2 Boss
    * ------------
    * -----------------------------------------------------------------------------------------------------------------
    */

    void boss2UFunc(Enemy* e) {
        
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern1); }
            forever(e) {
                every(e, 60) {
                    Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(randomSign() * randomFloat(200.0f, 700.0f), randomFloat(-100.0f, 100.0f)), boss2Pattern1MinionFunc);
                }
            }
        }
        
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern2); }
        }
        
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern3); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern5); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) { e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern7); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            wf(e, 60.0f) {
                e->createBulletSpawner(glm::vec2(0, 0), boss2Pattern6);
            }
            forever(e) {
                every(e, 60) e->dir = randomDir();
                rtfyexo(e, rtx, 60, 30, 30) e->move(linearBurst(rtx - 30, 8.0f, 0.5f, 30) * e->dir, glm::vec4(-400.0f, 400.0f, 400.0f, 800.0f));
            }
        }
        
    }

    void boss2Pattern1MinionFunc(Enemy* e) {
        once(e) { e->createBulletSpawner(boss2Pattern1MinionBSFunc); };
        delay(e, 300.0f);
        during(e, 60) {
            e->color.w -= 1.0f / 60.0f;
        }
        wf(e, 60) {
            e->destroy();
        }
    }

    void boss2Pattern1MinionBSFunc(BSp s) {
        every(s, 20) {
            s->spawnPreset(BulletType::KnifeRed, DirectionalBullet(targetPlayer(s->pos, 100.0f * randomDir()), 8.0f));
        }
    }

    void boss2Pattern1(BSp s) {
        every(s, dchoice(40, 30, 20)) {
            float rf = randomFloat(0.0f, 360.0f);
            nring(o, dchoice(4, 6, 8)) {
                nspread(a, o + rf, 15, 2)
                    nstack(spd, 8.0f, 2.0f, 2)
                        s->spawnPreset(BulletType::KnifeBlue, s->pos, DirectionalBullet{ avecd(a), spd });
            }
        }
        
    }

    void boss2Pattern2(BSp s) {
        every(s, dchoice(80, 60, 40)) {
            nring(o, dchoice(8, 12, 16)) {
                Bsp b = s->spawnPreset(BulletType::KnifeRed, s->pos + glm::vec2(avecd(o + t(s)/20)), SpinningDirectionalBullet(s->pos, 8.0f, 2.0f, dchoice(0.001f, 0.002f, 0.003f), dchoice(-0.0015f, -0.0013f, -0.001f)));
                b->destroyFlags.offScreen = false;
                b->destroyFlags.destroyTime = 360.0f;
            }
        }
    }

    void boss2Pattern3(BSp s) {
        float spawnTime = dchoice(60, 60, 80);
        rtfyex(s, rtx, 120, spawnTime) {
            BulletType bt = BulletType::KnifeRed;
            if (ti(s) % 240 > 120) { bt = BulletType::KnifeBlue; }
            every(s, 5) {
                nringi(o, i, dchoice(8, 16, 16)) {
                    Bsp b = s->spawnPreset(bt, s->pos + glm::vec2(avecd(o)), boss2Pattern3BFunc);
                    b->initializeCustomVars(s->pos, 8.0f, 2.0f, -0.01f, -0.001f, 30 + 15 * i + spawnTime - rtx);
                }
            }
        }
    }

    void boss2Pattern3BFunc(Bp b) {
        during(b, cf(b, 6)) {
            spinningDirectionalBullet(b);
        }
        delay(b, cf(b, 6));
        once(b) { b->speed = 10.0f; }
        forever(b) { directionalBullet(b); }
        
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