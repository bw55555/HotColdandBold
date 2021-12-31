#include "Level1.h"
#include "LevelMacros.h"
#include "GameWindow.h"
#include "EnemyBuilder.h"

namespace Level {
    
    float operator"" _s(long double val) {
        return val * 60.0f;
    };

    float operator"" _s(unsigned long long val) {
        return val * 60.0f;
    }

    using namespace Movement;
    using namespace BulletMovement;
    void Level1(GameLevel* l) {
        FairyBuilder* fairy = new FairyBuilder(); // Creates the FairyBuilder
        DoppleBuilder* dopple = new DoppleBuilder(); // Creates the DoppleBuilder
        EnemyBuildDirector director; //Creates the director
        //std::cout << "Running Level Update\n";
        wf(l, 0.5_s) {
            //Esp e = director.buildEnemy(fairy, glm::vec2(0.0f, 500.0f), enemyTestFunc); // Make a fairy at 0, 500
            //e->createBulletSpawner(glm::vec2(0, 0), macroExample);
            Esp e = director.buildEnemy(dopple, glm::vec2(0.0f, 500.0f), [](Ep e) {
                delay(e, 30);
                every(e, 60) e->dir = randomDir();
                //fyex(e, 60, 30) e->move(linearBurst(rt(e, 60), 8.0f, 0.5f, 30) * e->dir, glm::vec4(-400.0f, 400.0f, 400.0f, 800.0f));
            });
            e->createBulletSpawner(glm::vec2(0, 0), bossPattern2);
        }
        wf(l, 1.5_s) {
            //force you to unfocus, must keep player at the bottom of the screen
            /*
            Esp e2 = director.buildEnemy(fairy, glm::vec2(0.0f, 100.0f), enemyTestFunc);
            e2->createBulletSpawner(glm::vec2(0, 0), [](BSp s) {
                every(s, 4) s->spawnPreset(BulletType::RoundBlue, s->pos, TargetedBullet{ 10.0f });
            });
            */
        }
        wu(l, 4.0_s) {
            //std::shared_ptr<Enemy> e3 = director.buildEnemy(dopple, glm::vec2(500.0f, 500.0f), enemyTestFunc);
        }
        delete fairy;
        delete dopple;
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
        fyex(s, spawnInterval, 24) { //executes 24 frames in a row every spawnInterval frames
            every(s, 2) { //every 2 frames
                nring(o, 6) { //6 bullets in a ring
                    nstacki(spd, i, 4, 2, 5) { //5 bullets in a stack with varying speed
                        BulletType bt = rt(s, spawnInterval*2) < spawnInterval ? BulletType::KnifeBlue : BulletType::KnifeRed; //alternate bullet type
                        Bsp b = s->spawnPresetwLambda(bt, s->pos + avecd(1.2f * o + 3.7385f * t(s) + 26.0f * i), [](Bp b) { //choose a starting direction
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
            std::cout << "Custom Floats not initialized" << std::endl;
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