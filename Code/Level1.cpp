#include "Level1.h"
#include "GameWindow.h"
#include "EnemyBuilder.h"

//please do not use namespace std... you will probably break some of these macros

//better name plz...
//For X frames Every Y frames
#define fxey(obj, x, y) if (obj->frameInterval(x, 0, y))

//every interval frames
#define every(obj, interval) if (obj->frameInterval(interval))

//wait for
#define wf(obj, time) if (obj->wait(time))

//wait for, returns true n times
#define wf2(obj, time, n) if (obj->wait(time, n))

//wait until
#define wu(obj, time) if (obj->waitUntil(time))

//wait until, returns true n times
#define wu2(obj, time, n) if (obj->waitUntil(time, n))

//bullet ring, vname is the variable name to insert
#define nring(vname, num) for (float vname = 0; vname < 360.0; vname += 360.0f/num)

//bullet stack, vname is the variable name to insert
#define nstack(vname, minspd, incr, num) for (float vname = minspd; vname<num * incr + minspd; vname += incr)

//unfortunate that you cant declare i as an int but it'll have to do
#define nstacki(vname, i, minspd, incr, num) for (float vname = minspd, i = 0; vname<num * incr + minspd; vname += incr, i+=1)

//bullet spread, vname is the variable name to insert, assumes num > 1
#define nspread(vname, center, range, num) for (float vname = center-range/2; vname < center + range/2 + range/num; vname += range/(num-1))

#define rad glm::radians

//get vector from angle, i is the variable name to insert
#define avec(vname, angle) glm::vec2 vname{cos(angle), sin(angle)}

#define avecd(angle) glm::vec2(cos(rad(angle)), sin(rad(angle)))

//idk maybe I just want to be lazy
#define sfs [](BulletSpawner* s)
#define sf(name) [](BulletSpawner* name)


#define t(obj) obj->currTime

//reduce time
#define rt(obj, n) static_cast<float>(static_cast<int>(t(obj)) % static_cast<int>(n))

#define initwait(obj, time) if (t(obj) < static_cast<float>(time)) {return;}

