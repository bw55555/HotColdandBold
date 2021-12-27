#include "Level1.h"
#include "GameWindow.h"
#include "EnemyBuilder.h"

namespace Level {
    using namespace Movement;

    void Level1(GameLevel* level) {
        float ct = level->currTime;
        FairyBuilder* fairy = new FairyBuilder(); // Creates the FairyBuilder
        DoppleBuilder* dopple = new DoppleBuilder(); // Creates the DoppleBuilder
        EnemyBuildDirector director; //Creates the director
        if (level->wait(30)) {
            std::shared_ptr<Enemy> e = director.buildEnemy(fairy, glm::vec2(0.0f, 500.0f), doNothingFunc); // Make a fairy at 0, 500
            e->createBulletSpawner(glm::vec2(0, 0), bs1);
        }
        if (level->wait(30)) {
            //std::shared_ptr<Enemy> e2 = director.buildEnemy(fairy, glm::vec2(500.0f, 100.0f), enemyFasterFunc);
            //e2->createBulletSpawner(glm::vec2(0, 0), bulletSpawnerTestSpinning);
        }
        if (level->waitUntil(120)) {
            //std::shared_ptr<Enemy> e3 = director.buildEnemy(dopple, glm::vec2(500.0f, 500.0f), enemyTestFunc);
        }
        delete fairy;
        delete dopple;
    }

    void bs1(BulletSpawner* spawner) {
        if ((int)(spawner->currTime) % 2 == 0) {
            for (float offset = 0; offset < 360; offset += 45) {
                float angle = glm::radians(360.0f * oscillate(-1, 1, 0.04f, spawner->currTime) + offset + 0.25 * spawner->currTime);
                glm::vec2 dir{ cos(angle), sin(angle) };
                std::shared_ptr<Bullet> bullet = spawner->spawnPreset(BulletType::Knife, spawner->pos + dir, BulletMovement::DirectionalBullet{ dir, 10.0f });
            }
        }
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