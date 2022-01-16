#include "Level1.h"
#include "LevelMacros.h"
#include "GameWindow.h"
#include "EnemyBuilder.h"
#include "BossEnemy.h"

namespace Level {
    
    float operator"" _s(long double val) {
        return val * 60.0f;
    };

    float operator"" _s(unsigned long long val) {
        return val * 60.0f;
    }

    using namespace Movement;
    using namespace BulletMovement;
    void Level1(GLp l) {
        //FairyBuilder* fairy = new FairyBuilder(); // Creates the FairyBuilder
        //DoppleBuilder* dopple = new DoppleBuilder(); // Creates the DoppleBuilder
        //EnemyBuildDirector director; //Creates the director
        //std::cout << "Running Level Update\n";
        L1Part1(l);
        L1Part2(l);
        wf(l, 120.0f) { GameWindow::Instance->clearScreen(); }
        once(l) {
            std::shared_ptr<Enemy> e = BossEnemy::makeBossEnemy(300.0f, Hitbox::Circle(10), glm::vec2(0.0f, 500.0f), GameWindow::enemyTextures[0], bossUFunc);
        }
        delay(l, 30.0f);
        delayClear(l, 10000.0f);
        wf(l, 30) {
            //switch to win menu here
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
            
            //e->createBulletSpawner(glm::vec2(0, 0), bossPattern2);
            
            //e->createBulletSpawner(glm::vec2(0, 0), bossPattern6);
            
            
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

    void L1Part1(GLp l) {
        during(l, 360) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(850.0f, 900.0f), L1P1EnemyFunc);
                e->createBulletSpawner(L1P1EnemyBSFunc);
            }
        }
        delay(l, 60);
        delayClear(l, 900);
        delay(l, 60);
        during(l, 360) {
            every(l, 60) {
                Esp e = Enemy::makePresetEnemy(EnemyType::Fairy, glm::vec2(850.0f, 900.0f), L1P1EnemyFunc2);
                e->createBulletSpawner(L1P1EnemyBSFunc);
            }
        }
        delay(l, 60);
        delayTrigger(l, Enemy::enemies.size() == 0, 900); // same as delayClear(l, 900)
        delay(l, 60);
    }

    void L1P1EnemyFunc(Ep e) {
        float mT = 600.0f;
        during(e, mT) {
            float cbct = cubic_bezier_time(t(e), mT, 0, .89, 1, .57);
            e->moveTo(followBezierCurve(cbct, glm::vec2(850.0f, 900.0f), glm::vec2(-850.0f, 400.0f), glm::vec2(566.0f, 504.0f)));
        } 
        wf(e, mT) {
            e->destroy();
        }
    }

    void L1P1EnemyFunc2(Ep e) {
        float mT = 600.0f;
        during(e, mT) {
            float cbct = cubic_bezier_time(t(e), mT, 0, .89, 1, .57);
            e->moveTo(followBezierCurve(cbct, glm::vec2(-850.0f, 900.0f), glm::vec2(850.0f, 400.0f), glm::vec2(-566.0f, 504.0f)));
        } 
        wf(e, mT) {
            e->destroy();
        }
    }

    void L1P1EnemyBSFunc(BSp s) {
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

    void L1Part2(GLp l) {
        once(l) {
            nspread(xpos, 0, 1200, 8) {
                Esp e = Enemy::makePresetEnemy(EnemyType::WeakFairy, glm::vec2(xpos, 1100.0f), L1P2EnemyFunc);
            }
        }
        delayClear(l, 660);
    }

    void L1P2EnemyFunc(Ep e) {
        during(e, 30) {
            e->move(glm::vec2(0.0f, 1.0f) * linearBurst(t(e), -20.0f, 0.5f, 30));
        } delay(e, 30);
        once(e) { e->createBulletSpawner(L1P2EnemyBSFunc); }
        delay(e, 600);
        during(e, 30) {
            float accel = 0.5f;
            e->move(glm::vec2(0.0f, 1.0f)*std::max(e->getNestedTime() * accel, 20.0f));
        } 
        wf(e, 30) { e->destroy(); };
        
    }

    void L1P2EnemyBSFunc(BSp s) {
        every(s, 120) {
            nstack(spd, dchoice(6, 8, 10), 2.0f, dchoice(3, 4, 6)) {
                s->spawnPreset(BulletType::RoundBlue, DirectionalBullet(glm::vec2(0.0f, -1.0f), spd));
            }
        }
        everyo(s, 120, 60) {
            nring(o, 16) {
                s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(o), dchoice(5.0f, 6.0f, 8.0f)));
            }
        }
    }

    void bossUFunc(Enemy* e) {
        float destroyTime = 3600.0f;
        if (e->onNextPhase()) {
            once(e) { e->createBulletSpawner(glm::vec2(0, 0), bossPattern7); }
            wf(e, destroyTime) {
                e->destroy();
            }
        }
        if (e->onNextPhase()) {
            once(e) { 
                e->createBulletSpawner(glm::vec2(0, 0), bossPattern6); }
            forever(e) {
                enemyTestFunc(e);
            }
            wf(e, destroyTime) {
                e->destroy();
            }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            once(e) { e->createBulletSpawner(glm::vec2(0, 0), bossPattern1); }
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
            once(e) { e->createBulletSpawner(glm::vec2(0, 0), bossPattern2); }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            once(e) { e->createBulletSpawner(glm::vec2(0, 0), bossPattern3); }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            once(e) { e->createBulletSpawner(glm::vec2(0, 0), bossPattern4); }
            wf(e, destroyTime) { e->destroy(); }
        }
        if (e->onNextPhase()) {
            motw(e, glm::vec2(0.0f, 500.0f), 30.0f);
            once(e) { e->createBulletSpawner(glm::vec2(0, 0), bossPattern5); }
            wf(e, destroyTime) { e->destroy(); }
        }
    }

    void bossPattern1(BSp s) {
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

    void bossPattern2(BSp s) {
        int spawnInterval = 90; //probably too hard
        spawnInterval = 120; //this is a lot easier...
        fyex(s, spawnInterval, 18) { //executes 18 frames in a row every spawnInterval frames
            every(s, 2) { //every 2 frames
                nring(o, 6) { //6 bullets in a ring
                    nstacki(spd, i, 4, 2, 5) { //5 bullets in a stack with varying speed
                        BulletType bt = rt(s, spawnInterval*2) < spawnInterval ? BulletType::KnifeBlue : BulletType::KnifeRed; //alternate bullet type
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

    void bossPattern3(BSp s) {
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

    void bossPattern4(BSp s) {
        every(s, 40) {
            float rf = randomFloat(0.0f, 15.0f);
            rf = 0;
            nring(a, 12) {
                nstack(spd, 5, 0.3, 7) {
                    s->spawnPreset(BulletType::KnifeBlue, DirectionalBullet(avecd(rf + a + 15 * t(s)/40), spd));
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

    void bossPattern5(BSp s) {
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

    void bossPattern6(BSp s) {
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
        everyo(s, sI, sI/2) {
            nringi(a, i, numBullets) {
                float wave = initialSpeed * oscillate(i + 1, -1, 1, waveChange, 0);
                s->spawnPreset(BulletType::KnifeRed, SwitchDirectionalBullet(avecd(a - 2.34653 * t(s) / sI + 360/5/2), 1.0f + 2.0f * initialSpeed + wave, 15.0f, finalSpeed + randomFloat(0.0f, 1.0f)));
            }
        }
    }

    //spawns stars and throws them at you!
    void bossPattern7(BSp s) {
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

    //it failed, but happy accidents
    void bossPattern7Fail(BSp s) {
        every(s, 3000.0f) {
            nring(o, 7) {
                float numBullets = 7.0f;
                nrep(i, numBullets) {
                    float height = 10.0f;
                    float radius = 20.0f;
                    float halflength = pow(pow(radius, 2) - pow(height, 2), 0.5);
                    
                    float l_incr = 2 * halflength / (numBullets - 1);
                    float iLength = halflength - l_incr * i;
                    float angle = glm::degrees(asin(iLength/radius));
                    
                    glm::vec2 dest = static_cast<float>(pow(pow(iLength, 2) + pow(height, 2), 0.5)) * avecd(o + angle);
                    std::cout << halflength << " " << l_incr << " " << iLength << " A: " << angle << " Dest: " << dest.x << " " << dest.y << "\n";
                    Bsp b = s->spawnPresetwLambda(BulletType::RoundBlue, s->pos, [](Bp b) {
                        motw(b, glm::vec2(cf(b, 0), cf(b, 1)), 15);
                        b->rotateAround(glm::vec2(cf(b, 2), cf(b, 3)), 2);
                        });
                    b->initializeCustomVars(s->pos + 15.0f * dest, s->pos);
                }
            }
        }
    }

    void macroExample(BSp s) { //BSp is short for BulletSpawner*
        wf(s, 60.0f) { //executes once at 60 frames (1 second). Adds 60 to the wait timer
            std::cout << t(s) << " 1\n";
            fyex(s, 7, 2) {
                std::cout << "This never happens\n";
            } //this statement is useless because wf executes only once
        } //the next statement will try to execute immediately not next update
        wf2(s, 6.0f, 5) { //executes 5 times at 66 to 70 frames. (not 6 to 10 frames, 60 is added by the wait timer) 
            //Adds 6 to the wait timer. note that executing 5 times does not add an extra 5 to the timer
            std::cout << t(s) << " 2\n";
            fyex(s, 7, 2) { std::cout << t(s) << " 3\n"; } //this statement will only execute once at 70 frames (why?)
            //probably need a function to standardize times inside waits so this problem doesn't happen

            //wf(s, 10.0f) {} //wf or any other wait function will cause runtime errors that will cause problems somewhere
            //currently, best option is to use fyexo()
            fyexo(s, 7, 2, -1) { std::cout << t(s) << " 3.5\n"; } //this executes at 69 and 70 frames. 
        }
        forever(s) {std::cout << t(s) << " 4ever\n"; } //executes forever from 66 frames to end of time
        wu(s, 65.0f) { std::cout << "Never\n"; } //the wait timer is currently 66 frames, so the code will never run. 
        wu(s, 1.5_s) { std::cout << t(s) << " 5\n"; } //executes once at 90 frames (_s is short for 60 frames). This does not stop forever() from running
        delay(s, 1_s) { //basically adds 1 second to the wait timer. Not very useful since wf exists, but hey readability
            //does not need brackets, but it is not an error to provide them anyway so be careful
            every(s, 1) { std::cout << t(s) << " tl6\n"; } //this executes every frame since it is considered top level...
        }
        until(s, 3_s) { std::cout << t(s) << " 7\n"; } //executes every frame from 150 frames inclusive to 180 frames inclusive
        once(s) { std::cout << t(s) << " 8\n"; } //executes once at 150 frames not 180 frames since until does not increase the wait timer. 
        delayTo(s, 3_s); //its surprisingly hard to create a function that increases the wait timer while having the same functionality as until. 
        //the best alternative I have is to use both until() and delayTo(). It works, so don't complain
        //in fact, the only unique functions are wf2, wu2, and until. All other functions are just readability versions of these 3
        //basically all other functions can be implemented with just wf2, wu2 and until. 

        //enclose every single statement in at least one time/wait function. 
        //even if you want code to run every frame, use every(s, 1) (to ignore wait timer) or forever(s) (to use the wait timer) instead of being lazy



        //this will execute every frame since it is top level
        every(s, 17) { //every 17 frames...
            nring(offset, 8) { //create a ring of 8 bullets, variable name offset (this is the angle offset for each bullet in the ring)
                nstack(spd, 5.0f, 3.0f, 3) { //create a stack of 3 bullets, speed of first bullet is 5.0f, second bullet is 5.0f + 3.0f, third bullet is 5.0f + 2 * 3.0f
                    float angle = rad(t(s)/2 + offset); //rad is short for glm::radians, t is short for s->currTime
                    avec(dir, angle); //initialize variable dir to be a vec2 pointing at angle
                    s->spawnPreset(BulletType::KnifeBlue, s->pos, BulletMovement::DirectionalBullet{ dir, spd });
                }
            }
        }
    }

    void bs1(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 2 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = glm::radians(360.0f * oscillate(spawner->currTime, -1, 1, 0.04f) + offset + 0.25f * spawner->currTime);
                glm::vec2 dir{ cos(angle), sin(angle) };
                spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 10.0f });
            }
        }
    }

    void bs_1(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 2 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = rad(360.0f * oscillate(-1, 1, 0.04f, spawner->currTime) + offset + 0.25f * spawner->currTime);
                glm::vec2 dir{ cos(angle), sin(angle) };
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 10.0f });
            }
        }
    }

    void bs2(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 3 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = glm::radians(linearAcceleration(spawner->currTime, 0.05f, 4.71f, 60.0f, true) + offset);
                glm::vec2 dir{ cos(angle), sin(angle) };
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 20.0f });
            }
        }
    }


    void enemyTestFunc(Enemy* enemy) {
        //how to use void* like this?
        if (enemy->customFloats.size() <= 0) {
            enemy->customFloats.push_back(1.0f);
            return;
        }
        float xpos = enemy->getPos().x;
        float spd = 2.0f;

        if (xpos <= -800.0f) {
            enemy->customFloats[0] = 1.0f;
        }
        if (xpos >= 800.0f) {
            enemy->customFloats[0] = -1.0f;
        }

        float dir = enemy->customFloats[0];
        enemy->move(glm::vec2(dir * spd, 0.0f));

    }

    void enemyFasterFunc(Enemy* enemy) {
        //how to use void* like this?
        if (enemy->customFloats.size() <= 0) {
            std::cout << "Custom Floats not initialized" << std::endl;
            return;
        }
        float xpos = enemy->getPos().x;
        float spd = 20.0f;

        if (xpos <= -800.0f) {
            enemy->customFloats[0] = 1.0f;
        }
        if (xpos >= 800.0f) {
            enemy->customFloats[0] = -1.0f;
        }

        float dir = enemy->customFloats[0];
        enemy->move(glm::vec2(dir * spd, 0.0f));

    }


    void bulletSpawnerTestFunc(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 1 == 0) {

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos, BulletMovement::directionalBullet);
            glm::vec2 dir{ sin(90 + 45 * spawner->currTime), cos(90 + 45 * spawner->currTime) };
            bullet->initializeCustomVars(Movement::Speed{ 10.0f }, Movement::Direction{ dir });
            bullet->setRotation(dir);
        }

        if ((int)(spawner->currTime) % 5 == 0 && (int)(spawner->currTime) % 100 != 5 && (int)(spawner->currTime) % 100 != 10) {
            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::RoundBlue, spawner->pos, BulletMovement::directionalBullet);
            glm::vec2 dir = normalizeSafe(GameWindow::player->getPos() - bullet->getPos());
            bullet->initializeCustomVars(Movement::Speed{ 20.0f }, Movement::Direction{ dir });
            bullet->setRotation(dir);
        }
    }

    

    void bulletSpawnerTestFunc2(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 1 == 0) {

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::RoundBlue, spawner->pos, testFunc2);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(60 * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = normalizeSafe(dir);
            bullet->customFloats.push_back(spawner->pos.x);
            bullet->customFloats.push_back(spawner->pos.y);
            bullet->customFloats.push_back(dir.x);
            bullet->customFloats.push_back(dir.y);
            bullet->setRotation(dir);
        }
    }

    void testFunc2(Bullet* b) {
        //speed, centerX, centerY, directionX, directionY

        glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
        glm::vec2 spinDir = normalizeSafe(glm::vec2(temp.y, -temp.x));
        glm::vec2 finalDir = normalizeSafe(1.1f * spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]));

        if (b->currTime < 15) {
            b->move(glm::vec2(0.0f, -1.0f) * b->customFloats[0]);
        }
        else {
            b->move(finalDir * b->customFloats[0]);
        }
    }

    void bulletSpawnerTestFuncDisplay(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 1 == 0) {

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos, spinningDirectionalBulletDisplay);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(63.017 * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = normalizeSafe(dir);
            bullet->customFloats.push_back(spawner->pos.x);
            bullet->customFloats.push_back(spawner->pos.y);
            bullet->customFloats.push_back(dir.x);
            bullet->customFloats.push_back(dir.y);
            bullet->setRotation(dir);
        }
    }

    void spinningDirectionalBulletDisplay(Bullet* b) {
        //speed, centerX, centerY, directionX, directionY

        glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
        glm::vec2 spinDir = normalizeSafe(glm::vec2(temp.y, -temp.x));
        glm::vec2 finalDir = normalizeSafe(spinDir * 1.05f + glm::vec2(b->customFloats[3], b->customFloats[4]));

        if (b->currTime < 15) {
            b->move(glm::vec2(b->customFloats[3], b->customFloats[4]) * b->customFloats[0]);
        }
        else {
            b->move(finalDir * b->customFloats[0]);
            b->setRotation(finalDir);
        }
    }

    void bulletSpawnerTest3(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 1 == 0) {

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos, testFunc3);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(64.513f * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = normalizeSafe(dir);
            bullet->customFloats.push_back(spawner->pos.x);
            bullet->customFloats.push_back(spawner->pos.y);
            bullet->customFloats.push_back(dir.x);
            bullet->customFloats.push_back(dir.y);
            bullet->setRotation(dir);
        }
    }

    void testFunc3(Bullet* b) {
        //speed, centerX, centerY, directionX, directionY

        glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
        glm::vec2 spinDir = normalizeSafe(glm::vec2(temp.y, -temp.x)) * (1 + b->currTime / 500);
        glm::vec2 finalDir = spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]);

        if (b->currTime < 15) {
            b->move(glm::vec2(b->customFloats[3], b->customFloats[4]) * b->customFloats[0]);
        }
        else if (b->currTime < 360) {
            b->move(finalDir * b->customFloats[0]);
            b->setRotation(finalDir);
        }
        else if (b->currTime == 360) {
            b->customFloats.push_back(finalDir.x);
            b->customFloats.push_back(finalDir.y);
        }
        else {
            b->move(glm::vec2(b->customFloats[0] * glm::vec2(b->customFloats[5], b->customFloats[6])));
        }
    }

    void bulletSpawnerTest4(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 1 == 0) {

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos, spinningDirectionalBullet);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(64.513f * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = normalizeSafe(dir);
            bullet->customFloats.push_back(spawner->pos.x);
            bullet->customFloats.push_back(spawner->pos.y);
            bullet->customFloats.push_back(dir.x);
            bullet->customFloats.push_back(dir.y);
            bullet->setRotation(dir);
        }
    }

    void testFunc4(Bullet* b) {
        //speed, centerX, centerY, directionX, directionY

        glm::vec2 temp = glm::vec2(b->customFloats[1], b->customFloats[2]) - b->getPos();
        glm::vec2 spinDir = normalizeSafe(glm::vec2(temp.y, -temp.x));
        glm::vec2 finalDir = normalizeSafe(1.1f * spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]));

        if (b->currTime < 15) {
            b->move(glm::vec2(b->customFloats[3], b->customFloats[4]) * b->customFloats[0]);
        }
        else {
            b->move(glm::vec2((1 + b->currTime / 30) * b->customFloats[0] * finalDir));
            b->setRotation(finalDir);
        }

        if (b->currTime == 100) {
            b->destroy();
        }
    }

    void bulletSpawnerTestSpinning(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 7 == 0) {
            for (float offset = 0; offset < 360; offset += 72) {
                float angle = glm::radians(3.0f * spawner->currTime + offset);
                glm::vec2 dir{ cos(angle), sin(angle) };
                //std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos + dir, Bullet::spinningDirectionalBullet);
                //bullet->initializeCustomVars(spawner->pos.x, spawner->pos.y, 8.0f, 0.7f, 0.02f, 0.00f);
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::KnifeBlue, spawner->pos + dir, BulletMovement::SpinningDirectionalBullet{ spawner->pos, 6.0f, 0.7f, 0.02f, 0.00f });
            }
        }
    }
}