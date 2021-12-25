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
#include "BulletMovement.h"
#include "CollidableObject.h"

class Bullet :
    public CollidableObject
{
public:
    static std::vector<std::shared_ptr<Bullet>> bullets;
    static std::shared_ptr<Bullet> makeBullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling = glm::vec3(50.0f));
    

    typedef void (*UpdateFunc)(Bullet*);
    typedef BulletMovement::Direction Direction;
    typedef BulletMovement::Speed Speed;

    
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

