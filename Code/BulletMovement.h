#pragma once
#include <algorithm>
#include "Movement.h"

class Bullet;

namespace BulletMovement {
    typedef void (*UpdateFunc)(Bullet*);

    void directionalBullet(Bullet* bullet);
    void homingBullet(Bullet* bullet);
    void spinningDirectionalBullet(Bullet* bullet);
    void spinningDirectionalBullet2(Bullet* bullet);
    void switchDirectionalBullet(Bullet* bullet);

    glm::vec2 targetPlayer(Bullet* b, glm::vec2 playerOffset = glm::vec2(0.0f));
    glm::vec2 targetPlayer(glm::vec2 initialPos, glm::vec2 playerOffset = glm::vec2(0.0f));

    struct BulletInitializer {
        UpdateFunc f;
        BulletInitializer() : f(directionalBullet) {}
        BulletInitializer(UpdateFunc aFunc) { f = aFunc; }
        virtual void init(std::shared_ptr<Bullet> b) {};
    };

    struct DirectionalBullet : BulletInitializer {
        glm::vec2 dir;
        float spd;
        DirectionalBullet(glm::vec2 aDir, float aSpd) : BulletInitializer(directionalBullet) {
            dir = aDir;
            spd = aSpd;
        }
        void init(std::shared_ptr<Bullet> b);
    };

    struct TargetedBullet : BulletInitializer {
        float spd;
        TargetedBullet(float _spd) : BulletInitializer(directionalBullet) {
            spd = _spd;
        }
        void init(std::shared_ptr<Bullet> b);
    };

    struct SpinningDirectionalBullet : BulletInitializer {
        glm::vec2 center;
        float radiusChange;
        float angleChange;
        float acceleration;
        float spinAcceleration;
        SpinningDirectionalBullet(glm::vec2 aCenter, float aRadiusChange, float aAngleChange, float aAcceleration, float aSpinAcceleration) : BulletInitializer(spinningDirectionalBullet) {
            center = aCenter;
            radiusChange = aRadiusChange;
            angleChange = aAngleChange;
            acceleration = aAcceleration;
            spinAcceleration = aSpinAcceleration;
        }
        void init(std::shared_ptr<Bullet> b);
    };

    struct SwitchDirectionalBullet : BulletInitializer {
        glm::vec2 d1;
        glm::vec2 d2;
        float s1;
        float s2;
        float time;
        SwitchDirectionalBullet(glm::vec2 initialDir, float initialSpeed, float changeTime, glm::vec2 secondDir, float secondSpeed) : BulletInitializer(switchDirectionalBullet) {
            d1 = initialDir;
            d2 = secondDir;
            s1 = initialSpeed;
            s2 = secondSpeed;
            time = changeTime;
        }
        SwitchDirectionalBullet(glm::vec2 initialDir, float initialSpeed, float changeTime, float secondSpeed) : BulletInitializer(switchDirectionalBullet) {
            d1 = initialDir;
            d2 = initialDir;
            s1 = initialSpeed;
            s2 = secondSpeed;
            time = changeTime;
        }
        void init(std::shared_ptr<Bullet> b);
    };
}