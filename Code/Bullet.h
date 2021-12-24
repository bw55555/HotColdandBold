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
    UpdateFunc updatefunc;
    std::vector<float> customFloats;

    //use this if you want, not necessary
    glm::vec2 dir = glm::vec2(0.0f, -1.0f);
    //use this if you want, not necessary
    float speed = 10.0f;

    float currTime;
    float destroyTime;
    bool firedByPlayer = false;
    bool destroyed = false;
    Bullet(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Bullet*), glm::vec3 scaling = glm::vec3(50.0f));
    void update();
    void destroy();
};

