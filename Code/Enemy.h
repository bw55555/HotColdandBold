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
#include "BulletSpawner.h"

#include "CollidableObject.h"
class Enemy :
    public CollidableObject
{
public:
    static std::vector<Enemy*> enemies;

    typedef void (*UpdateFunc)(Enemy*);
    UpdateFunc updatefunc;
    std::vector<void*> customVars;

    std::vector<BulletSpawner*> spawners;
    float currTime;
    Enemy(Hitbox collisionbox, glm::vec2 initialPos, unsigned int textureID, void (*func)(Enemy*));
    void update();
    ~Enemy();
};

