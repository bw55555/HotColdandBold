#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

namespace Movement {
    struct Velocity {
        glm::vec2 vel;
        Velocity() : vel(glm::vec2(0.0f, -1.0f)) {}
        Velocity(float x, float y) { vel = glm::vec2(x, y); }
        Velocity(glm::vec2 aVel) { vel = aVel; }
    };

    struct Direction {
        glm::vec2 dir;
        Direction() : dir(glm::vec2(0.0f, -1.0f)) {}
        Direction(float x, float y) { dir = glm::normalize(glm::vec2(x, y)); }
        Direction(glm::vec2 aDir) { dir = glm::normalize(aDir); }
    };

    struct Speed {
        float spd;
        Speed() : spd(10.0f) {}
        Speed(float aSpd) { spd = aSpd; }
    };
    float randomFloat(float low, float high);
    glm::vec2 randomDir(float minAngle = 0.0f, float maxAngle = 360.0f);

    //oscillate and linearAccel does not return a movement speed, but a distance
    //likely should be in a different namespace, but what to name that namespace?

    //spd > 0, currTime should start at 0
    float oscillate(float currTime, float min, float max, float spd, float startPos);
    inline float oscillate(float currTime, float min, float max, float spd) {
        return oscillate(currTime, min, max, spd, (max + min) / 2);
    }
    float linearAcceleration(float currTime, float acceleration, float maxVelocity, float maxTime, bool reverseFlag);
    inline float linearAcceleration(float currTime, float acceleration, float maxVelocity, float maxTime) {
        return linearAcceleration(currTime, acceleration, maxVelocity, maxTime, false);
    }
    inline float linearAcceleration(float currTime, float acceleration, float maxVelocity) {
        return linearAcceleration(currTime, acceleration, maxVelocity, -1.0f, false);
    }
    inline float linearAcceleration(float currTime, float acceleration) {
        return linearAcceleration(currTime, acceleration, -1.0f, -1.0f, false);
    }

    //returns a speed, quick deceleration at the end
    float linearBurst(float currTime, float initialVelocity, float deceleration, float maxTime);
};