#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>

class Bullet;
namespace Movement {
    //spd > 0, currTime should start at 0
    float oscillate(float min, float max, float spd, float currTime, float startPos);
    inline float oscillate(float min, float max, float spd, float currTime) {
        return oscillate(min, max, spd, currTime, (max - min) / 2);
    }
};

namespace BulletMovement {
    typedef void (*UpdateFunc)(Bullet*);

    void directionalBullet(Bullet* bullet);
    void homingBullet(Bullet* bullet);
    void spinningDirectionalBullet(Bullet* bullet);
    void spinningDirectionalBullet2(Bullet* bullet);

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
}