namespace Level {
    typedef BulletSpawner* BSp;
    typedef Bullet* Bp;
    typedef Enemy* Ep;
    typedef std::shared_ptr<Enemy> Esp;
    typedef std::shared_ptr<Bullet> Bsp;
    typedef std::shared_ptr<BulletSpawner> BSsp;

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
        wf(l, 0.5_s) {
            //Esp e = director.buildEnemy(fairy, glm::vec2(0.0f, 500.0f), enemyTestFunc); // Make a fairy at 0, 500
            //e->createBulletSpawner(glm::vec2(0, 0), macroExample);
            Esp e = director.buildEnemy(fairy, glm::vec2(0.0f, 500.0f), [](Ep e) {
                initwait(e, 30);
                every(e, 60) e->dir = randomDir();
                fxey(e, 60, 30) e->move(linearBurst(rt(e, 60), 8.0f, 0.5f, 30) * e->dir, glm::vec4(-400.0f, 400.0f, 400.0f, 800.0f));
            });
            e->createBulletSpawner(glm::vec2(0, 0), sf(s) {
                
                every(s, 7) {
                    nring(o, 4) {
                        nspread(a, o, 10, 2)
                        s->spawnPreset(BulletType::Knife, s->pos, DirectionalBullet{ avecd(a), 10.0f });
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
                        avec(dir, o + t(s)/10);
                        //s->spawnPreset(BulletType::Knife, s->pos + dir, SpinningDirectionalBullet(s->pos, 3.0f, 0.5f, 0.02f, 0.0f));
                    }
                }
            });
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

    void macroExample(BSp s) { //BSp is short for BulletSpawner*
        every(s, 17) { //every 17 frames...
            nring(offset, 8) { //create a ring of 8 bullets, variable name offset (this is the angle offset for each bullet in the ring)
                nstack(spd, 5.0f, 3.0f, 3) { //create a stack of 3 bullets, speed of first bullet is 5.0f, second bullet is 5.0f + 3.0f, third bullet is 5.0f + 2 * 3.0f
                    float angle = rad(t(s)/2 + offset); //rad is short for glm::radians, t is short for s->currTime
                    avec(dir, angle); //initialize variable dir to be a vec2 pointing at angle
                    s->spawnPreset(BulletType::Knife, s->pos, BulletMovement::DirectionalBullet{ dir, spd });
                }
            }
        }
    }

    void bs1(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 2 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = glm::radians(360.0f * oscillate(spawner->currTime, -1, 1, 0.04f) + offset + 0.25f * spawner->currTime);
                glm::vec2 dir{ cos(angle), sin(angle) };
                spawner->spawnPreset(BulletType::Knife, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 10.0f });
            }
        }
    }

    void bs_1(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 2 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = rad(360.0f * oscillate(-1, 1, 0.04f, spawner->currTime) + offset + 0.25f * spawner->currTime);
                glm::vec2 dir{ cos(angle), sin(angle) };
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 10.0f });
            }
        }
    }

    void bs2(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 3 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = glm::radians(linearAcceleration(spawner->currTime, 0.05f, 4.71f, 60.0f, true) + offset);
                glm::vec2 dir{ cos(angle), sin(angle) };
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 20.0f });
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

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos, BulletMovement::directionalBullet);
            glm::vec2 dir{ sin(90 + 45 * spawner->currTime), cos(90 + 45 * spawner->currTime) };
            bullet->initializeCustomVars(Movement::Speed{ 10.0f }, Movement::Direction{ dir });
            bullet->setRotation(dir);
        }

        if ((int)(spawner->currTime) % 5 == 0 && (int)(spawner->currTime) % 100 != 5 && (int)(spawner->currTime) % 100 != 10) {
            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::RoundBlue, spawner->pos, BulletMovement::directionalBullet);
            glm::vec2 dir = glm::normalize(GameWindow::player->getPos() - bullet->getPos());
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
            dir = glm::normalize(dir);
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
        glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x));
        glm::vec2 finalDir = glm::normalize(1.1f * spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]));

        if (b->currTime < 15) {
            b->move(glm::vec2(0.0f, -1.0f) * b->customFloats[0]);
        }
        else {
            b->move(finalDir * b->customFloats[0]);
        }
    }

    void bulletSpawnerTestFuncDisplay(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 1 == 0) {

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos, spinningDirectionalBulletDisplay);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(63.017 * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = glm::normalize(dir);
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
        glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x));
        glm::vec2 finalDir = glm::normalize(spinDir * 1.05f + glm::vec2(b->customFloats[3], b->customFloats[4]));

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

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos, testFunc3);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(64.513f * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = glm::normalize(dir);
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
        glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x)) * (1 + b->currTime / 500);
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

            std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos, spinningDirectionalBullet);
            bullet->customFloats.push_back(10.0f);
            float angle = glm::radians(64.513f * spawner->currTime);
            glm::vec2 dir{ sin(angle), cos(angle) };
            dir = glm::normalize(dir);
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
        glm::vec2 spinDir = glm::normalize(glm::vec2(temp.y, -temp.x));
        glm::vec2 finalDir = glm::normalize(1.1f * spinDir + glm::vec2(b->customFloats[3], b->customFloats[4]));

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
                //std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos + dir, Bullet::spinningDirectionalBullet);
                //bullet->initializeCustomVars(spawner->pos.x, spawner->pos.y, 8.0f, 0.7f, 0.02f, 0.00f);
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos + dir, BulletMovement::SpinningDirectionalBullet{ spawner->pos, 6.0f, 0.7f, 0.02f, 0.00f });
            }
        }
    }

    void spinningDirectionalBullet(Bullet* b) {
        //centerX, centerY, radiusChange, angleChange, acceleration, spin acceleration
        glm::vec2 center = glm::vec2(b->customFloats[0], b->customFloats[1]);
        glm::vec2 radius = center - b->getPos();
        float angle = 180 - glm::degrees(glm::orientedAngle(glm::normalize(radius), glm::vec2(1, 0)));

        float incrAngle = angle + b->customFloats[3];
        float incrRadius = glm::length(radius) + b->customFloats[2] * (1 + b->currTime * b->customFloats[4]);
        glm::vec2 radiusEx = glm::vec2(incrRadius * cos(glm::radians(incrAngle)), incrRadius * sin(glm::radians(incrAngle)));
        b->move((radius + radiusEx) * (1 + b->currTime * b->customFloats[5]));
        if (b->currTime == 100) {
            b->destroy();
        }
    }
}