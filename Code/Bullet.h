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

#include "CollidableObject.h"

class Enemy;

struct Direction {
    glm::vec2 dir;
    Direction() : dir(glm::vec2(0.0f, -1.0f)) {}
    Direction(float x, float y) { dir = glm::vec2(x, y); }
    Direction(glm::vec2 aDir) { dir = aDir; }
};

struct Speed {
    float spd;
    Speed() : spd(10.0f) {}
    Speed(float aSpd) { spd = aSpd; }
};



class Bullet :
    public CollidableObject
{
public:
    

    static std::vector<std::shared_ptr<Bullet>> bullets;
    static std::shared_ptr<Bullet> makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling = glm::vec3(50.0f));
    static void directionalBullet(Bullet* bullet);
    static void homingBullet(Bullet* bullet);
    static void spinningDirectionalBullet(Bullet* bullet);
    static void spinningDirectionalBullet2(Bullet* bullet);

    typedef void (*UpdateFunc)(Bullet*);
    struct BulletInitializer {
        UpdateFunc f;
        BulletInitializer() : f(Bullet::directionalBullet) {}
        BulletInitializer(UpdateFunc aFunc) { f = aFunc; }
        virtual void init(std::shared_ptr<Bullet> b) {};
    };

    struct DirectionalBullet : BulletInitializer {
        glm::vec2 dir;
        float spd;
        DirectionalBullet(glm::vec2 aDir, float aSpd) : BulletInitializer(Bullet::directionalBullet) {
            dir = aDir;
            spd = aSpd;
        }
        void init(std::shared_ptr<Bullet> b) {
            b->initializeCustomVars(Speed{ spd }, Direction{ dir });
        }
    };

    struct SpinningDirectionalBullet : BulletInitializer {
        glm::vec2 center;
        float radiusChange;
        float angleChange;
        float acceleration;
        float spinAcceleration;
        SpinningDirectionalBullet(glm::vec2 aCenter, float aRadiusChange, float aAngleChange, float aAcceleration, float aSpinAcceleration) : BulletInitializer(Bullet::spinningDirectionalBullet) {
            center = aCenter;
            radiusChange = aRadiusChange;
            angleChange = aAngleChange;
            acceleration = aAcceleration;
            spinAcceleration = aSpinAcceleration;
        }
        void init(std::shared_ptr<Bullet> b) {
            b->initializeCustomVars(center.x, center.y, radiusChange, angleChange, acceleration, spinAcceleration);
        }
    };

    
    UpdateFunc updatefunc;
    std::vector<float> customFloats;
    //use this if you want, not necessary
    glm::vec2 dir = glm::vec2(0.0f, -1.0f);
    //use this if you want, not necessary
    float speed = 10.0f;


    void initializeCustomVars(float x)
    {
        customFloats.push_back(x);
    }

    void initializeCustomVars(Direction x)
    {
        dir = x.dir;
    }

    void initializeCustomVars(Speed x)
    {
        speed = x.spd;
    }

    template<typename T, typename... Args>
    void initializeCustomVars(T x, Args... args) // recursive variadic function
    {
        initializeCustomVars(x);
        initializeCustomVars(args...);
    }


    

    float currTime;
    float destroyTime;
    bool firedByPlayer = false;
    bool destroyed = false;
    Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling = glm::vec3(50.0f));
    void update();
    void destroy();
};

